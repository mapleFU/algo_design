#![feature(ptr_internals)]

extern crate alloc;

#[allow(unused)]
pub mod mvector;

#[cfg(test)]
mod tests {
    use crate::mvector::MVector;

    #[test]
    fn vec_push_back() {
        let mut v: MVector<usize> = MVector::new();
        for i in 1..2 {
            v.push(i);
            assert_eq!(v.len(), i);
        }
    }
}
