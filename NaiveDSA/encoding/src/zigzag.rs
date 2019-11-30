/// ZigZag is an algorithm according to this note: https://gist.github.com/mfuerstenau/ba870a29e16536fdbaba
/// It was common used by some rpc protocol, like protobuf and avro.
use num_traits::int;
#[allow(unused)]
use num_traits::sign::Signed;
use std::mem;

pub trait ZigZag {
    fn zig_encoding(self) -> Self;
    fn zig_decoding(self) -> Self;
}

impl<T: int::PrimInt + std::ops::Neg<Output = Self>> ZigZag for T {
    fn zig_encoding(self) -> Self {
        // zigzag for integer
        let sz: usize = mem::size_of::<Self>() * 8;

        (self << 1) ^ (self >> (sz - 1))
    }

    fn zig_decoding(self) -> Self {
        self.unsigned_shr(1) ^ -self.bitand(Self::from(1).unwrap())
    }
}

#[cfg(test)]
mod test {
    use super::ZigZag;

    #[test]
    fn test_encoding() {
        for i in -10..=10 {
            if i < 0 {
                assert_eq!(-i * 2 - 1, i.zig_encoding());
            } else {
                // i >= 0
                assert_eq!(i * 2, i.zig_encoding());
            }
        }
    }

    #[test]
    fn test_decoding() {
        for i in -100..=100 {
            let v = i.zig_encoding();
            assert_eq!(i, v.zig_decoding());
        }
    }
}
