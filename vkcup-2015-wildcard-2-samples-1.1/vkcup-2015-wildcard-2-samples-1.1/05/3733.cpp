#include <iostream>
#include <cmath>
#include <vector>
#include <map>
#include <cstring>
#include <string>
#include <cstdlib>
#include <algorithm>
#include <utility>
#include <sstream>
#include <set>
#include <time.h>
#include <memory.h>
#include <queue>
#include <bitset>
#include <functional>

using namespace std;

#define all(x) (x).begin(),(x).end()
#define sz(a) ((int) (a).size())
#define pb push_back
#define SORT(x) sort(all(x))
#define UNIQUE(x) SORT(x),(x).resize(unique(all(x))-(x).begin())
#define FOR(i,a,b) for(int i = (a); i < (b); ++i)
#define FORD(i,a,b) for (int i = (a); i >= (b); --i)
#define REP(i, n) FOR(i, 0, n)

#define X first
#define Y second

typedef pair<int, int> pii;
typedef vector<int> vi;
typedef vector<pii> vpii;
typedef vector<vi> vvi;
typedef long long ll;

const double pi = acos(-1.0);

ll gcd(ll x, ll y) {
	if (x < 0) x = -x;
	if (y < 0) y = -y;
	if (x < y) swap(x, y);
	while (y) {
		ll t = y;
		y = x % y;
		x = t;
	}
	return x;
}

vi a;
int n;
long long d[128][2];

int main () {
#ifdef LocalHost
	freopen("input.txt", "r", stdin);
#endif
	string s;
	cin >> s;

	REP (i, sz (s))
		a.pb(s[i]-'A');
	n = sz(a);

	long long res = 0;
	REP (i, 2) {
		memset(d, 0, sizeof(d));
		d[0][i] = 1;		
		if (a[0] == 0 && i == 1) {
			d[1][0] = 1;
			d[1][1] = 1;
		}
		REP (j, n) REP (v, 2) {
			int k = (j+1)%n;
			if (v == 0 && a[j] == 0) d[j+1][0] += d[j][v];
			if (v == 0 && a[j] == 1 && a[k] == 0) { d[j+2][0] += d[j][v]; d[j+2][1] += d[j][v]; }
			if (v == 1 && a[j] == 1) { d[j+1][0] += d[j][v]; d[j+1][1] += d[j][v]; }
		}

		if (a[0] == 0 && i == 1)
			res += d[n+1][0];
		else
			res += d[n][i];			
	}

	cout << res << endl;
#ifdef LocalHost
	cout << "--FINISHED--" << endl;
	while (1);
#endif
	return 0;
}
/*
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
*/