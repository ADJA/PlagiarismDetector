#include <bits/stdc++.h>

#define REP(i,n) for(int i=0;i<(int)(n);i++)
#define ALL(x) (x).begin(),(x).end()

using namespace std;

int a[128000];
bool f[128000];

int to_int(string s) {
  int n;
  istringstream is(s);
  is >> n;
  return n;
}

vector<int> func(int num, int mi, int ma) {
  if (num == 0) return vector<int>(0);
  int n = min(-mi, ma);
  vector<int> res;
  if (mi >= 0) REP(i,num) res.push_back(mi+i);
  else if (ma <= 0) REP(i,num) res.push_back(ma-i);
  else if (n * 2 + 1 >= num) {
    res.push_back(0);
    int cnt = 1;
    REP(i,n) {
      res.push_back(i+1);
      ++cnt;
      if (cnt >= num) break;
      res.push_back(-i-1);
      ++cnt;
      if (cnt >= num) break;
    }
  }
  else if (-mi < ma) {
    REP(i,-mi) res.push_back(-i-1);
    REP(i,num+mi) res.push_back(i);
  }
  else {
    REP(i,ma) res.push_back(i+1);
    REP(i,num-ma) res.push_back(-i);
  }
  sort(ALL(res));
  return res;
}

int main() {
  int n, k;
  cin >> n >> k;
  REP(i,n) {
    string s; cin >> s;
    if (s == "?") f[i] = true;
    else a[i] = to_int(s);
  }
  REP(i,k) {
    int mi = -1010000000;
    vector<int> v;
    for (int j = i; j < n; j += k) {
      if (f[j]) v.push_back(j);
      else {
        if ((int)v.size() > a[j] - mi - 1) {
          cout << "Incorrect sequence" << endl;
          return 0;
        }
        vector<int> w = func((int)v.size(), mi+1, a[j]-1);
        REP(k,v.size()) a[v[k]] = w[k];
        mi = max(mi, a[j]);
        v.clear();
      }
    }
    vector<int> w = func((int)v.size(), mi+1, 1010000000);
    REP(k,v.size()) a[v[k]] = w[k];
  }
  REP(i,n) {
    if (i > 0) printf(" ");
    printf("%d", a[i]);
  }
  printf("\n");
  return 0;
}
