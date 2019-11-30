use num_traits::int;
use std::mem;

pub trait ZigZag {
    fn zig_encoding(self)->Self;
    fn zig_decoding(self)->Self;
}

impl<T: int::PrimInt> ZigZag for T {
    fn zig_encoding(self) -> Self {
        // zigzag for integer
        let sz: usize = mem::size_of::<Self>();

        (self << 1) ^ (self >> sz - 1)
    }

    fn zig_decoding(self) -> Self {
        unimplemented!()
    }
}

#[test]
mod test {
    use super::ZigZag;

    #[test]
    fn test_encoding() {
        for i in -10..=10 {
            println!("{}", i.zig_encoding());
        }
    }
}