#include <iostream>
#include <cstdlib>
#include <algorithm>
#include <cstring>
#include <vector>
#define MAXN 5
#define MAXM 21
#define MAX 161051

using namespace std;

int n,m,a[MAXN],b[MAXM];
short dp[MAXM][MAX][1 << MAXN];
vector<int> c[4];
char ans[MAXN][MAXM];

int cont(int x) {
    int res = 0, prev = 0;
    while (x) {
        if (x & 1)
            if (!prev) res++;
        prev = x & 1;
        x >>= 1;
    }
    return res;
}

int trans(int x, int y) {
    int res = 0;
    for (int i = 0; i < 5; i++) {
        res *= 11;
        if (((y>>i) & 1) && !((x>>i) & 1)) res++;
    }
    return res;
}

int main() {
    cin >> n >> m;
    for (int i = 0; i < n; i++) cin >> a[i];
    for (int i = 1; i <= m; i++) cin >> b[i];
    int aa = 0;
    for (int i = 0; i < 5; i++) aa = aa * 11 + a[i];
    for (int i = 0; i < 32; i++)
        c[cont(i)].push_back(i);
    memset(dp,-1,sizeof(dp));
    dp[0][0][0] = 0;
    for (int i = 0; i < m; i++) {
        for (int j = 0; j <= aa; j++) {
            for (auto x : c[b[i]]) {
                if (dp[i][j][x] == -1) continue;
                for (auto y : c[b[i+1]]) {
                    int t = trans(x,y);
                    dp[i + 1][j + t][y] = x;
                }
            }
        }
    }
    int x;
    for (x = 0; x < 32; x++)
        if (dp[m][aa][x] != -1) break;
    for (int i = m, j = aa; i > 0; i--) {
        for (int k = 0; k < 5; k++) {
            if ((x>>k) & 1) ans[k][i-1] = '*';
            else ans[k][i-1] = '.';
        }
        int y = dp[i][j][x];
        int t = trans(y,x);
        j -= t;
        x = y;
    }
    for (int i = 0; i < n; i++) cout << ans[i] << '\n';
}
