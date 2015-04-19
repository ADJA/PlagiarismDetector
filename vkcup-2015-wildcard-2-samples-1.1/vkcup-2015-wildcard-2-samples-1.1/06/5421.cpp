#include<cstdio>
#include<iostream>
#include<algorithm>
#include<cstring>
#define N 2010000
using namespace std;
typedef long long LL;
LL pre[N];
int n, i, m, j, vis[N], la[N], lr[N], s[N], q[N], tr[N], a[N], tim;
inline int gi()
{
    int s = 0; char c = getchar();
    while (c < '0' || c > '9') c = getchar();
    while (c >= '0' && c <= '9') s = s * 10 + c - '0', c = getchar();
    return s;
}
void Work(LL x)
{
    int j = 1;
    for (i = 1; i <= n + n; i++)
    {
        while (j < min(i, n) + n && pre[j] - pre[i - 1] <= x) ++j;
        la[i] = j - 1;
    }
    ++tim; int ans = n + 1;
    for (i = 1; i <= la[1]; i++)
    {
        int h = 0;
        if (i > n) i -= n, h = 1;
        int t = 0, sum = 0, ed = i + n - 1;
        for (j = i; j <= ed; j = la[j] + 1) {
            if (vis[j] == tim) {
                sum += s[j];
                if (lr[j] < ed) sum++, j = lr[j] + 1;
                q[++t] = j, tr[t] = sum; break;
            }
            else q[++t] = j, tr[t] = ++sum;
        }
        for (j = t; j >= 1; j--)
            vis[q[j]] = tim, lr[q[j]] = la[q[t]], s[q[j]] = tr[t] - tr[j - 1];
        ans = min(ans, sum);
        if (h) i += n;
    }
    i = la[1] + 1;
    if (i <= n) {
        int ed = i + n - 1, sum = 0;
        for (j = i; j <= ed; j = la[j] + 1) ++sum;
        ans = min(ans, sum);
    }
    printf("%d\n", ans);
    
}
int main()
{
    scanf("%d%d", &n, &m);
    for (i = 1; i <= n; i++) a[i] = a[i + n] = gi();
    for (i = 1; i <= n + n; i++) pre[i] = pre[i - 1] + a[i];
    while (m--)
    {
        LL x; scanf("%I64d", &x);
        Work(x);
    }
    return 0;
}
