#include <time.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include <map>
#include <vector>
#include <sstream>
#include <iostream>

using namespace std;

// Template begin

#ifndef ONLINE_JUDGE
    #define READ freopen("in", "r", stdin)
    #define WRITE freopen("out", "w", stdout)
#else
    #define READ
    #define WRITE
#endif

#define int64 long long
#define uint64 unsigned long long

#define S(x) (x).size()
#define L(x) (x).length()
#define PB(x) push_back(x)
#define MP(a, b) make_pair(a, b)
#define PII pair<int, int>
#define PSI pair<string, int>
#define PIS pair<int, string>
#define PSS pair<string, string>

template<typename T>inline void checkMax(T& a, const T b) {if (a < b) a = b;}
template<typename T>inline void checkMin(T& a, const T b) {if (b < a) a = b;}

#define setv(a, v) memset(a, v, sizeof(a))

#define rep(i, n) for (int (i) = 0; (i) < (n); ++(i))
#define repD(i, n) for (int (i) = (n) - 1; (i) >= 0; --(i))

#define range(i, l, r) for (int (i) = (l); (i) < (r); ++(i))
#define rangeD(i, l, r) for (int (i) = (r) - 1; (i) >= (l); --(i))

#define all(c) (c).begin(), (c).end()

// Template end

const int N = 5000 + 128;

int n;
vector<int> g[N];

int b[N][2];

int bN;
int bs[N];

bool readData() {
    cin >> n;
    rep (i, n) {
        g[i].clear();
    }
    rep (i, n - 1) {
        int u, v;
        scanf("%d %d", &u, &v);
        --u;
        --v;
        g[u].PB(v);
        g[v].PB(u);
    }

    return true;
}

int cnt;
void dfs(int u, int pre) {
    ++cnt;
    rep (i, S(g[u])) {
        int v = g[u][i];
        if (v == pre) {
            continue;
        }
        dfs(v, u);
    }
}

bool can[N];

int aN;
int a[N];

void go() {
    setv(can, false);
    can[0] = true;
    rep (j, aN) {
        for (int i = n; i >= a[j]; --i) {
            if (can[i - a[j]])
                can[i] = true;
        }
    }
}

bool blue[N];

void solve() {
    setv(blue, false);
    rep (u, n) {
        aN = 0;
        rep (i, S(g[u])) {
            int v = g[u][i];
            cnt = 0;
            dfs(v, u);
            a[aN++] = cnt;
        }

        go();
        rep (i, n) {
            if (can[i]) {
                blue[i] = true;
            }
        }
    }

    bN = 0;
    for (int i = 1; i < n - 1; ++i) {
        if (blue[i]) {
            bs[bN++] = i;
        }
    }

    cout << bN << endl;
    rep (i, bN) {
        printf("%d %d\n", bs[i], n - 1 - bs[i]);
    }
}

bool hasNext() {
    char c;
    if (EOF == scanf(" %c", &c)) {
        return false;
    }
    ungetc(c, stdin);
    return true;
}

void runWithoutCaseT() {
    while (hasNext()) {
        readData();
        solve();
    }
}

int main() {
    READ;
    //WRITE;

    // runWithCaseT();
    runWithoutCaseT();

    return 0;
}
