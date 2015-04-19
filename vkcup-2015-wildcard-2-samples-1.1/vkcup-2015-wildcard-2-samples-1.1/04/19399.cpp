#pragma comment(linker, "/stack:256000000")
#define _CRT_SECURE_NO_DEPRECATE

#include <iostream>
#include <iomanip>
#include <string>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <cmath>
#include <ctime>
#include <climits>
#include <cassert>
#include <set>
#include <map>
#include <vector>
#include <bitset>
#include <queue>
#include <stack>
#include <algorithm>
#include <functional>
#include <numeric>
#include <utility>

#define forn(i, n) for (int i = 0; i < int(n); i++)
#define forl(i, n) for (int i = 1; i <= int(n); i++)
#define ford(i, n) for (int i = int(n) - 1; i >= 0; i--)
#define fore(i, l, r) for (int i = int(l); i <= int(r); i++)
#define correct(x, y, n, m) (0 <= (x) && (x) < (n) && 0 <= (y) && (y) < (m))
#define all(a) (a).begin(), (a).end()
#define mp(x, y) make_pair((x), (y))
#define sz(a) int((a).size())
#define pb(a) push_back(a)
#define ft first
#define sc second

using namespace std;

template<typename X> inline X abs(const X& a) { return a < 0 ? -a : a; }
template<typename X> inline X sqr(const X& a) { return a * a; }
template<typename X> inline void print(const vector<X>& a, ostream& out) { out << sz(a) << endl; forn(i, sz(a)) out << a[i] << ' '; out << endl; }
template<typename X> inline void print(const vector<X>& a) { print(a, cerr); }
template<typename X> inline void print(X* a, int n, ostream& out) { out << n << endl; forn(i, n) out << a[i] << ' '; out << endl; }
template<typename X> inline void print(X* a, int n) { print(a, n, cerr); }

typedef long long li;
typedef long double ld;
typedef pair<int, int> pt;

const int INF = int(1e9);
const li INF64 = li(1e18);
const ld EPS = 1e-9, PI = 3.1415926535897932384626433832795;

const int N = 5000 + 3;

int n;
vector<int> g[N];

inline bool read()
{
	if (scanf("%d", &n) != 1)
		return false;
		
	forn(i, n - 1)
	{
		int x, y;
		assert(scanf("%d%d", &x, &y) == 2);
		x--, y--;
		
		g[x].pb(y), g[y].pb(x);
	}
	
	return true;
}

bool calced[N][3];
vector<int> z[N][3];

vector<int>& solve(int v, int p, int col)
{
	if (calced[v][col]) return z[v][col];
	calced[v][col] = true;
	
	vector<int>& res = z[v][col];
	
	if (col != 1)
	{
		vector<int> ans;
		ans.pb(0);
		ans.pb(0);
		
		forn(i, sz(g[v]))
		{
			if (g[v][i] == p) continue;
			
			vector<int>& next = solve(g[v][i], v, 0);
			vector<int> anss(sz(ans) + sz(next) - 1, 0);
			
			forn(j, sz(ans))
				forn(k, sz(next))
					anss[j + k] = max(anss[j + k], ans[j] + next[k]);
					
			ans = anss;
		}
		
		res.resize(max(sz(res), sz(ans)));
		
		forn(i, sz(ans))
			res[i] = max(res[i], ans[i]);
	}
	
	if (col != 0)
	{
		vector<int> ans;
		ans.pb(1);
		
		forn(i, sz(g[v]))
		{
			if (g[v][i] == p) continue;
			
			vector<int>& next = solve(g[v][i], v, 1);
			vector<int> anss(sz(ans) + sz(next) - 1, 0);
			
			forn(j, sz(ans))
				forn(k, sz(next))
					anss[j + k] = max(anss[j + k], ans[j] + next[k]);
					
			ans = anss;
		}
		
		res.resize(max(sz(res), sz(ans)));
		
		forn(i, sz(ans))
			res[i] = max(res[i], ans[i]);
	}
	
	{
		vector<int> ans;
		ans.pb(0);
		
		forn(i, sz(g[v]))
		{
			if (g[v][i] == p) continue;
			
			vector<int>& next = solve(g[v][i], v, 2);
			vector<int> anss(sz(ans) + sz(next) - 1, 0);
			
			forn(j, sz(ans))
				forn(k, sz(next))
					anss[j + k] = max(anss[j + k], ans[j] + next[k]);
					
			ans = anss;
		}
		
		res.resize(max(sz(res), sz(ans)));
		
		forn(i, sz(ans))
			res[i] = max(res[i], ans[i]);
	}
	
	/*cerr << v << ' ' << p << ' ' << col << endl;
	print(res);
	cerr << endl;*/
	
	return res;
}

inline void solve()
{
	vector<int>& ans = solve(0, -1, 2);
	//print(ans);
	
	int maxVal = 0;
	vector<pt> res;
	
	forl(i, sz(ans) - 1)
		if (ans[i] > 0)
		{
			int curVal = i + ans[i];
			
			if (maxVal < curVal)
				maxVal = curVal, res.clear();
				
			if (curVal == maxVal)
				res.pb(mp(i, ans[i]));
		}
		
	cout << sz(res) << endl;
	
	forn(i, sz(res))
		printf("%d %d\n", res[i].ft, res[i].sc);
}

int main()
{
#ifndef ONLINE_JUDGE
	freopen("input.txt", "rt", stdin);
	freopen("output.txt", "wt", stdout);
#endif

	assert(read());
	solve();
	
	return 0;
}
