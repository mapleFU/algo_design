from .Polynomial import Poly


class Counter:
    def __init__(self, x1, x2, x5):
        self.x1 = x1
        self.x2 = x2
        self.x5 = x5
        seq1 = Poly(1, x1)
        seq2 = Poly(2, x2)
        seq5 = Poly(5, x5)
        self.expr = seq1 * seq2 * seq5
        self.__length = len(self.expr)

    def count(self):
        cnt = 0
        for v in self.expr.seq:
            cnt += v
        return cnt

    def get_solution(self, n):
        return self.expr.seq[self.__length - n]

    def print_all_solutions(self):
        for i in range(1, self.__length + 1):
            sol = self.get_solution(i)
            if sol != 0:
                print('总值为{}的方法有{}种'.format(i, sol))

    def __len__(self):
        return self.__length
