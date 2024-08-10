import sys


def solve(k, text, pattern):
    positions = []
    len_t = len(text)
    len_p = len(pattern)

    for i in range(len_t - len_p + 1):
        mismatches = 0
        for j in range(len_p):
            if text[i + j] != pattern[j]:
                mismatches += 1
                if mismatches > k:
                    break
        if mismatches <= k:
            positions.append(i)

    return positions


# Read input from standard input
for line in sys.stdin.readlines():
    k, t, p = line.split()
    ans = solve(int(k), t, p)
    print(len(ans), *ans)
