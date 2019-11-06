use std::alloc::{alloc, dealloc, realloc, Layout};
use std::mem;
use std::ops::{Deref, DerefMut};
use std::ptr::Unique;
///
/// 按照 《Rust 死灵书》写的 sample
/// 用到的材料除了 《Rust 死灵书》还有：
/// 1. LLVM GEP 指令:
///    https://opensource.apple.com/source/clang/clang-211.10.1/src/docs/LangRef.html#i_getelementptr
///    https://opensource.apple.com/source/clang/clang-211.10.1/src/docs/GetElementPtr.html#intro
///
use std::{ptr, slice};

pub struct MVector<T> {
    ptr: Unique<T>,
    cap: usize,
    len: usize,
}

impl<T> MVector<T> {
    pub fn insert(&mut self, index: usize, elem: T) {
        assert!(index <= self.len, "index is out of bound");
        if self.cap == self.len {
            self.grow();
        }
        unsafe {
            // insert at `index`, meaning that [index, end) will be moved to [index + 1, end + 1)
            // [index] = elem.
            ptr::copy(
                self.ptr.as_ptr().offset(index as isize),
                self.ptr.as_ptr().offset((index + 1) as isize),
                self.len - index,
            );
            ptr::write(self.ptr.as_ptr().offset(index as isize), elem);
        }
        self.len += 1;
    }

    /// Remove the data by the index in the `MVector`
    ///
    /// panic:
    ///
    /// It will panic if index is out of bound.
    pub fn remove(&mut self, index: usize) -> T {
        assert!(index < self.len, "index must < self.len in `remove`");
        self.len -= 1;
        unsafe {
            let to_return = ptr::read(self.ptr.as_ptr().offset(index as isize));
            ptr::copy(
                self.ptr.as_ptr().offset((index + 1) as isize),
                self.ptr.as_ptr().offset(index as isize),
                self.len - index,
            );
            to_return
        }
    }

    pub fn push(&mut self, elem: T) {
        if self.len == self.cap {
            self.grow();
        }
        unsafe {
            ptr::write(self.ptr.as_ptr().offset(self.len as isize), elem);
        }
        self.len += 1;
    }

    pub fn pop(&mut self) -> Option<T> {
        if self.len == 0 {
            None
        } else {
            let to_return = unsafe { Some(ptr::read(self.ptr.as_ptr().offset(self.len as isize - 1))) };
            self.len -= 1;
            to_return
        }
    }

    pub fn new() -> Self {
        assert_ne!(mem::size_of::<T>(), 0);
        println!("new() called");
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

    pub fn len(&self) -> usize {
        self.len
    }

    pub fn cap(&self) -> usize {
        self.cap
    }
}

impl<T> Drop for MVector<T> {
    fn drop(&mut self) {
        if self.cap != 0 {
            // need to release memory
            while let Some(_) = self.pop() {}

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

impl<T> Deref for MVector<T> {
    type Target = [T];

    fn deref(&self) -> &[T] {
        unsafe { slice::from_raw_parts(self.ptr.as_ptr(), self.len) }
    }
}

impl<T> DerefMut for MVector<T> {
    fn deref_mut(&mut self) -> &mut [T] {
        unsafe { slice::from_raw_parts_mut(self.ptr.as_mut(), self.len) }
    }
}
