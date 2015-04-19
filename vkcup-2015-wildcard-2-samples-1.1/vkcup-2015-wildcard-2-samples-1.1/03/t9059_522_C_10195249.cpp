#undef NDEBUG
#ifdef SU2_PROJ
#define _GLIBCXX_DEBUG
#endif

#include <iostream>
#include <iomanip>
#include <sstream>
#include <fstream>
#include <string>
#include <cstdlib>
#include <cstdio>
#include <climits>
#include <cstring>
#include <cassert>
#include <ctime>
#include <cmath>
#include <vector>
#include <queue>
#include <stack>
#include <list>
#include <set>
#include <map>
#include <bitset>
#include <algorithm>
#include <utility>
#include <numeric>
#include <functional>

#define forn(i, n) for (int i = 0; i < int(n); i++)
#define forl(i, n) for (int i = 1; i <= int(n); i++)
#define ford(i, n) for (int i = int(n) - 1; i >= 0; i--)
#define fore(i, l, r) for (int i = int(l); i <= int(r); i++)
#define correct(x, y, n, m) (0 <= (x) && (x) < (n) && 0 <= (y) && (y) < (m))
#define all(a) (a).begin(), (a).end()
#define sz(a) int((a).size())
#define pb(a) push_back(a)
#define mp(x, y) make_pair((x), (y))
#define ft first
#define sc second
#define x first
#define y second
#define eprintf(...) fprintf(stderr, __VA_ARGS__)

using namespace std;

typedef long long li;
typedef long double ld;
typedef pair<int, int> pt;

template<typename X> inline X abs(const X& a) { return a < 0? -a: a; }
template<typename X> inline X sqr(const X& a) { return a * a; }

const int INF = int(1e9);
const li INF64 = li(1e18);
const ld EPS = 1e-9, PI = 3.1415926535897932384626433832795;

const int N = 100 * 1000 + 3;

int n, m;
int a[N];
int x[N], y[N];

inline bool read()
{
	if (scanf("%d%d", &n, &m) != 2) return false;
	forn(i, m) scanf("%d", &a[i]);
	n--;
	forn(i, n)
	{
		scanf("%d%d", &x[i], &y[i]);
		x[i]--;
	}
	return true;
}

bool ans[N];
int last[N];

inline void solve()
{
	forn(i, m) ans[i] = false;
	
	forn(i, m) last[i] = -1;
	forn(i, n) if (x[i] != -1) last[x[i]] = i;

	set<pt> z;
	forn(i, m) if (last[i] == -1) z.insert(mp(a[i], i));

	int c = 0;
	bool is = false;
	set<int> mdied;
	forn(i, n)
	{
		if (y[i] == 1 && !is)
		{
			int cur = INF;
			for (set<int>::iterator it = mdied.begin(); it != mdied.end(); it++)
				cur = min(cur, a[*it]);
			assert(cur != INF);
			c -= cur;
			assert(c >= 0);
			is = true;
		}

		if (x[i] == -1)
			c++;
		else
		{
			a[x[i]]--;
			if (last[x[i]] == i) z.insert(mp(a[x[i]], x[i]));
		}

		while (!z.empty() && z.begin()->x <= c)
		{
			int idx = z.begin()->y;
			ans[idx] = true;
			mdied.insert(idx);
			z.erase(z.begin());
		}
	}

	forn(i, m) if (a[i] <= c) ans[i] = true;
	forn(i, m) putchar(ans[i] ? 'Y' : 'N');
	puts("");
}

int main()
{
#ifdef SU2_PROJ
    assert(freopen("input.txt", "rt", stdin));
    assert(freopen("output.txt", "wt", stdout));
#endif
    
    cout << setprecision(10) << fixed;
    cerr << setprecision(5) << fixed;
    
	int tt;
	cin >> tt;
    while (read())
	{
		solve();
		if (--tt <= 0) break;
	}
	
    return 0;
}
