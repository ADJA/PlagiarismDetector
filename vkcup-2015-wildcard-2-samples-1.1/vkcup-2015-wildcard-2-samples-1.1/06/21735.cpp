#include <iostream>
#include <cstdio>
#include <cmath>
#include <cstring>
#include <algorithm>
using namespace std;
#define rep(i, l, r) for (int i = l; i <= r; i++)
#define drep(i, r, l) for (int i = r; i >= l; i--)
typedef long long ll;
const int N = 2e6 + 8;
int n, a[N], ans, go[N], s, q;
ll sum[N];
ll read()
{
    char c; ll num = 0, w = 1;
    for (c = getchar(); !isdigit(c) && c != '-'; c = getchar());
    if (c == '-') c = getchar(), w = -1;
    for (;isdigit(c); c = getchar()) num = num * 10 + c - '0';
    return num * w;
}
void solve()
{
    //printf("***%d\n", s);
    int Min = n + n, p = 0; 
    ans = n + n;
    memset(go, 0, sizeof(go));
    for (int l = 1, r = 1; l <= n + n; l++)
    {
        while (r <= min(l + n - 1, n + n) && sum[r] - sum[l - 1] <= s) r++;
        r--;
        go[l] = r + 1;
        if (l <= n && go[l] - l + 1 < Min) Min = r - l + 1, p = l;
        //printf("%d %d\n", l, go[l]);
    }
    //printf("%d %d\n", p, go[p]);
    rep(i, p, go[p])
    {
        int cnt = 0, flag = 0;
        //printf("*%d\n", i);
        for (int j = i; j < i + n; j = go[j], cnt++)
        {
            //printf("(%d)\n", j);
        }
        ans = min(ans, cnt); 
    }
}
int main()
{
#ifndef ONLINE_JUDGE
    freopen("input.txt","r",stdin);
    //freopen("output.txt","w",stdout);
#endif
    scanf("%d%d", &n, &q);
    rep(i, 1, n) a[i] = read(), a[i + n] = a[i];
    rep(i, 1, n + n) sum[i] = sum[i - 1] + a[i]; 
    rep(i, 1, q)
    {
        s = read();
        solve();
        printf("%d\n", ans);
    }
#ifndef ONLINE_JUDGE
    fclose(stdin); fclose(stdout);
#endif
    return 0;
}