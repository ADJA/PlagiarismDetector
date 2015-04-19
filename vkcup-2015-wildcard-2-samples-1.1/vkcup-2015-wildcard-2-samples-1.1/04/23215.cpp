/* 
 * File:   main.cpp
 * Author: contest
 *
 * Created on July 15, 2012, 10:53 AM
 */

#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <cmath>
#include <climits>
#include <cctype>
#include <iostream>
#include <iomanip>
#include <sstream>
#include <vector>
#include <string>
#include <queue>
#include <stack>
#include <set>
#include <map>
#include <utility>
#include <algorithm>
#include <functional>
#include <numeric>

using namespace std;

int n, cnt[5010], par[5010];
vector<int> g[5010];
set<int> ans;
bool can[5010];

int dfs(int v, int p) {
    par[v] = p;
    cnt[v] = 1;
    for (vector<int>::iterator i = g[v].begin(); i != g[v].end(); ++i) {
        if (*i != p) {
            cnt[v] += dfs(*i, v);
        }
    }
    if (cnt[v] < n - 1) {
        ans.insert(cnt[v]);
        ans.insert(n - 1 - cnt[v]);
    }
    return cnt[v];
}

bool solve() {
    if (scanf("%d", &n) == EOF)
        return false;
    for (int i = 0; i < n; ++i)
        g[i].clear();
    for (int i = 1; i < n; ++i) {
        int a, b;
        scanf("%d%d", &a, &b);
        g[a - 1].push_back(b - 1);
        g[b - 1].push_back(a - 1);
    }
    memset(cnt, 0, sizeof(cnt));
    ans.clear();
    dfs(0, -1);
    for (int i = 0; i < n; ++i) {
        memset(can, 0, sizeof(can));
        can[0] = true;
        for (vector<int>::iterator j = g[i].begin(); j != g[i].end(); ++j) {
            for (int k = n - 1; k >= 0; --k) {
                if (can[k]) {
                    can[k + (*j == par[i] ? n - cnt[i] : cnt[*j])] = true;
                }
            }
        }
        for (int k = 1; k < n - 1; ++k) {
            if (can[k])
                ans.insert(k);
        }
    }
    printf("%d\n", ans.size());
    for (set<int>::iterator i = ans.begin(); i != ans.end(); ++i)
        printf("%d %d\n", *i, n - *i - 1);
    return true;
}

int main() {
    //freopen("E.in", "r", stdin);
    while (solve());
    return 0;
}
