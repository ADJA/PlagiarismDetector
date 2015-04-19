#include <bits/stdc++.h>
using namespace std;

const int INF = (int) 2e9 + 7;
const int N = (int) 1e5;
char buf[20];
int a[3 * N];
bool unknown[3 * N];
int n;
int k;

long long sum(long long from, long long to) {
    return to * (to + 1) / 2 - from * (from - 1) / 2;
}

long long F(long long start, int cnt) {
    if (start < 0 && start + cnt - 1 > 0) return F(start, -start) + F(0, cnt + start);
    if (start < 0) return sum(-(start + cnt - 1), -start);
    return sum(start, start + cnt - 1);
}

int getFirst(long long before, long long after, int gap) {
    long long low = before + 1;
    long long high = after - gap;
    if (low > high) return INF;
    while (low < high) {
        long long mid = (low + high) / 2;
        if (low + 1 == high) mid = low;
        if (F(mid, gap) <= F(mid + 1, gap)) high = mid;
        else low = mid + 1;
    }
    return low;
}

int main() {
    ios::sync_with_stdio(false);
    scanf("%d%d", &n, &k);
    for (int i = 0; i < n; ++i) {
        scanf("%s", buf);
        if (buf[0] == '?') unknown[k + i] = true;
        else sscanf(buf, "%d", &a[k + i]);
    }
    for (int i = 0; i < k; ++i) {
        a[i] = -INF;
        a[n + k + i] = INF;
    }
    n += 2 * k;
    for (int start = 0; start < k; ++start) {
        int first = start;
        while (first + k < n) {
            int last = first + k;
            int gap = 0;
            while (last < n && unknown[last]) {
                ++gap;
                last += k;
            }
            assert(last < n);
            if (gap > 0) {
                int firstValue = getFirst(a[first], a[last], gap);
                if (firstValue == INF) {
                    puts("Incorrect sequence");
                    return 0;
                }
                for (int x = first + k; x != last; x += k) a[x] = firstValue++;
            } else {
                if (a[first] >= a[last]) {
                    puts("Incorrect sequence");
                    return 0;
                }
            }
            first = last;
        }
    }
    n -= 2 * k;
    for (int i = 0; i < n; ++i) {
        if (i > 0) printf(" ");
        printf("%d", a[k + i]);
    }
    printf("\n");
    return 0;
}
