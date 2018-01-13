import numpy as np


# 代表多项式的类
class Poly:
    def __init__(self, exp=None, n=None, seq=None):
        # max_len = exp * (n - 1)
        if exp is not None and n is not None:
            self.seq = np.poly1d(Poly.get_poly(exp, n))
        elif seq is not None:
            self.seq = seq
        else:
            raise ValueError(exp, n, seq)

    def __mul__(self, other):
        if isinstance(other, Poly):
            seq = other.seq * self.seq
            return Poly(seq=seq)
        else:
            raise TypeError(other)

    @staticmethod
    def get_poly(exp: int, n: int):
        """
        :param exp:
        :param n:
        :return:
        """
        # return (i * exp for i in range(0, n))
        return [1 if i % exp == 0 else 0 for i in range(n * exp, -1, -1)]

    def __len__(self):
        return len(self.seq)


def main():
    p = Poly(1, 4)


if __name__ == '__main__':
    main()
