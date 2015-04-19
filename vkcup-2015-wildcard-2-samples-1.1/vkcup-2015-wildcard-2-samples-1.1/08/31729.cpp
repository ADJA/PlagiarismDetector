#include <bits/stdc++.h>
#include <iostream>
#include <vector>
#include <queue>
#include <string>
#include <cstring>
#include <sstream>
#include <set>
#include <map>
#include <algorithm>
#include <cstdio>
#include <cstdlib>

#define rep(i,n) for(int i=0;i<(int)(n);++i)
#define iter(a) __typeof(a.begin())
#define FOR(it,a) for(iter(a)it=a.begin();it!=a.end();++it)
#define F first
#define S second
#define SZ(a) (int)((a).size())
#define sz(a) SZ(a)
#define pb(a) push_back(a)
#define mp(a,b) make_pair(a,b)
#define ALL(a) (a).begin(),(a).end()
using namespace std;

typedef long long ll;
typedef pair<int,int> PI;
typedef unsigned long long ull;

#ifdef ONLINE_JUDGE
#define PR(...) (void(0))
#else
#define PR(...) do{cerr << "line : " << __LINE__ << endl; pr(#__VA_ARGS__, __VA_ARGS__);}while(0)
template<class T>
void pr(const string& name, T t){
  cerr << name << ": " << t << endl;
}
template<typename T, typename ... Types>
void pr(const string& names, T t, Types ... rest) {
  auto comma_pos = names.find(',');
  cerr << names.substr(0, comma_pos) << ": " << t << ", ";
  auto next_name_pos = names.find_first_not_of(" \t\n", comma_pos + 1);
  pr(string(names, next_name_pos), rest ...);
}
#endif

template<class T,class U> ostream& operator<< (ostream& o, const pair<T,U>& v){return o << "(" << v.F << ", " << v.S << ")";}
template<class T> ostream& operator<< (ostream& o, const vector<T>& v){o << "{";rep(i,SZ(v)) o << (i?", ":"") << v[i];return o << "}";}
template<class T,class U> ostream& operator<< (ostream& o, const map<T,U>& v){o << "{";for(const auto& e : v) o << e << ", ";return o << "}";}
template<class T> string to_s(const T& v){ostringstream is;is << v;return is.str();}
//                 <  ^  >  V
const int dx[] = { 0,-1, 0, 1};
const int dy[] = {-1, 0, 1, 0};
#define endl '\n'


int main(int argc, char *argv[])
{
  ios::sync_with_stdio(0);
  cin.tie(0);
  
  int n;
  cin >> n;
  vector<ll> a(n);
  rep(i, n) cin >> a[i];
  int m;
  cin >> m;
  vector<int> b(m);
  rep(i, m) cin >> b[i];
  rep(i, m) --b[i];
  if(set<int>(ALL(b)).size() == m){
    cout << a[b[m-1]] - a[b[0]] << endl;
    return 0;
  }
  vector<int> app(n);
  rep(i, m) ++app[b[i]];

  vector<int> hoge;
  rep(i, n) hoge.pb(i);
  rep(i, n - 2) hoge.pb(n - i - 2);
  set<ll> ans;
  
  int s = 0;
  int diff = count(ALL(app), 0);
  ll tcost = 0;
  
  diff -= app[0] == 0;
  --app[0];
  diff += app[0] == 0;
  
  rep(i, m-1){
    tcost += abs(a[hoge[(s+i)%SZ(hoge)]] - a[hoge[(s+i+1)%SZ(hoge)]]);
    int h = hoge[(s+i+1)%SZ(hoge)];
    diff -= app[h] == 0;
    --app[h];
    diff += app[h] == 0;
  }
  
  if(diff == n)
    ans.insert(tcost);
  
  rep(i, SZ(hoge)){
    int h = hoge[i];
    int h2 = hoge[(i+1)% SZ(hoge)];
    //PR(h, h2);
    tcost -= abs(a[h] - a[h2]);
    diff -= app[h] == 0;
    ++app[h];
    diff += app[h] == 0;
    h = hoge[(i + m - 1) % SZ(hoge)];
    h2 = hoge[(i + m) % SZ(hoge)];
    //PR(h, h2, diff);
    tcost += abs(a[h2] - a[h]);
    diff -= app[h2] == 0;
    --app[h2];
    diff += app[h2] == 0;
    if(diff == n)
      ans.insert(tcost);
  }
  
  if(SZ(ans) == 1) cout << *ans.begin() << endl;
  else cout << -1 << endl;
}
