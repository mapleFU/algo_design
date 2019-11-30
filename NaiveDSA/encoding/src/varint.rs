use super::zigzag::ZigZag;
#[allow(unused)]
use num_traits::cast::{AsPrimitive, FromPrimitive};
use num_traits::int;
use num_traits::sign::Signed;

/// https://developers.google.com/protocol-buffers/docs/encoding#varints
/// Varints is used in protobuf. Varints are a method of serializing integers using one or more bytes.
/// Smaller numbers take a smaller number of bytes.
///
/// Each byte in a varint, except the last byte,
/// has the most significant bit (msb) set – this indicates that there are further bytes to come.
/// The lower 7 bits of each byte are used to store the two's complement representation of the number in groups of 7 bits,
/// least significant group first.
///
/// I implement this with the cppreference bit-field part: https://en.cppreference.com/w/cpp/language/bit_field
pub trait Varint {
    /// Change a signed int to varint vector.
    fn varint(s: Self) -> Vec<u8>;
    /// Parse varint vector to signed int.
    fn from_varint(v: Vec<u8>) -> Self;
}

const GROUP_MAX: usize = 127;
const GROUP_VAL: usize = 128;

fn write_group(data: &mut Vec<u8>, is_end: bool, val: u8) {
    assert!(val <= GROUP_MAX as u8);
    let mut v = val;
    if is_end {
        v += GROUP_VAL as u8;
    }
    data.push(v);
}

impl<T: int::PrimInt + Signed> Varint for T {
    fn varint(i: Self) -> Vec<u8> {
        let mut unsigned = i.zig_encoding();
        // 1 7 for a number
        // 1 is msb.
        // 7 is end.
        let mut result = Vec::new();
        let max_group_val = Self::from(GROUP_VAL).unwrap();
        while unsigned != Self::zero() {
            let end;
            let current;
            if unsigned >= max_group_val {
                end = 1;
                current = unsigned % max_group_val;
                unsigned = unsigned / max_group_val;
            } else {
                end = 0;
                current = unsigned;
                unsigned = Self::zero();
            }
            // current max be less than u8, so it will not panic.
            write_group(&mut result, end != 0, current.to_u8().unwrap());
        }

        result
    }

    fn from_varint(v: Vec<u8>) -> Self {
        let mut current: u64 = 0;
        let mut times = 1;
        for arg in v {
            let continuing: bool;
            let mut val = arg;
            if arg > GROUP_MAX as u8 {
                continuing = false;
                val -= 128;
            } else {
                continuing = true;
            }
            current += val as u64 * times;
            times *= 128;

            if !continuing {
                break;
            }
        }
        // current should be an u64, and if data could not be cast from u64,
        // the program will panic.
        Self::from(current).unwrap().zig_decoding()
    }
}

#[cfg(test)]
mod test {
    use super::Varint;

    #[test]
    fn test_encoding() {
        let test_arg: Vec<(i32, usize)> = vec![(1, 1), (300, 2)];

        for (k, v) in test_arg {
            let var = i32::varint(k);
            assert_eq!(var.len(), v);
            assert_eq!(i32::from_varint(var), k);
        }
    }
}
