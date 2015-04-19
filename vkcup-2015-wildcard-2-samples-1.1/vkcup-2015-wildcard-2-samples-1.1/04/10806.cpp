#include <iostream>
#include <cstring>
#include <vector>
#include <set>
#include <map>
#include <algorithm>
#include <iomanip>
#include <cstdio>
#include <ctime>
#include <functional>
#include <iterator>
#include <complex>
#include <queue>
#include <cassert>
#include <sstream>
#include <cstdlib>

using namespace std;

typedef long long LL;
typedef long double LD;

const int MAX_N = 5010;

int n;
vector<int> g [MAX_N];
int mark [MAX_N], can [MAX_N];
vector< pair<int, int> > ans;

int dfs(int u, int p) {
    int sz = 1;
    for (int i = 0; i < g[u].size(); i++) {
        int v = g[u][i];
        if (v == p)
            continue;

        sz += dfs(v, u);
    }

    return sz;
}

int main() {
    scanf("%d", &n);
    for(int i = 0; i < n - 1; i++) {
        int u, v;
        scanf("%d%d", &u, &v);
        u--, v--;
        g[u].push_back(v);
        g[v].push_back(u);
    }

    memset(can, -1, sizeof(can));
    for (int u = 0; u < n; u++) {
        vector<int> sz;
        for (int i = 0; i < g[u].size(); i++)
            sz.push_back(dfs(g[u][i], u));

#ifdef DEBUG
        cerr << "sizes\n";
        for (int i = 0; i < sz.size(); i++)
            cerr << sz[i] << ' ';
        cerr << '\n';
#endif

        can[0] = u;
        for (int i = 0; i < sz.size(); i++)
            for (int j = n - 1; j - sz[i] >= 0; j--)
                if (can[j - sz[i]] == u)
                    can[j] = u;

        for (int j = 1; j < n - 1; j++)
            if (can[j] == u)
                mark[j] = 1;
    }    

    for (int i = 1; i < n - 1; i++)
        if (mark[i])
            ans.push_back(make_pair(i, n - 1 - i));

    cout << ans.size() << '\n';
    for (int i = 0; i < ans.size(); i++)
        cout << ans[i].first << ' ' << ans[i].second << '\n';
        
    return 0;
}
