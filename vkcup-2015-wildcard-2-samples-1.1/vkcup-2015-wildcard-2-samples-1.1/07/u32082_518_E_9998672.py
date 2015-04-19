from sys import stdin, stdout
def main():
    n, k = map(int, stdin.readline().split())
    s = stdin.readline().split() + [0] * k
    for i in xrange(k):
        p = (0, -1001001001)
        t = s[i:n:k] + [1001001001]
        for j, x in enumerate(t):
            if x != "?":
                z = s[i + j * k] = int(x)
                if z - p[1] < j - p[0]:
                    print "Incorrect sequence"
                    return
                l, r = i + p[0] * k, i + j * k - k
                if z <= 0:
                    t = z - 1
                    while r >= l:
                        s[r] = t
                        t -= 1
                        r -= k
                elif p[1] >= 0:
                    t = p[1]
                    while l <= r:
                        s[l] = t
                        t += 1
                        l += k
                elif l <= r:
                    zm = (p[0] + j) / 2
                    if p[0] - p[1] < zm:
                        m = i + (p[0] - p[1]) * k
                        s[m] = t = 0
                        while m >= l:
                            s[m] = t
                            t -= 1
                            m -= k
                        m = i + (p[0] - p[1]) * k
                        s[m] = t = 0
                        while m <= r:
                            s[m] = t
                            t += 1
                            m += k
                    elif j - z > zm:
                        m = i + (j - z) * k
                        s[m] = t = 0
                        while m >= l:
                            s[m] = t
                            t -= 1
                            m -= k
                        m = i + (j - z) * k
                        s[m] = t = 0
                        while m <= r:
                            s[m] = t
                            t += 1
                            m += k
                    else:
                        m = i + zm * k
                        s[m] = t = 0
                        while m >= l:
                            s[m] = t
                            t -= 1
                            m -= k
                        m = i + zm * k
                        s[m] = t = 0
                        while m <= r:
                            s[m] = t
                            t += 1
                            m += k
                p = (j + 1, z + 1)
    for i in xrange(n - k):
        if s[i] >= s[i + k]:
            print "Incorrect sequence"
            return
    stdout.write(" ".join(map(str, s[:n])))
main()
