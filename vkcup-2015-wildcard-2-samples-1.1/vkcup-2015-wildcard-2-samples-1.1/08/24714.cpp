#include <list>
#include <map>
#include <set>
#include <deque>
#include <stack>
#include <queue>
#include <algorithm>
#include <sstream>
#include <iostream>
#include <iomanip>
#include <cstdio>
#include <cmath>
#include <cstdlib>
#include <memory.h>
#include <ctime>
#include <bitset>
#include <unordered_set>
#include <unordered_map>

using namespace std;

#define ABS(a) ((a>0)?a:-(a))
#define MIN(a,b) ((a<b)?(a):(b))
#define MAX(a,b) ((a<b)?(b):(a))
#define FOR(i,a,n) for (int i=(a);i<(n);++i)
#define FI(i,n) for (int i=0; i<(n); ++i)
#define pnt pair <int, int>
#define mp make_pair
#define PI 3.1415926535897
#define MEMS(a,b) memset(a,b,sizeof(a))
#define LL long long
#define U unsigned

struct vertex
{
	int min1, max1;
	vertex()
	{
		min1 = max1 = 0;
	}
};

vertex t[800100];
int add[800100];

inline void push(int v, int L, int R)
{
	t[v].min1 += add[v];
	t[v].max1 += add[v];
	if (L != R)
	{
		add[v + v] += add[v];
		add[v + v + 1] += add[v];
	}
	add[v] = 0;
}

inline void recalc(int v, int L, int R)
{
	if (L == R)
		return;
	t[v].max1 = MAX(t[v + v].max1+add[v+v], t[v + v + 1].max1+add[v+v+1]);
	t[v].min1 = MIN(t[v + v].min1 + add[v + v], t[v + v + 1].min1 + add[v + v + 1]);
}

void addTo(int v, int l, int r, int L, int R, int val)
{
	push(v,L,R);
	if ((l == L) && (r == R))
	{
		add[v] += val;
		return;
	}
	int m = (L + R) / 2;
	if (r <= m)
		addTo(v + v, l, r, L, m, val);
	else
	if (l > m)
		addTo(v + v + 1, l, r, m + 1, R, val);
	else
	{
		addTo(v + v, l, m, L, m, val);
		addTo(v + v + 1, m + 1, r, m + 1, R, val);
	}
	recalc(v,L,R);
}

set<LL> dist;

int a[200100];
int n, m;
vector<pnt > all;
int k;

inline void solve(int st, int dir)
{
	all.clear();
	int have = m-1;
	int v = st;
	int fi = 1;
	LL now = 0;
	while (have > 0)
	{
		if (dir == 1)
		{
			int ne = MIN(n, v + have);
			int l = v;
			if (!fi)
				l++;
			int r = ne;
			addTo(1, l, r, 1, k, -1);
			now += a[ne-1] - a[v-1];
			have -= (ne - v);
			v = ne;
			all.push_back(mp(l, r));
		}
		else
		{
			int ne = MAX(1, v - have);
			int l = ne;
			int r = v;
			if (!fi)
				r--;
			addTo(1, l, r, 1, k, -1);
			now += a[v-1] - a[ne-1];
			have -= (v - ne);
			v = ne;
			all.push_back(mp(l, r));
		}
		fi = 0;
		dir ^= 1;
	}
	push(1, 1, k);
	vertex res = t[1];
	if ((res.max1 == 0) && (res.min1 == 0))
	{
		dist.insert(now);
	}
	FOR(i, 0, all.size())
		addTo(1, all[i].first, all[i].second, 1, k, 1);
}

int main()
{
#ifdef Fcdkbear
	freopen("in.txt", "r", stdin);
	//freopen("in.txt", "w", stdout);
	double beg = clock();
#endif

	scanf("%d", &n);
	FOR(i, 0, n)
		scanf("%d", &a[i]);
	k = 1;
	while (k < n)
		k += k;
	scanf("%d", &m);
	FOR(i, 0, m)
	{
		int v;
		scanf("%d", &v);
		addTo(1, v, v, 1, k, 1);
	}
	if (m == 1)
	{
		printf("0\n");
		return 0;
	}
	FOR(i, 0, n)
	{
		solve(i + 1, 0);
		solve(i + 1, 1);
	}
	if (dist.size() == 0)
		throw;
	LL res = -1;
	if (dist.size() == 1)
	{
		res = *dist.begin();
	}
	cout << res << endl;

#ifdef Fcdkbear
	double end = clock();
	fprintf(stderr, "*** Total time = %.3lf ***\n", (end - beg) / CLOCKS_PER_SEC);
#endif
	return 0;
}