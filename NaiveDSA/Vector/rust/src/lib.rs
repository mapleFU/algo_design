#![feature(ptr_internals)]

extern crate alloc;

#[allow(unused)]
pub mod mvector;

#[cfg(test)]
mod tests {
    #[test]
    fn it_works() {
        assert_eq!(2 + 2, 4);
    }
}
