// dolphinigle
// 15 JUL 2012

#include <cstdio>
#include <cstdlib>
#include <iostream>
#include <algorithm>
#include <vector>
#include <deque>
#include <list>
#include <stack>
#include <queue>
#include <ctime>
#include <cmath>
#include <cassert>
#include <cstring>
#include <set>
#include <map>

#define FORN(X,Y) for (int X = 0; X < (Y); ++X)
#define REP(X,Y,Z) for (int X = (Y); X < (Z); ++X)
#define FORIT(X,Y) for (typeof((Y).begin()) X = (Y).begin(); X != (Y).end(); ++X)
#define SZ(X) ((int)(X).size())
#define A first
#define B second
#define MX(X,Y) X = max((X),(Y))
#define MN(X,Y) X = min((X),(Y))
#define MP make_pair
#define PB push_back

using namespace std;

typedef long long ll;
typedef double db;
typedef vector<int> vint;

typedef pair<db, db> Point;
typedef pair<Point, Point> Segment;
typedef vector<Point> Polygon;

ll Gcd(ll a, ll b) {
  if (a < 0LL || b < 0LL) return Gcd(abs(a), abs(b));
  if (b == 0) return a;
  return Gcd(b, a % b);
}

ll Power(ll num, ll ex, ll modu) {
  if (ex == 0LL) return 1LL % modu;
  if (ex % 2 == 0LL) {
    ll base = Power(num, ex/2, modu);
    return (base * base) % modu;
  }
  return (Power(num, ex-1, modu) * num) % modu;
}

ll Inverse(ll num, ll modu) {
  return Power(num, modu-2LL, modu);
}

void Answer(ll a) {
  cout << a << endl;
  exit(0);
}

ll dp[2][2][102];
int kod[204];

int main() {
  string s;
  cin >> s;
  int n = SZ(s);
  FORN(i, n) kod[i] = s[i] - 'A';
  dp[0][0][0] = 1;
  dp[1][1][0] = 1;
  kod[n] = kod[0];
  ++n;
  REP(i, 1, n) {
    FORN(j, 2) FORN(k, 2) {
      if (k == kod[i-1] || k == 1) {
        // freedom
        // try stay same
        if (!(k == 0 && kod[i] == 1))
        dp[j][kod[i]][i] += dp[j][k][i-1];
        
        if (kod[i] == 1) {
          dp[j][0][i] += dp[j][k][i-1];
        }
      } else {
        if (kod[i] == 1) continue;
        dp[j][1][i] += dp[j][k][i-1];
      }
    }
  }
  ll res = dp[0][0][n-1] + dp[1][1][n-1];
  cout << res << endl;
}
