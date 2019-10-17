
array = [1, 7, 2, 6, 8, 12]
note = [True for i in range(len(array))]

last_pre = None
(pre, cur) = (0, 1)
while cur < len(array):
    if array[pre] > array[cur]:
        note[pre] = note[cur] = False
        if last_pre is None:
            pre += 2
            cur += 2
        else:
            pre = last_pre
            cur += 1
    else:
        last_pre = pre
        pre, cur = cur, cur + 1

