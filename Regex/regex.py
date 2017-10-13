import unittest


class Regex:
    def build_nfa(self, pat: str):
        """
        :param pat:
        :return: an nfa
        """
        dfa = dict() # from dfa[state][ch] = nextstate
        for ch in pat:
            if ch == '|':
                pass
            elif ch == '(':
                pass
            elif ch == '*':
                pass
            else:
                pass

    def build_dfa(self, nfa):
        """
        :param nfa: builded nfa
        :return: an dfa
        """
        pass

    def __init__(self, pat: str):
        if not isinstance(pat, str):
            raise TypeError('{} in Regex is not a str'.format(pat))
        nfa = build_nfa(pat)
        dfa = build_dfa(nfa)
        self.dfa = dfa

    def regex_find(self, text: str):
        pass


class RegTest(unittest.TestCase):
    def setUp(self):
        self.reg = Regex('a*(b|c)')

    def test_find(self):
        reg = self.reg
        self.assertTrue(reg.regex_find('ab'))
        self.assertTrue(reg.regex_find('b'))
        self.assertTrue(reg.regex_find('aaac'))

    def test_unfind(self):
        self.assertFalse(reg.regex_find('aaabc'))
        self.assertFalse(reg.regex_find('fasd'))


if __name__ == '__main__':
    unittest.main()

