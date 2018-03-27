def solve(c, s):
    if c % 2 != 0 or c < 4 or s < (c / 2) - 1:
        return []
    a = c / 4
    b = c / 2 - a
    if s > a * b:
        return []
    d = a * b - s
    if d == 0:
        return [(0, 0), (a, 0), (a, b), (0, b)]
    if d % (a - 1) == 0:
        return [(0, 0), (a, 0), (a, b - d / (a - 1)), (1, b - d / (a - 1)), (1, b), (0, b)]
    if d <= a - 1:
        return [(0, 0), (a, 0), (a, b - 1), (a - d % (a - 1), b - 1), (a - d % (a - 1), b), (0, b)]
    return [(0, 0), (a, 0), (a, b - d / (a - 1) - 1), (a - d % (a - 1), b - d / (a - 1) - 1), (a - d % (a - 1), b - d / (a - 1)), (1, b - d / (a - 1)), (1, b), (0, b)]

c, s = map(int, raw_input().split())
poly = solve(c, s)
if len(poly) == 0:
    print -1
else:
    print len(poly)
    for x, y in poly:
        print x, y
