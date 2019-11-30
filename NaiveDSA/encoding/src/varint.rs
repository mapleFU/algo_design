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

use super::zigzag::ZigZag;
use num_traits::{int, CheckedNeg};
#[allow(unused)]
use num_traits::cast::{FromPrimitive, AsPrimitive};

pub trait Varint {
    fn varint(s: Self) -> Vec<u8>;
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

impl<T: int::PrimInt + CheckedNeg> Varint for T {
    fn varint(i: Self) -> Vec<u8> {
        let mut unsigned = i.zig_encoding();
        // 1 7 for a number
        // 1 is msb.
        // 7 is end.
        let mut result = Vec::new();
        while unsigned != Self::from(0).unwrap() {
            let end;
            let current;
            if unsigned >= Self::from(GROUP_VAL).unwrap() {
                end = 1;
                current = unsigned % Self::from(GROUP_VAL).unwrap();
                unsigned = unsigned / Self::from(GROUP_VAL).unwrap();
            } else {
                end = 0;
                current = unsigned;
                unsigned = Self::from(0).unwrap();
            }
            // write
            write_group(&mut result, end != 0, current.to_u8().unwrap() );
        }

        result
    }

    fn from_varint(v: Vec<u8>) -> Self {
        let mut current: u64 = 0;
        let mut times = 1;
        for arg in v {
            let continuing: bool;
            let mut val = arg;
            if arg > GROUP_MAX as u8{
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
        Self::from(current).unwrap().zig_decoding()
    }
}

#[cfg(test)]
mod test {
    use super::Varint;

    #[test]
    fn test_encoding() {
        let test_arg: Vec<(i32, usize)> = vec![
            (1, 1),
            (300, 2)
        ];

        for (k, v) in test_arg {
            let var = i32::varint(k);
            assert_eq!(var.len(), v);
            assert_eq!(i32::from_varint(var), k);
        }
    }
}