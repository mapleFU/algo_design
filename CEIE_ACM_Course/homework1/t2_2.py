from random import randint
import logging
import os


def merge_and_count(A, lo, mid, hi):
    # if mid - lo <= 1 or hi - mid <= 1:
    #     return 0

    left_cursor = lo
    right_cursor = mid
    inverse = 0
    l_index = 0
    l = [0 for _ in range(lo, hi)]

    if mid - lo > 0 and hi - mid > 0:
        while left_cursor < mid and right_cursor < hi:
            # 脑子不要全是大与小于，心里要有<=
            if A[left_cursor] <= A[right_cursor]:
                # <left, right>不构成逆序数, 故left...mid内任何一个数都不和right构成逆序
                # A[left] = A[right], 此时右边的应该后移直到不重复，情况与LEFT < RIGHT相同
                l[l_index] = A[right_cursor]
                l_index += 1
                right_cursor += 1
            elif A[left_cursor] > A[right_cursor]:
                # <left, right>构成逆序数，<left-mid, right>都不构成逆序数
                # <left, right...hi>都构成逆序数
                inverse += hi - right_cursor
                l[l_index] = A[left_cursor]
                left_cursor += 1
                l_index += 1

    # 只有左侧右侧需要考虑逆序数，此处只需要写回

    while left_cursor < mid:
        l[l_index] = A[left_cursor]
        l_index += 1
        left_cursor += 1
    while right_cursor < hi:
        l[l_index] = A[right_cursor]
        l_index += 1
        right_cursor += 1

    A[lo:hi] = l
    return inverse


def count_inverse(A, lo, hi):
    if hi - lo <= 1:
        return 0
    elif hi - lo == 2:
        if A[lo] < A[lo + 1]:
            A[lo], A[lo + 1] = A[lo + 1], A[lo]
            return 1
        else:
            return 0

    # // 让inverse表示逆序数，初始化为0
    inverse = 0

    mid = (lo + hi) // 2
    inverse += count_inverse(A, lo, mid)
    inverse += count_inverse(A, mid, hi)
    inverse += merge_and_count(A, lo, mid, hi)

    return inverse


if __name__ == '__main__':
    l = [1, 8, 7, 5, 4, 2, 3, 4, 6, 2, 1, 3, 2, 9, 4, 6]
    print(count_inverse(l, 0, len(l)))

