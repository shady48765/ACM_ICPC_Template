import sys

def debug(*params):
    print >> sys.stderr, params

def solve(count):
    p, values3 = solve3(count[3], count[9], count[6])
    values5 = solve5(count[5], count[10])
    result = 0
    for t3, a3, b3 in values3:
        for t5, a5, b5 in values5:
            params = [count[2], count[4], count[8]]
            params[p] += a3
            params[0] += a5
            coef = solve2(*params)
            constant = coef[0] + coef[1] * count[2] + coef[2] * count[4] + coef[3] * count[8]
            if t3 == 0:
                constant += coef[p + 1] * a3
            if t5 == 0:
                constant += coef[1] * a5
            amt = amount(t3, a3, b3) * amount(t5, a5, b5)
            result += constant * amt
            if t3 == 1:
                result += coef[p + 1] * (a3 + b3) * amt / 2
            if t5 == 1:
                result += coef[1] * (a5 + b5) * amt / 2
    result *= (count[7] + 1) * (count[11] + 1)
    return result % (10 ** 9 + 7)

def amount(t, a, b):
    if t == 0:
        return b
    return b - a + 1

def solve2(a, b, c):
    if a >= 2:
        return (1, 1, 2, 3)
    if a == 1:
        if b >= 1:
            return (1, 1, 2, 3)
        if b == 0:
            return (2, 0, 0, 2)
    if a == 0:
        if b == 0:
            return (1, 0, 0, 1)
        if b == 1:
            return (2, 0, 0, 2)
        if b >= 2:
            if c == 0:
                return (1, 0, 1, 0)
            if c > 0:
                return (-1, 0, 2, 3)

def add_range(values, a, b):
    while a < 2 and a <= b:
    #while a <= b:
        values.append((0, a, 1))
        a += 1
    if a <= b:
        values.append((1, a, b))

def solve5(c5, c10):
    values = []
    if 0 < min(c5, c10):
        add_range(values, 0, min(c5, c10) - 1)
    if c5 < c10:
        values.append((0, c5, c10 - c5))
    if c10 < c5:
        values.append((0, c10, c5 - c10))
    add_range(values, 0, min(c5, c10))
    return values

def solve3(c3, c9, c6):
    if c3 > 0:
        return (0, solve5(c3 + c9 * 2, c6))
    ## 0 <= x <= 2 * c9 + c6
    ## max{x - 2 * c9, 0} <= y <= min{x, c6}, x = y (mod 2)
    ## if x < min(2 * x9, x6)
    ##   0 <= y <= x, x = y (mod 2)
    values = []
    if 0 < min(2 * c9, c6):
        t = min(2 * c9, c6) - 1
        add_range(values, 0, t / 2)
        if t > 0:
            add_range(values, 0, (t - 1) / 2)
    ## if 2 * c9 <= x < c6
    ##   x - 2 * x9 <= y <= x
    if 2 * c9 < c6:
        values.append((0, c9, c6 - 2 * c9))
    ## if x6 <= x < 2 * x9
    ##   0 <= y <= x6
    if c6 < 2 * c9:
        values.append((0, c6 / 2, max(c9 - (c6 + 1) / 2, 0)))
        if c6 > 0:
            values.append((0, (c6 - 1) / 2, max(c9 - c6 / 2, 0)))
    t = min(2 * c9, c6)
    add_range(values, 0, t / 2)
    if t > 0:
        add_range(values, 0, (t - 1) / 2)
    return (1, values)

f = sys.stdin
count = [0] + map(int, f.readline().split())
count.append(0)
print(solve(count))
