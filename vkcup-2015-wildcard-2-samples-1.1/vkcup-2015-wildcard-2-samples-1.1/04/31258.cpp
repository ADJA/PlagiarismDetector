#include <cstdio>
#include <cstdlib>
#include <algorithm>
#include <cmath>
#include <cassert>
#include <cstring>
#include <string>
#include <vector>
#include <ctime>
#include <set>
#include <map>
#include <ctime>

using namespace std;

typedef pair<int, int> pii;
typedef long long ll;
typedef vector<int> vi;
typedef vector<vi> vvi;
typedef vector<ll> vll;
typedef vector<vll> vvll;
typedef vector<bool> vb;
typedef vector<vb> vvb;

#ifdef WIN32
  #define LLD "%I64d"
#else
  #define LLD "%lld"
#endif

#define eprintf(...) fprintf(stderr, __VA_ARGS__)
#define mp make_pair
#define pb push_back
#define sz(x) ((int)(x).size())
#define TASKNAME "text"
#define INF ((int)1e9)
#define EPS (1e-9)

vvi es;
vb ans, used;
int n;
vi d;

void dfs0(int v) {
	used[v] = 1;
	d[v] = 1;
	for (int it = 0; it < sz(es[v]); it++) {
		int u = es[v][it];
		if (used[u])
			continue;
		dfs0(u);
		d[v] += d[u];
	}
}

const int maxn = 5000;
#define count mcount
int count[maxn];

void dfs(int v, int upcnt) {
	used[v] = 1;
	for (int it = 0; it < sz(es[v]); it++) {
		int u = es[v][it];
		if (used[u])
			continue;
		dfs(u, upcnt + d[v] - d[u]);
	}
	
	memset(count, 0, sizeof(count));
	count[0] = 1;
	for (int it = 0; it < sz(es[v]); it++) {
		int u = es[v][it];
		int now = d[u] > d[v] ? upcnt : d[u];
		for (int i = n - 1; i >= 0; i--)
			if (count[i] && i + now < n)
				count[i + now] = 1;
	}
	
	for (int i = 0; i < n; i++)
		if (count[i])
			ans[i] = 1;
}

int main() {
	{
		ll tmp;
		asm("rdtsc" : "=A"(tmp));
		srand(tmp);
	}
	#ifdef DEBUG
		freopen(TASKNAME".in", "r", stdin);
		freopen(TASKNAME".out", "w", stdout);
	#endif
	
	while (scanf("%d", &n) >= 1) {
		es = vvi(n);
		for (int i = 0; i < n - 1; i++) {
			int s, t;
			scanf("%d%d", &s, &t);
			--s, --t;
			es[s].pb(t), es[t].pb(s);
		}
		
		
		d = vi(n, 1);
		used = vb(n, 0);
		dfs0(0);
		
		used = ans = vb(n, 0);
		dfs(0, 0);
		
		vector<pii> res;
		for (int i = 1; i < n - 1; i++)
			if (ans[i])
				res.pb(mp(i, n - i - 1));
		int m = sz(res);
		printf("%d\n", m);
		for (int i = 0; i < m; i++)
			printf("%d %d\n", res[i].first, res[i].second);
		//break;
	}
	return 0;
}
