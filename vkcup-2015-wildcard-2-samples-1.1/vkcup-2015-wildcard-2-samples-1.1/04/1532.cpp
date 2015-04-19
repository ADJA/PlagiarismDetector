#include <cstdio>
#include <cstring>
#include <map>
#include <set>
#include <queue>
#include <vector>
#include <stack>
#include <algorithm>
#include <numeric>
#include <iostream>
#include <cassert>
#include <climits>
using namespace std;

#define rep(i, n) for (int i = 0; i < (int)n; ++i)
#define all(a) (a).begin(), (a).end()
#define iter(c) __typeof(c.begin())
#define tr(c, i) for (iter(c) i = c.begin(); i != c.end(); ++i)
#define pb push_back
#define mp make_pair

int N;
vector<int> adj[5010];
bool ans[5010], tmp[5010];

int dfs(int v, int p) {
  vector<int> cs;
  int n = 1;
  rep (i, adj[v].size()) {
    int w = adj[v][i];
    if (w == p) continue;
    int c = dfs(w, v);
    cs.pb(c);
    n += c;
  }
  cs.pb(N - 1 - accumulate(all(cs), 0));

  memset(tmp, 0, sizeof(tmp));
  tmp[0] = true;
  rep (i, cs.size()) {
    int c = cs[i];
    for (int k = N - c; k >= 0; --k) tmp[k + c] |= tmp[k];
  }
  for (int k = 0; k <= N; ++k) ans[k] |= tmp[k];

  return n;
}

int main() {
  while (1 == scanf("%d", &N)) {
    rep (i, N) adj[i].clear();
    rep (i, N - 1) {
      int a, b;
      scanf("%d%d", &a, &b);
      --a;
      --b;
      adj[a].pb(b);
      adj[b].pb(a);
    }

    memset(ans, 0, sizeof(ans));
    dfs(0, -1);
    ans[0] = ans[N - 1] = false;
    
    printf("%d\n", (int)count(ans, ans + N, true));
    rep (i, N) if (ans[i]) printf("%d %d\n", i, N - i - 1);
  }
}
