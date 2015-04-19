#include <iostream>
#include <cstdio>
#include <cmath>
#include <algorithm>
#include <vector>
#include <map>
#include <set>
#include <bitset>
#include <queue>
#include <deque>
#include <stack>
#include <sstream>
#include <cstring>
#include <numeric>
#include <ctime>

#define re return
#define fi first
#define se second
#define mp make_pair
#define pb push_back
#define all(x) (x).begin(), (x).end()
#define sz(x) ((int) (x).size())
#define rep(i, n) for (int i = 0; i < (n); i++)
#define rrep(i, n) for (int i = (n) - 1; i >= 0; i--)
#define y0 y32479
#define y1 y95874
#define fill(x, y) memset(x, y, sizeof(x))
#define sqr(x) ((x) * (x))
#define sqrt(x) sqrt(abs(x))
#define unq(x) (x.resize(unique(all(x)) - x.begin()))
#define spc(i,n) " \n"[i == n - 1]
#define Pi 3.1415926535897932384626433832795

using namespace std;

typedef vector<int> vi;
typedef vector<vi> vvi;
typedef pair<int, int> ii;
typedef vector<ii> vii;
typedef vector<string> vs;
typedef double D;
typedef long double LD;
typedef long long ll;
typedef pair<ll, ll> pll;
typedef vector<ll> vll;

template<class T> T abs(T x) { return x > 0 ? x : -x;}
template<class T> string toString(T x) { stringstream sout; sout << x; re sout.str();}

int nextInt() { int a; scanf("%d", &a); re a; }
double nextDouble() { double a; scanf("%lf", &a); re a;}
string nextString() { string s; cin >> s; re s;}
ll nextLong() { ll x; cin >> x; re x;}

#define ni nextInt()
#define nd nextDouble()
#define ns nextString()
#define nl nextLong()

#define sii(x) scanf("%d", &x)
#define sid(x) scanf("%lf", &x)
#define sis(x) scanf("%s", x)
#define sil(x) scanf("%I64d", &x)

#define si(x) int x; scanf("%d", &x)
#define sd(x) double x; scanf("%lf", &x)
#define sl(x) ll x; scanf("%I64d", &x)

#define FILENAME ""

void initFiles()
{
#ifdef LOCAL_BOBER
    freopen("input.txt", "r", stdin);
    //freopen("output.txt", "w", stdout);
#endif
}

int m;
int n;

bool table[20][32][170000];
bool was[20][32][170000];

int a[5];
int b[20];

vi v[20];

int getcol(int mask) {
	vi v;
	rep(i, n)
		v.pb((mask >> i) & 1);

	int ans = 0;
	rep(i, sz(v) + 1)
	if (i == sz(v) || v[i] == 0)
		if (i && v[i - 1] == 1)
			ans++;
	re ans;
}

int build(int* a) {
	int ans = 0;
	rep(i, n)
		ans = ans * 11 + a[i];
	re ans;
}

void parse(int x, int* a) {
	rep(i, n) {
		a[i] = x % 11;
		x /= 11;
	}
	reverse(a, a + n);
}

int st11[10];

int matr[5][20];

bool getans(int p, int mm, int val) {
	if (p == m)
		re val == 0;
	if (was[p][mm][val])
		re table[p][mm][val];
	was[p][mm][val] = 1;

	int c[5];
	parse(val, c);
	rep(i, sz(v[p])) {
		int cm = v[p][i];
		int nval = val;
		int f = 1;
		rep(j, n) {
			if ((mm & (1 << j)) == 0)
				if (cm & (1 << j)) {
					if (c[j] == 0) {
						f = 0;
						break;
					}
					nval -= st11[n - j - 1];
				}
		}
		if (f)
			if (getans(p + 1, cm, nval)) {
//				cout << p << ' ' << cm << ' ' << mm << ' ' << nval << ' ' << val << " ok" << endl;
				rep(k, n)
					matr[k][p] = (cm >> k) & 1;

				table[p][mm][val] = 1;
				re 1;
			}
	}
	re 0;
}

void out(int p, int mm, int val) {

}

int main() {
    //cin.sync_with_stdio(0);
    //cout.sync_with_stdio(0);

	initFiles();

	st11[0] = 1;
	for (int i = 1; i < 10; i++)
		st11[i] = st11[i - 1] * 11;

	cin >> n >> m;
	rep(i, n)
		cin >> a[i];
	rep(j, m)
		cin >> b[j];

	rep(i, m)
	rep(mask, (1 << n)) {
		if (getcol(mask) == b[i])
			v[i].pb(mask);
	}

	int z = getans(0, 0, build(a));
	//cout << z << endl;

	rep(i, n) {
		rep(j, m)
			if (matr[i][j])
				cout << "*";
			else
				cout << ".";
		cout << endl;
	}

    re 0;
}
