
use std::ptr::Unique;

pub struct MVector<T> {
    ptr: Unique<T>,
    cap: usize,
    len: usize
}

