#pragma comment(linker, "/STACK:256000000")

#include <iostream>
#include <vector>
#include <cstdio>
#include <cmath>
#include <set>
#include <map>
#include <queue>
#include <deque>
#include <algorithm>
#include <cstring>
#include <sstream>
using namespace std;

#define forn(i, n) for (int i = 0; i < int(n); i++)
#define forv(i, v) forn(i, v.size())
#define for1(i, n) for (int i = 1; i <= int(n); i++)

#define pb push_back
#define mp make_pair
#define all(v) v.begin(), v.end() 

#define CIN_FILE "input.txt"
#define COUT_FILE "output.txt"

#define pi 3.14159265358979

typedef long long ll;
typedef long double ld;
typedef pair<int, int> pii;

#define NMAX 5005

int n;
vector<int> g[NMAX];
bool d[NMAX];
int size[NMAX];
bool ans[NMAX];
int prv[NMAX];

void dfs(int v, int p)
{
    size[v] = 1;
    prv[v] = p;

    forv(i, g[v])
    {
        int u = g[v][i];
        if (u == p) continue;
        dfs(u, v);
        size[v] += size[u];
    }
}
int main()
{   

    cin >> n;
    forn(i, n - 1)
    {
        int a, b;
        cin >> a >> b;
        --a; --b;
        g[a].pb(b);
        g[b].pb(a);
    }
    
    dfs(0, -1);

    forn(v, n)
    {
        memset(d, 0, sizeof(d));
        d[0] = true;

        forv(i, g[v])
        {
            int u = g[v][i];
            if (u == prv[v]) continue;
            for (int s = NMAX - 1; s >= 0; s--)
            {
                if (d[s]) d[s + size[u]] = true;
            }
        }

            for (int s = NMAX - 1; s >= 0; s--)
            {
                if (d[s]) d[s + n - size[v]] = true;
            }
        forn(i, NMAX) ans[i] |= d[i];
    }
    int cnt = 0;
    forn(i, n)
    {
        if (i > 0 && i < n -1 && ans[i]) cnt++;
    }

    printf("%d\n", cnt);
    forn(i, n)
    {
        if (i > 0 && i < n - 1 && ans[i])
        {
            printf("%d %d\n", i, n - 1 - i);
        }
    }
        

    return 0;
}