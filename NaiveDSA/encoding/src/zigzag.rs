use num_traits::int;
use num_traits::sign::Signed;
use std::mem;

/// ZigZag is an algorithm according to this note: https://gist.github.com/mfuerstenau/ba870a29e16536fdbaba
/// It was common used by some rpc protocol, like protobuf and avro.
///
/// Zigzag is implements for all signed int.
/// The encoding number is actually an unsigned int, but it was represented the same as signed int.
/// If you want to interpret it, please use `as u_` to get it.
pub trait ZigZag {
    fn zig_encoding(self) -> Self;
    fn zig_decoding(self) -> Self;
}

impl<T: int::PrimInt + Signed> ZigZag for T {
    fn zig_encoding(self) -> Self {
        // zigzag for integer
        let sz: usize = mem::size_of::<Self>() * 8;
        (self << 1) ^ (self >> (sz - 1))
    }

    fn zig_decoding(self) -> Self {
        // self.bitand(1).neg() must valid.
        self.unsigned_shr(1) ^ -self.bitand(Self::one())
    }
}

#[cfg(test)]
mod test {
    use super::ZigZag;

    #[test]
    fn test_encoding() {
        for i in -100..=100 {
            if i < 0 {
                assert_eq!((-i * 2 - 1) as u32, i.zig_encoding() as u32);
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
