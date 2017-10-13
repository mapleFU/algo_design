def build_dfa(pat: str):
    """
    :param pat:
    :return: a dfa. dfa[char][pos] SHOWS next pos
    """
    pat_len = len(pat)

    dfa = dict({ch: [0 for _ in range(pat_len)] for ch in pat})
    pre = 0
    dfa[pat[0]][0] = 1
    for i in range(1, pat_len):
        for key in dfa:
            dfa[key][i] = dfa[pat[pre]][i]
        dfa[pat[i]][i] = i + 1
        pre = dfa[pat[i]][pre]
    return dfa


def kmp(pat: str, text: str)->int:
    dfa = build_dfa(pat)
    i = 0 # text pos
    j = 0 # pat pos
    text_len = len(text)
    pat_len = len(pat)
    while i < text_len and j < pat_len:
        if text[i] not in dfa:
            j = 0
        else:
            j = dfa[text[i]][j]
        i += 1
    if j == pat_len:
        return i - pat_len
    else:
        return text_len


if __name__ == '__main__':
    print(kmp('bbab', 'abbab'))
    print(kmp('AAAAB', 'AAAACAAAAB'))
    print(kmp('AAAAB', 'AAAACBAAAB'))


