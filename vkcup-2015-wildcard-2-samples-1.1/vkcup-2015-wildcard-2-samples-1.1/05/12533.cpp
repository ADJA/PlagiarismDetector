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

#define N 1012
#define M 1012

int n, m, q;
int A[N];
char S[N];
ll D[N][2][2];

ll fnd(int i, int p, int f)
{
	ll &res = D[i][p][f];
	if(res >= 0) return res;
	res = 0;
	if(i == n)
	{
		if(p == 0 && S[i - 1] == 'B') res += f == 1 && S[0] == 'A';
		else if(p == 0) res += f == 0;
		else res += f == 0 || S[0] == 'B';
		return res;
	}
	if(p) return res = fnd(i + 1, 0, f) + (S[i] == 'B' ? fnd(i + 1, 1, f) : 0);
	else
	{
		if(S[i - 1] == 'A') return res = fnd(i + 1, 0, f);
		if(S[i - 1] == 'B' && S[i] == 'A') return res = fnd(i + 1, 1, f);
		return res;
	}
}

int main()
{
#ifdef XDEBUG
	freopen("in.txt", "r", stdin);
#endif
	int i, j, k;
	int a, b;
	char c;

	for(; in(s, S) > 0;)
	{
		n = strlen(S);
		rep(i, 0, n + 1) rep(j, 0, 2) rep(k, 0, 2) D[i][j][k] = -1;
		ll res = fnd(1, 0, 0) + fnd(1, 1, 1);		
		out(I64d, res); nl;
	}
	return 0;
}