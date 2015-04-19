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

vint adj[5050];

int pos[5500];

int Dfs(int node, int root) {
  int res = 1;
  FORIT(it, adj[node]) if (*it != root) res += Dfs(*it, node);
 // cout << node << " " << root << " " << res << endl;
  return res;
}

int knap[5200];
int ok[5200];

int main() {
  int n;
  cin >> n;
  FORN(i, n-1) {
    int a, b;
    cin >> a >> b;
    --a;
    --b;
    adj[a].PB(b);
    adj[b].PB(a);
  }
  
  FORN(i, n) {
    vint values;
    FORIT(it, adj[i]) values.PB(Dfs(*it, i));
    //cout << "END" << endl;
    FORN(i, 5200) knap[i] = 0;
    knap[0] = 1;
    FORIT(v, values) {
      for (int j = 5100; j >= 0; --j) if (knap[j]) knap[j+*v] = 1;
    }
    FORN(i, 5200) ok[i] |= knap[i];
  }
  
  vint ans;
  FORN(i, 5200) if (ok[i] && i != 0 && i != (n-1)) ans.PB(i);
  
  cout << SZ(ans) << endl;
  FORIT(it, ans) cout << *it << " " << (n-1-*it) << endl;
}
