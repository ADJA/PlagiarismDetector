#include <cstdio>
#include <cstdlib>
#include <cmath>
#include <algorithm>
#include <iostream>
#include <cstring>
#include <vector>
#include <set>
#include <map>
#include <cassert>
#include <ctime>
#include <string>

using namespace std;

#ifdef _WIN32
#define LLD "%I64d"
#else
#define LLD "%lld"
#endif

typedef long double ld;
typedef long long ll;

ll rdtsc() {
  ll tmp;
  asm("rdtsc" : "=A"(tmp));
  return tmp;
}

inline int myrand() {
  return abs((rand() << 15) ^ rand());
}

inline int rnd(int x) {
  return myrand() % x;
}

#define pb push_back
#define mp make_pair
#define eprintf(...) fprintf(stderr, __VA_ARGS__)
#define sz(x) ((int)(x).size())
#define TASKNAME "text"

const ld EPS = 1e-9;

const int maxn = (int)1e5 + 10;
const int INF = (int)1e9 + maxn;
int a[maxn];

int getLeft(int l, int r, int cnt) {
  int bestl = -(cnt / 2);
  bestl = max(bestl, l + 1);
  bestl = min(bestl, r - cnt);
  return bestl;
}

bool solve() {
  int n, k;
  if (scanf("%d%d", &n, &k) < 2) {
    return 0;
  }

  for (int i = 0; i < n; ++i) {
    if (scanf("%d", &a[i]) < 1) {
      scanf(" ?");
      a[i] = INF;
    } else {
      assert(abs(a[i]) < INF);
    }
  }

  for (int r = 0; r < n && r < k; ++r) {
    int cnt = 0, first = -INF;
    for (int pos = r; pos < n + k; pos += k) {
      int apos = (pos < n) ? a[pos] : INF - 1;
      if (apos == INF) {
        ++cnt;
        continue;
      }
      int last = apos;
      if (first + cnt + 1 > last) {
        printf("Incorrect sequence\n");
        return 1;
      }
      int left = getLeft(first, last, cnt);
      for (int x = pos - cnt * k, iter = 0; x < pos; x += k, ++iter) {
        a[x] = left + iter;
      }
      first = last;
      cnt = 0;
    }
  }

  for (int i = 0; i < n; ++i) {
    printf("%d%c", a[i], " \n"[i == n - 1]);
  }
  return 1;
}

int main() {
  srand(rdtsc());
#ifdef DEBUG
  freopen(TASKNAME".out", "w", stdout);
  freopen(TASKNAME".in", "r", stdin);
#endif

  while (1) {
    if (!solve())
      break;
#ifdef DEBUG
    eprintf("%.18lf\n", (double)clock() / CLOCKS_PER_SEC);
#endif
  }
  return 0;
}
