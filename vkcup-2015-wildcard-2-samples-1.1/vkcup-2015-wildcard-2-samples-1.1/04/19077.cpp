#include <cstdio>
#include <cstdlib>
#include <cmath>
#include <cstring>
#include <cassert>
#include <iostream>
#include <complex>
#include <sstream>
#include <list>
#include <algorithm>
#include <vector>
#include <string>
#include <map>
#include <set>
using namespace std;
#pragma comment(linker, "/STACK:255000000")

typedef long long ll;

#define rep(i, a, b) for(i = (a); i < (b); ++i)
#define repb(i, a, b) for(i = (a) - 1; i >= (b); --i)
#define repd(i, a, b, d) for(i = (a); i < (b); i += (d))
#define repbd(i, a, b, d) for(i = (a) - 1; i >= (b); i -= (d))
#define reps(i, s) for(i = 0; (s)[i]; ++i)
#define repl(i, l) for(i = l.begin(); i != l.end(); ++i)

#define in(d, x) scanf("%"#d, &(x))
#define out(d, x) printf("%"#d, (x))

bool bfirstout = 1;
#define outf(d, x) printf(bfirstout ? "%"#d : " %"#d, (x)), bfirstout = 0
#define nl printf("\n"), bfirstout = 1

#define inf 1012345678
#define eps 1e-9

#define mp make_pair
#define sqr(x) ((x) * (x))
#define all(x) (x).begin(),(x).end()

template<class T>
inline T &maxx(T &a, T b)
{
	if(a < b) a = b;
	return a;
}

template<class T>
inline T &minn(T &a, T b)
{
	if(b < a) a = b;
	return a;
}

#ifdef XDEBUG
#define mod 23
#else
#define mod 1000000007
#endif

inline int &madd(int &a, int b)
{
	a += b;
	if(a >= mod) a -= mod;
	return a;
}

inline int &msub(int &a, int b)
{
	a -= b;
	if(a < 0) a += mod;
	return a;
}

inline int &mmult(int &a, int b)
{
	a = (ll)a * b % mod;
	return a;
}

int mdiv(ll a, ll b, ll m)
{
    a = (a % m + m) % m;
    b = (b % m + m) % m;
    if(a % b == 0) return a / b;
    return (a + m * mdiv(-a, m, b)) / b;
}

#define N 5012
#define M 1012

int n, m, q;
vector<int> A[N];
bool B[N];
pair<int, int> R[2 * N];
int X[N];
int C[N];
int D[N][N];

int dfs(int i, int p = -1)
{
	m = 0;
	int j, k;
	C[i] = 1;
	for(k = 0; k < A[i].size(); ++k)
	{
		j = A[i][k];
		if(j != p) C[i] += dfs(j, i);
	}
	return C[i];
}

int fnd(int x, int i)
{
	if(x < 0) return 0;
	int &res = D[x][i];
	if(res >= 0) return res;
	if(x == 0) return res = 1;
	if(i == m) return res = 0;
	return res = fnd(x, i + 1) || fnd(x - X[i], i + 1);
}

void dfsb(int i, int p = -1)
{
	m = 0;
	int j, k;
	X[m++] = n - C[i];
	for(k = 0; k < A[i].size(); ++k)
	{
		j = A[i][k];
		if(j != p) X[m++] = C[j];
	}
	rep(k, 0, n + 1) rep(j, 0, m + 1) D[k][j] = -1;
	rep(k, 1, n - 1) if(!B[k]) B[k] = fnd(k, 0);
	for(k = 0; k < A[i].size(); ++k)
	{
		j = A[i][k];
		if(j != p) dfsb(j, i);
	}
}

int main()
{
#ifdef XDEBUG
	freopen("e.in", "r", stdin);
#endif
	int i, j, k;
	int a, b;
	char c;

	for(; in(d, n) > 0;)
	{
		rep(i, 0, n) A[i].clear();
		rep(k, 0, n - 1)
		{
			in(d, i); in(d, j);
			--i; --j;
			A[i].push_back(j);
			A[j].push_back(i);
		}
		rep(i, 0, n) B[i] = 0;
		dfs(0);
		dfsb(0);
		int nr = 0;
		rep(i, 1, n - 1) if(B[i]) R[nr++] = mp(i, n - i - 1), R[nr++] = mp(n - i - 1, i);
		sort(R, R + nr);
		nr = unique(R, R + nr) - R;
		out(d, nr); nl;
		rep(i, 0, nr) outf(d, R[i].first), outf(d, R[i].second), nl;
	}
	return 0;
}