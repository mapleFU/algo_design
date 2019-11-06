use std::alloc::{alloc, dealloc, realloc, Layout};
use std::mem;
use std::ptr::Unique;

/// Now that we've implemented it and identified actual logic duplication,
/// this is a good time to perform some logic compression.
/// 我个人感觉比较类似 C++ 的 `vector_base`
pub(crate) struct MRawVec<T> {
    pub(crate) ptr: Unique<T>,
    pub(crate) cap: usize,
}

impl<T> MRawVec<T> {
    pub fn new() -> MRawVec<T> {
        // !0 is max usize
        let cap = if mem::size_of::<T>() == 0 { !0 } else { 0 };
        MRawVec {
            ptr: Unique::empty(),
            cap,
        }
    }

    pub(crate) fn grow(&mut self) {
        unsafe {
            let align = mem::align_of::<T>();
            let elem_sz = mem::size_of::<T>();

            // since we set the capacity to usize::MAX when elem_size is
            // 0, getting to here necessarily means the Vec is overfull.
            assert_ne!(elem_sz, 0, "capacity overflow");

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
                assert!(
                    old_num_bytes <= (::std::isize::MAX as usize) / 2,
                    "capacity overflow"
                );

                let new_num_bytes = old_num_bytes * 2;

                let ptr = realloc(
                    self.ptr.as_ptr() as *mut _,
                    Layout::from_size_align_unchecked(old_num_bytes, align),
                    new_num_bytes,
                );
                (new_cap, ptr)
            };

            // If allocate or reallocate fail, we'll get `null` back
            if ptr.is_null() {
                panic!("oom");
            }
            // Unique must not be null
            self.ptr = Unique::new(ptr as *mut _).unwrap();
            self.cap = new_cap;
        }
    }
}

impl<T> Drop for MRawVec<T> {
    fn drop(&mut self) {
        let elem_sz = mem::size_of::<T>();
        if self.cap != 0 && elem_sz != 0 {
            let align = mem::align_of::<T>();
            let elem_sz = mem::size_of::<T>();

            unsafe {
                dealloc(
                    self.ptr.as_ptr() as *mut _,
                    Layout::from_size_align_unchecked(elem_sz, align),
                );
            }
        }
    }
}

impl<T> Default for MRawVec<T> {
    fn default() -> Self {
        Self::new()
    }
}
