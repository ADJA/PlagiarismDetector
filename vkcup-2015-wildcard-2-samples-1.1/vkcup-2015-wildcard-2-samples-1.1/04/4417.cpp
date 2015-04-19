#include <iostream>
#include <iomanip>
#include <cstring>
#include <cstdio>
#include <cstdlib>
#include <cmath>
#include <cassert>
#include <ctime>
#include <algorithm>
#include <string>
#include <map>
#include <set>
#include <queue>
#include <list>
#include <stack>
#include <vector>

using namespace std;

#define forn(i, n) for(int i = 0; i < int(n); ++i)
#define ford(i, n) for(int i = int(n) - 1; i >= 0; --i)
#define sz(v) (int((v).size()))
#define all(v) (v).begin(),(v).end()
#define X first
#define Y second

typedef long long li;
typedef long double ld;
typedef pair<int, int> pt;

const int INF = int(1e9) + 7;
const ld EPS = 1e-9;
const ld PI = acosl(ld(-1.0));

const int N = 5010;

int n;
vector<int> g[N];

int cnt[N];
int cused;
int used[N];

void dfs(int v){
    cnt[v] = 1;

    forn(i, sz(g[v])){
        int u = g[v][i];
        if(used[u] == cused)
            continue;
        used[u] = cused;
        dfs(u);
        cnt[v] += cnt[u];
    }
}

bool reach[2][N];
int szd;
int d[N];

bool ans[N];

int main(){
#ifdef myproject
    freopen("input.txt", "r", stdin);
    //freopen("output.txt", "w", stdout);
#endif
    
    cin >> n;

    forn(i, n - 1){
        int x, y;
        scanf("%d %d", &x, &y);
        x--; y--;
        g[x].push_back(y);
        g[y].push_back(x);
    }

    forn(root, n){
        cused++;
        used[root] = cused;
        dfs(root);


        szd = 0;
        forn(i, sz(g[root]))
            d[szd++] = cnt[g[root][i]];

        memset(reach[0], 0, sizeof(bool)*n);
        reach[0][0] = true;

        forn(i, szd){
            memset(reach[1 - (i&1)], 0, sizeof(bool)*n);
            forn(j, n){
                if(reach[i&1][j]){
                    reach[1 - (i&1)][j] = true;
                    if(j + d[i] < n)
                        reach[1 - (i&1)][j + d[i]] = true;
                }
            }
        }

        forn(i, n)
            ans[i] = ans[i] || reach[szd&1][i];       
    }

    vector<pt> res;
    res.reserve(n);

    for(int i = 1; i < n - 1; ++i)
        if(ans[i])
            res.push_back(pt(i, n - 1 - i));

    cout << sz(res) << endl;

    forn(i, sz(res))
        printf("%d %d\n", res[i].X, res[i].Y);

    return 0;
}