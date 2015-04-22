from sys import stdin
from itertools import repeat
def main():
    n = int(stdin.readline())
    d = map(int, stdin.readline().split(), repeat(10, n))
    m = int(stdin.readline())
    a = map(int, stdin.readline().split(), repeat(10, m))
    sa = [0] * n
    for x in a:
        sa[x-1] += 1
    sd = 0
    sx = [0, 1, -1]
    tx = [0, 1, 1]
    si = [0] * n
    def walk(p):
        x, dx, sgn = p
        x += dx
        r = (d[x] - d[x-dx]) * dx * sgn
        if x == n - 1:
            dx = -1
        if x == 0:
            dx = 1
        p[0], p[1] = x, dx
        return r
    si[0] = 1
    for i in xrange(m - 1):
        sd += walk(tx)
        si[tx[0]] += 1
    c = 0
    for i in xrange(n):
        c += si[i] == sa[i]
    ans = []
    for i in xrange(n * 2):
        if c == n:
            ans.append(sd)
        px = sx[0]
        if si[px] == sa[px]:
            c -= 1
        si[px] -= 1
        if si[px] == sa[px]:
            c += 1
        sd += walk(sx)
        sd += walk(tx)
        px = tx[0]
        if si[px] == sa[px]:
            c -= 1
        si[px] += 1
        if si[px] == sa[px]:
            c += 1
    if not ans:
        print -1
    elif min(ans) == max(ans):
        print max(ans)
    else:
        print -1
main()
