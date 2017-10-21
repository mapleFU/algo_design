from collections import namedtuple


Record = namedtuple('Record', 'length value')


def get_min_length_1(l: list, s: int) -> int:
    pre_records = list()
    min_length = len(l) + 1
    pre_records.append((1, l[0]))
    for i in range(1, len(l)):
        cur_records = list()

        if l[i] > s:
            return 1
        else:
            cur_records.append(Record(1, l[i]))

        for value in pre_records:
            pre_len, pre_val = value
            cur_len, cur_val = pre_len + 1, pre_val + l[i]
            if cur_val > s:
                if cur_len < min_length:
                    min_length = cur_len
            else:
                cur_records.append(Record(cur_len, cur_val))

        pre_records = cur_records
    return min_length


def get_min_length_2(seq: list, need_sum: int)->int:
    dp = list()
    dp.append(0)
    for value in seq:
        if len(dp):
            dp.append(dp[len(dp) - 1] + value)
        else:
            dp.append(value)
    # 得到dp的和序列

    min_length = len(dp) + 1
    cur_index, pre_index = 1, 0
    while cur_index < len(dp):
        while cur_index < len(dp) and dp[cur_index] - dp[pre_index] < need_sum:
            cur_index += 1
        if cur_index >= len(dp):
            continue
        while pre_index < cur_index and dp[cur_index] - dp[pre_index] >= need_sum:
            min_length = min(min_length, cur_index - pre_index)
            pre_index += 1
        if min_length > cur_index - pre_index + 1:
            min_length = cur_index - pre_index + 1
    return min_length


l = [1, 6, 1, 2, 3, 2, 1]
s = 8
assert get_min_length_2(l, s) == 3

l = [10, 15, 5, 1, 3, 5, 10, 7, 4, 9, 2, 8]
s = 15
assert get_min_length_2(l, s) == 1

l = [5, 1, 3, 5, 10, 7, 4, 9, 2, 8]
s = 15
assert get_min_length_2(l, s) == 2

l = [1, 2, 3, 4, 5]
s = 11
assert get_min_length_2(l, s) == 3

