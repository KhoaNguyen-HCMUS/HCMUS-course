# python3

import sys


def build_suffix_array(s):
    n = len(s)
    suffixes = sorted((s[i:], i) for i in range(n))
    suffix_array = [suffix[1] for suffix in suffixes]
    return suffix_array


def build_lcp_array(s, suffix_array):
    n = len(s)
    rank = [0] * n
    lcp = [0] * n
    for i, suffix in enumerate(suffix_array):
        rank[suffix] = i
    h = 0
    for i in range(n):
        if rank[i] > 0:
            j = suffix_array[rank[i] - 1]
            while i + h < n and j + h < n and s[i + h] == s[j + h]:
                h += 1
            lcp[rank[i]] = h
            if h > 0:
                h -= 1
    return lcp


def solve(s, t):
    concat_str = s + "#" + t
    suffix_array = build_suffix_array(concat_str)
    lcp_array = build_lcp_array(concat_str, suffix_array)

    max_len = 0
    start_s = start_t = 0
    n, m = len(s), len(t)

    for i in range(1, len(concat_str)):
        if (suffix_array[i] < n) != (suffix_array[i - 1] < n):
            if lcp_array[i] > max_len:
                max_len = lcp_array[i]
                if suffix_array[i] < n:
                    start_s = suffix_array[i]
                    start_t = suffix_array[i - 1] - (n + 1)
                else:
                    start_s = suffix_array[i - 1]
                    start_t = suffix_array[i] - (n + 1)

    return start_s, start_t, max_len


for line in sys.stdin.readlines():
    s, t = line.split()
    i, j, l = solve(s, t)
    print(i, j, l)
