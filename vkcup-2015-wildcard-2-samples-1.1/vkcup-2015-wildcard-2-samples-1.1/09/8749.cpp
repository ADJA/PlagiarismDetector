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

long long rdtsc() {
  long long tmp;
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

const int INF = (int)1e9 + 1;
const ld EPS = 1e-9;

void precalc() {
}

const int maxn = 5, maxm = 20;
int n, m;
int rows[maxn], cols[maxm];

bool read() {
  if (scanf("%d%d", &n, &m) < 2) {
    return 0;
  }
  for (int i = 0; i < n; ++i) {
    scanf("%d", &rows[i]);
  }
  for (int i = 0; i < m; ++i) {
    scanf("%d", &cols[i]);
  }
  return 1;
}

const int maxcnt = (int) 52e5;

bool d[maxcnt], nd[maxcnt];
int dans[maxcnt][maxn], ndans[maxcnt][maxn];

int coef[maxn];

int getRowValue(int code, int r) {
  code >>= n;
  for (int i = n - 1; i > r; --i) {
    code /= rows[i] + 1;
  }
  return code % (rows[r] + 1);
}

void solve() {
  int cnt = 1;
  for (int i = 0; i < n; ++i) {
    cnt *= rows[i] + 1;
  }
  cnt <<= n;

  memset(d, 0, sizeof(d));
  memset(nd, 0, sizeof(nd));
  d[0] = 1;
  for (int i = 0; i < n; ++i) {
    dans[0][i] = 0;
  }

  coef[n - 1] = 1;
  for (int i = n - 2; i >= 0; --i) {
    coef[i] = coef[i + 1] * (rows[i + 1] + 1);
  }

  for (int c = 0; c < m; ++c) {
    for (int r = 0; r < n; ++r) {
      for (int code = 0; code < cnt; ++code) {
        if (!d[code]) {
          continue;
        }

        int mask = (code & ((1 << n) - 1));
        for (int col = 0; col < 2; ++col) {
          int ncode = code;
          if (col != ((mask >> r) & 1)) {
            ncode ^= (1 << r);
            if (col == 1) {
              if (getRowValue(code, r) == rows[r]) {
                continue;
              }
              ncode += (coef[r] << n);
            }
          }
          assert(ncode < cnt);
          if (!nd[ncode]) {
            nd[ncode] = 1;
            memcpy(ndans[ncode], dans[code], sizeof(dans[code]));
            ndans[ncode][r] ^= (col << c);
          }
        }
      }

      for (int code = 0; code < cnt; ++code) {
        d[code] = nd[code];
        if (d[code]) {
          nd[code] = 0;
          memcpy(dans[code], ndans[code], sizeof(dans[code]));
        }
      }
    }
    for (int code = 0; code < cnt; ++code) {
      if (!d[code]) {
        continue;
      }
      int last = 0;
      int group = 0;
      for (int i = 0; i < n; ++i) {
        int x = ((dans[code][i] >> c) & 1);
        if (x && !last) {
          ++group;
        }
        last = x;
      }
      if (group != cols[c]) {
        d[code] = 0;
      }
    }
  }

  for (int code = cnt - 1; code >= cnt - (1 << n); --code) {
    if (!d[code]) {
      continue;
    }
    for (int i = 0; i < n; ++i) {
      for (int j = 0; j < m; ++j) {
        printf("%c", ((dans[code][i] >> j) & 1) ? '*' : '.');
      }
      printf("\n");
    }
    return;
  }
  assert(0);
}

int main() {
  srand(rdtsc());
#ifdef DEBUG
  freopen(TASKNAME".out", "w", stdout);
  assert(freopen(TASKNAME".in", "r", stdin));
#endif

  precalc();
  while (1) {
    if (!read()) {
      break;
    }
    solve();
#ifdef DEBUG
    eprintf("%.18lf\n", (double)clock() / CLOCKS_PER_SEC);
#endif
  }
  return 0;
}
