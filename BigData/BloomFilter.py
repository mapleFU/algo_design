from typing import List


class BloomFilter:
    def __init__(self, length: int, hashFuncs: List, data_sets: set=None):
        self._filters = [0 for _ in range(length)]
        self._length = length
        self._hash_funcs = hashFuncs
        if data_sets is not None:
            for var in data_sets:
                self.push_filter(var)
           
    def push_filter(self, var):
        if var is not None:
            for hash_func in self._hash_funcs:
                self._filters[hash_func(var) % self._length] = 1

    def in_filter(self, var):
        for hash_func in self._hash_funcs:
            if self._filters[hash_func(var) % self._length] != 0:
                return True
        return False


class CountBloomFilter(BloomFilter):
    def push_filter(self, var):
        if var is not None:
            for hash_func in self._hash_funcs:
                self._filters[hash_func(var) % self._length] += 1

    def delete_filter(self, var):
        if self.in_filter(var):
            for hash_func in self._hash_funcs:
                self._filters[hash_func(var) % self._length] -= 1
