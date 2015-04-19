#include <bits/stdc++.h>
using namespace std;

bool f[21][32][11][11][11][11][11];
int beauty[20][32];
int numBeauty[20];
int a[5];
int b[20];
int n;
int m;
char result[5][21];

bool backtrack(int col, int prev, int a0, int a1, int a2, int a3, int a4) {
    if (a0 > a[0] || a1 > a[1] || a2 > a[2] || a3 > a[3] || a4 > a[4]) return false;
    if (a0 + (m - col + 1 - (prev >> 0 & 1)) / 2 < a[0]) return false;
    if (a1 + (m - col + 1 - (prev >> 1 & 1)) / 2 < a[1]) return false;
    if (a2 + (m - col + 1 - (prev >> 2 & 1)) / 2 < a[2]) return false;
    if (a3 + (m - col + 1 - (prev >> 3 & 1)) / 2 < a[3]) return false;
    if (a4 + (m - col + 1 - (prev >> 4 & 1)) / 2 < a[4]) return false;
    if (col == m) return true;
    if (f[col][prev][a0][a1][a2][a3][a4]) return false;
    f[col][prev][a0][a1][a2][a3][a4] = true;
    for (int i = 0; i < numBeauty[col]; ++i) {
        int mask = beauty[col][i];
        int aa0 = a0, aa1 = a1, aa2 = a2, aa3 = a3, aa4 = a4;
        if ((mask & 1) && !(prev & 1)) ++aa0;
        if ((mask & 2) && !(prev & 2)) ++aa1;
        if ((mask & 4) && !(prev & 4)) ++aa2;
        if ((mask & 8) && !(prev & 8)) ++aa3;
        if ((mask & 16) && !(prev & 16)) ++aa4;
        if (backtrack(col + 1, mask, aa0, aa1, aa2, aa3, aa4)) {
            for (int i = 0; i < 5; ++i) result[i][col] = mask & 1 << i ? '*' : '.';
            return true;
        }
    }
    return false;
}

int main() {
    #ifndef ONLINE_JUDGE
    assert(freopen("F.in", "r", stdin));
    #endif // ONLINE_JUDGE
    ios::sync_with_stdio(false);
    cin >> n >> m;
    for (int i = 0; i < n; ++i) cin >> a[i];
    for (int i = 0; i < m; ++i) cin >> b[i];
    for (int i = 0; i < m; ++i) {
        for (int mask = 0; mask < 32; ++mask) {
            int cnt = 0;
            for (int i = 0; i < 5; ++i) if ((mask & 1 << i) && (i == 0 || !(mask & 1 << (i - 1)))) ++cnt;
            if (cnt == b[i]) beauty[i][numBeauty[i]++] = mask;
        }
    }
    assert(backtrack(0, 0, 0, 0, 0, 0, 0));
    for (int i = 0; i < n; ++i) cout << result[i] << '\n';
    return 0;
}
