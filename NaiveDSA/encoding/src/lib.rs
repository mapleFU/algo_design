extern crate bit_field;
extern crate num_traits;

mod varint;
mod zigzag;

#[cfg(test)]
mod tests {
    #[test]
    fn it_works() {
        assert_eq!(2 + 2, 4);
    }
}
