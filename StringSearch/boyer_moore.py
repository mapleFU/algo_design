import unittest
from collections import defaultdict


def build_right(text: str):
    right = defaultdict(lambda: 0)
    for i, ch in enumerate(text):
        right[ch] = i + 1
    return right


def boyer_moore(pat: str, text: str):
    right = build_right(pat)

    i = 0
    while i <= len(text) - len(pat):

        dif_pos = len(pat) - 1
        while dif_pos >= 0 and text[i + dif_pos] == pat[dif_pos]:
            dif_pos -= 1
        if dif_pos == -1:
            return i
        delta_pos = len(pat) - right[text[i + dif_pos]]
        if delta_pos < 1:
            delta_pos = 1
        i += delta_pos
    return len(text)


class BMFindTest(unittest.TestCase):
    def test_find(self):
        self.assertTrue(boyer_moore('AAAAB', 'AAAACAAAAB') == 5)
        self.assertTrue(boyer_moore('bbab', 'abbab') == 1)

    def test_unfind(self):
        self.assertTrue(boyer_moore('AAAAB', 'AAAACBAAAB') == len('AAAACBAAAB'))


if __name__ == '__main__':
    unittest.main()
    # print(boyer_moore('bbab', 'abbab'))