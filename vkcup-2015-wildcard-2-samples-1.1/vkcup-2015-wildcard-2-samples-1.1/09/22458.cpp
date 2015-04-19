#undef NDEBUG
#ifdef SU2_PROJ
#define _GLIBCXX_DEBUG
#endif

#include <bits/stdc++.h>

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

const int N = 5 + 1, M = 20 + 1;

int n, m;
int a[N], b[M];

bool gen() {
	n = 5, m = 20;
	forn(i, n) a[i] = rand() % 7;
	forn(i, m) b[i] = rand() % 3;
	return true;
}

inline bool read()
{
	//return gen();
	if (!(cin >> n >> m)) return false;
	forn(i, n) assert(scanf("%d", &a[i]) == 1);
	forn(i, m) assert(scanf("%d", &b[i]) == 1);
	return true;
}

int deg[N];

int get(int mask, int i) { return mask / deg[i] % 10; }
int _set(int mask, int i, int v) { return mask - (get(mask, i) - v) * deg[i]; }

const int M1 = 32 + 2, M2 = int(1e5) + 2;

vector<int> z[M];
bool used[M1][M][M2];
int ans[M];
int c[M2][N];

bool dfs(int msk1, int j, int msk2) {
	//cerr << msk1 << ' ' << j << ' ' << msk2 << endl;
	if (j == m) {
		if (msk2 != 0) return false;
		forn(i, n)
		{
			forn(j, m)
				putchar((ans[j] & (1 << i)) ? '*' : '.');
			puts("");
		}
		return true;
	}
	
	if (used[msk1][j][msk2]) return false;
	used[msk1][j][msk2] = true;

	int* cc = c[msk2];
	//forn(i, n) cerr << cc[i] << ' '; cerr << endl;
	forn(k, sz(z[j])) {
		int nmsk1 = z[j][k], nmsk2 = msk2;
		bool bad = false;
		forn(i, n)
			if (!(msk1 & (1 << i)) && (nmsk1 & (1 << i))) {
				if (cc[i] == 0)  {
					bad = true;
					break;
				}
				nmsk2 -= deg[i];
			}
		ans[j] = nmsk1;
		if (!bad && dfs(nmsk1, j + 1, nmsk2)) return true;
	}

	return false;
}

inline void solve()
{
	deg[0] = 1; forl(i, N - 1) deg[i] = deg[i - 1] * 10;
	memset(used, 0, sizeof(used));

	forn(i, M2) forn(j, n) c[i][j] = get(i, j);

	forn(i, M) z[i].clear();
	forn(k, m) {
		forn(mask, (1 << n)) {
			int cnt = 0;
			for (int i = 0, j = 0; i < n; i = j) {
				if (!(mask & (1 << j)))
					j++;
				else {
					while (j < n && (mask & (1 << j))) j++;
					cnt++;
				}
			}
			if (cnt == b[k]) z[k].pb(mask);
		}
	}

	/*forn(i, m) {
		forn(j, sz(z[i])) cerr << z[i][j] << ' ';
		cerr << endl;
	}*/

	int mask = 0;
	forn(i, n) mask = _set(mask, i, a[i]);
	assert(dfs(0, 0, mask));
}

int main()
{
#ifdef SU2_PROJ
    assert(freopen("input.txt", "rt", stdin));
    assert(freopen("output.txt", "wt", stdout));
#endif
    
    cout << setprecision(10) << fixed;
    cerr << setprecision(5) << fixed;

    while (read())
	{
		solve();
		break;
	}
	
    return 0;
}
