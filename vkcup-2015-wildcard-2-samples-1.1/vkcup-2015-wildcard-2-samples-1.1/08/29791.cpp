#include <bits/stdc++.h>
using namespace std;
int a[200005];
int b[200005];
int dist[200005];
int n, x, m;
long long sim(int pos, int dir) {
  long long sum = 0;
  for (int i = 0; i < m - 1; i++) {
    if (b[pos] == 0) return -1;
    b[pos]--;
    if (pos == 1) dir = 1;
    if (pos == n) dir = -1;
    if (dir == 1) {
      sum += dist[pos];
      pos++;
    } else {
      sum += dist[pos - 1];
      pos--;
    }
  }
  if (b[pos] != 1) return -1;
  return sum;
}
int main() {
  bool equildistant = true;
  long long total = 0;
  int last;
  scanf("%d %d", &n, &last);
  for (int i = 1; i < n; i++) {
    scanf("%d", &x);
    dist[i] = x - last;
    last = x;
    if (dist[i] != dist[1]) {
      equildistant = false;
    }
    total += dist[i];
  }
  scanf("%d", &m);
  for (int i = 0; i < m; i++) {
    scanf("%d", &x);
    a[x]++;
  }
  if (a[1] == a[n] && n > 2) {
    bool ok = true;
    for (int i = 2; i <= n - 1; i++) {
      if (a[i] != 2 * a[1]) {
        ok = false;
        break;
      }
    }
    if (ok) {
      if (m == 1) {
        cout << 0;
      } else if (equildistant) {
        cout << total * a[2] - dist[1];
      } else {
        cout << -1;
      }
      return 0;
    }
  }
  long long ans = -1;
  for (int i = 2; i <= n - 1; i++) {
    if (a[i] > a[i - 1]) {
      memcpy(b, a, sizeof a);
      ans = max(ans, sim(i, 1));
    }
    if (a[i] > a[i + 1]) {
      memcpy(b, a, sizeof a);
      ans = max(ans, sim(i, -1));
    }
  }
  memcpy(b, a, sizeof a);
  ans = max(ans, sim(2, -1));
  memcpy(b, a, sizeof a);
  ans = max(ans, sim(n - 1, 1));
  memcpy(b, a, sizeof a);
  ans = max(ans, sim(1, 1));
  memcpy(b, a, sizeof a);
  ans = max(ans, sim(n, -1));
  
  cout << ans;
  return 0;
}

