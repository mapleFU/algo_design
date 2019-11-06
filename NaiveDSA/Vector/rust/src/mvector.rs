use std::mem;
use std::ops::{Deref, DerefMut};
use std::{ptr, slice};

#[allow(unused)]
use crate::raw_vec::*;

///
/// 按照 《Rust 死灵书》写的 sample
/// 用到的材料除了 《Rust 死灵书》还有：
/// 1. LLVM GEP 指令:
///    https://opensource.apple.com/source/clang/clang-211.10.1/src/docs/LangRef.html#i_getelementptr
///    https://opensource.apple.com/source/clang/clang-211.10.1/src/docs/GetElementPtr.html#intro
///


pub struct MVector<T> {
    buf: MRawVec<T>,
    len: usize,
}

impl<T> MVector<T> {
    pub fn insert(&mut self, index: usize, elem: T) {
        assert!(index <= self.len, "index is out of bound");
        if self.buf.cap == self.len {
            self.grow();
        }
        unsafe {
            // insert at `index`, meaning that [index, end) will be moved to [index + 1, end + 1)
            // [index] = elem.
            ptr::copy(
                self.buf.ptr.as_ptr().offset(index as isize),
                self.buf.ptr.as_ptr().offset((index + 1) as isize),
                self.len - index,
            );
            ptr::write(self.buf.ptr.as_ptr().offset(index as isize), elem);
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
            let to_return = ptr::read(self.buf.ptr.as_ptr().offset(index as isize));
            ptr::copy(
                self.buf.ptr.as_ptr().offset((index + 1) as isize),
                self.buf.ptr.as_ptr().offset(index as isize),
                self.len - index,
            );
            to_return
        }
    }

    pub fn push(&mut self, elem: T) {
        if self.len == self.buf.cap {
            self.grow();
        }
        unsafe {
            ptr::write(self.buf.ptr.as_ptr().offset(self.len as isize), elem);
        }
        self.len += 1;
    }

    pub fn pop(&mut self) -> Option<T> {
        if self.len == 0 {
            None
        } else {
            let to_return = unsafe {
                Some(ptr::read(
                    self.buf.ptr.as_ptr().offset(self.len as isize - 1),
                ))
            };
            self.len -= 1;
            to_return
        }
    }

    pub fn new() -> Self {
        assert_ne!(mem::size_of::<T>(), 0);
        println!("new() called");
        MVector {
            buf: MRawVec::new(),
            len: 0,
        }
    }

    fn grow(&mut self) {
        self.buf.grow();
    }

    pub fn len(&self) -> usize {
        self.len
    }

    pub fn cap(&self) -> usize {
        self.buf.cap
    }
}

impl<T> Drop for MVector<T> {
    fn drop(&mut self) {
        if self.buf.cap != 0 {
            // need to release memory
            while let Some(_) = self.pop() {}
            // Not need to self delete.
            //            let align = mem::align_of::<T>();
            //            let elem_sz = mem::size_of::<T>();
            //
            //            unsafe {
            //                dealloc(
            //                    self.ptr.as_ptr() as *mut _,
            //                    Layout::from_size_align_unchecked(elem_sz, align),
            //                );
            //            }
        }
    }
}

impl<T> Deref for MVector<T> {
    type Target = [T];

    fn deref(&self) -> &[T] {
        unsafe { slice::from_raw_parts(self.buf.ptr.as_ptr(), self.len) }
    }
}

impl<T> DerefMut for MVector<T> {
    fn deref_mut(&mut self) -> &mut [T] {
        unsafe { slice::from_raw_parts_mut(self.buf.ptr.as_mut(), self.len) }
    }
}

#[allow(unused)]
pub struct MVectorIntoIter<T> {
    _buf: MRawVec<T>,

    start: *const T,
    end: *const T,
}

impl<T> Iterator for MVectorIntoIter<T> {
    type Item = T;

    fn next(&mut self) -> Option<Self::Item> {
        if self.start == self.end {
            None
        } else {
            unsafe {
                let item = ptr::read(self.start);
                self.start = self.start.offset(1);
                Some(item)
            }
        }
    }
}

impl<T> IntoIterator for MVector<T> {
    type Item = T;
    type IntoIter = MVectorIntoIter<T>;

    fn into_iter(self) -> Self::IntoIter {

        // need to use ptr::read to unsafely move the buf out since it's
        // not Copy, and Vec implements Drop (so we can't destructure it).
        // Use but removed:
        // ```
        // let buf = self.buf;
        // ```

        unsafe {
            let buf = ptr::read(&self.buf);
            let cap = buf.cap;
            let len = self.len;

            // Make sure not to drop Vec since that will free the buffer
            // TODO: make clear what will happen if we forget to using forget.
            mem::forget(self);
            let ptr = buf.ptr;
            MVectorIntoIter {
                start: ptr.as_ptr(),
                // Note: handle the case when cap is zero, and Unique is just a fucking empty pointer.
                end: if cap == 0 {
                    // can't offset off this pointer, it's not allocated!
                    ptr.as_ptr()
                } else {
                    ptr.as_ptr().offset(len as isize)
                },
                _buf:  buf,
            }
        }
    }

    //    fn size_hint(&self) -> (usize, Option<usize>) {
    //        let len = (self.end as usize - self.start as usize)
    //            / mem::size_of::<T>();
    //        (len, Some(len))
    //    }
}

impl<T> DoubleEndedIterator for MVectorIntoIter<T> {
    fn next_back(&mut self) -> Option<Self::Item> {
        if self.start == self.end {
            None
        } else {
            unsafe {
                self.end = self.end.offset(-1);
                Some(ptr::read(self.end))
            }
        }
    }
}

//impl<T> Drop for MVectorIntoIter<T> {
//    fn drop(&mut self) {
//        let align = mem::align_of::<T>();
//        let elem_sz = mem::size_of::<T>();
//
//        unsafe {
//            dealloc(
//                self.buf.as_ptr() as *mut _,
//                Layout::from_size_align_unchecked(elem_sz, align),
//            );
//        }
//    }
//}
