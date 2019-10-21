///
/// 按照 《Rust 死灵书》写的 sample
/// 用到的材料除了 《Rust 死灵书》还有：
/// 1. LLVM GEP 指令:
///    https://opensource.apple.com/source/clang/clang-211.10.1/src/docs/LangRef.html#i_getelementptr
///    https://opensource.apple.com/source/clang/clang-211.10.1/src/docs/GetElementPtr.html#intro
///
use std::ptr::Unique;
use std::mem;
use std::alloc::{alloc, realloc, Layout};


pub struct MVector<T> {
    ptr: Unique<T>,
    cap: usize,
    len: usize
}

impl<T> MVector<T> {
    fn new() -> Self {
        assert_eq!(mem::size_of::<T>(), 0);

        MVector {
            ptr: Unique::empty(),
            cap: 0,
            len: 0,
        }
    }

    fn grow(&mut self) {
        unsafe {
            let align = mem::align_of::<T>();
            let elem_sz = mem::size_of::<T>();

            let (new_cap, ptr) = if self.cap == 0 {

                let ptr = alloc(Layout::from_size_align_unchecked(elem_sz, align));
                (1, ptr)
            } else {
                // as an invariant, we can assume that `self.cap < isize::MAX`,
                // so this doesn't need to be checked.
                let new_cap = self.cap * 2;
                // Similarly this can't overflow due to previously allocating this
                let old_num_bytes = self.cap * elem_sz;

                // check that the new allocation doesn't exceed `isize::MAX` at all
                // regardless of the actual size of the capacity. This combines the
                // `new_cap <= isize::MAX` and `new_num_bytes <= usize::MAX` checks
                // we need to make. We lose the ability to allocate e.g. 2/3rds of
                // the address space with a single Vec of i16's on 32-bit though.
                // Alas, poor Yorick -- I knew him, Horatio.
                assert!(old_num_bytes <= (::std::isize::MAX as usize) / 2,
                        "capacity overflow");

                let new_num_bytes = old_num_bytes * 2;

                let ptr = realloc(self.ptr.as_ptr() as *mut _,
                                  Layout::from_size_align_unchecked(old_num_bytes, align),
                                           new_num_bytes);
                (new_cap, ptr)
            };

            // If allocate or reallocate fail, we'll get `null` back
            if ptr.is_null() { panic!("oom"); }
            // Unique must not be null
            self.ptr = Unique::new(ptr as *mut _).unwrap();
            self.cap = new_cap;
        }
    }
}