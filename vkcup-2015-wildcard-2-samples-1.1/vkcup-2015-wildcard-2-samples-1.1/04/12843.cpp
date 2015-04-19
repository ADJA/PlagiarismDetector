#include <algorithm>
#include <iostream>
#include <cstdlib>
#include <iomanip>
#include <cstring>
#include <vector>
#include <cstdio>
#include <cmath>
#include <map>
using namespace std;

int n;
vector <int> e[5001];
bool ans[5001];

int sz[5001];

void setUp(bool *t, int v)
{
    for(int i = n; i >= v; i--)
        if(t[i-v])
            t[i] = true;
}

void dfs(int cur, int father)
{
    bool t[5001];
    sz[cur] = 1;
    memset(t, false, sizeof(t));
    t[0] = true;
    for(int i = 0; i < e[cur].size(); i++)
    {
        int nextNode = e[cur][i];
        if(nextNode == father)
            continue;
        dfs(nextNode, cur);
        sz[cur] += sz[nextNode];
        setUp(t, sz[nextNode]);
    }
    setUp(t, n - sz[cur]);
    for(int i = 1; i <= n; i++)
        if(t[i])
            ans[i] = true;
}

int MAIN()
{
    while(cin >> n)
    {
        for(int i = 1; i <= n; i++)
            e[i].clear();
        for(int i = 1; i < n; i++)
        {
            int a, b;
            cin >> a >> b;
            e[a].push_back(b);
            e[b].push_back(a);
        }
        memset(ans, 0, sizeof(ans));
        dfs(1, -1);
        int cnt = 0;
        for(int i = 1; i < n-1; i++)
            if(ans[i])
                cnt ++;
        cout << cnt << endl;
        for(int i = 1; i < n-1; i++)
            if(ans[i])
                cout << i << " " << n-1-i << endl;
    }
    return 0;;
}

int main()
{
    ios :: sync_with_stdio(false);
    #ifdef LOCAL
        freopen("in.txt", "r", stdin);
        freopen("out.txt", "w", stdout);
    #endif
    cout << fixed << setprecision(16);
    return MAIN();
}

