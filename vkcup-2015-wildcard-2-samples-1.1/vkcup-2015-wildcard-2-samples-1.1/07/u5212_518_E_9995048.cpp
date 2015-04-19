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

#define PR(...) do{cerr << "line : " << __LINE__ << endl; pr(#__VA_ARGS__, __VA_ARGS__);}while(0);
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

template<class T,class U> ostream& operator<< (ostream& o, const pair<T,U>& v){return o << "(" << v.F << ", " << v.S << ")";}
template<class T> ostream& operator<< (ostream& o, const vector<T>& v){o << "{";rep(i,SZ(v)) o << (i?", ":"") << v[i];return o << "}";}

const int dx[] = {0,1,0,-1};
const int dy[] = {-1,0,1,0};
#define endl '\n'

const int MAX_N = 1e5 + 100;
bool isq[MAX_N];
ll val[MAX_N];

ll out[MAX_N];

int main(int argc, char *argv[])
{
  int n,k;
  cin >> n >> k;
  rep(i,n){
    string t;
    cin >> t;
    if(t == "?"){
      isq[i] = true;
      continue;
    }
    stringstream ss(t);
    ss >> val[i];
  }
  
  
  rep(i, n){
    if(!isq[i] && i+k < n && !isq[i+k] && val[i] >= val[i+k]){
      cout << "Incorrect sequence" << endl;
      return 0;
    }
    if(!isq[i]) continue;
    int e = i;
    int s = i;
    int cnt = -1;
    while(e < n && isq[e]){
      e += k;
      ++cnt;
    }
    
    while(s >=0 && isq[s]){
      s -= k;
      ++cnt;
    }
    ll minv = -2e9;
    ll maxv = 2e9;
    if(e < n) maxv = val[e];
    if(s >= 0) minv = val[s];
    if(minv + cnt >= maxv){
      cout << "Incorrect sequence" << endl;
      return 0;
    }

    if(minv >= 0){
      for(int i = s+k; i < min(n,e); i += k)
    val[i] = val[i-k]+1;
    }else if(maxv <= 0){
      for(int i = e-k; i > max(-1,s); i -= k)
    val[i] = val[i+k]-1;
    }else if(abs(minv) < abs(maxv)){/* minv < 0 < maxv */
      if(abs(minv)*2-1 >= cnt){
    val[s+k] = -(cnt/2);
    for(int i = s+k*2; i < min(e,n); i += k)
      val[i] = val[i-k]+1;
      }else{
    for(int i = s+k; i < min(e,n); i += k)
      val[i] = val[i-k]+1;
      }
    }else{
      if(abs(maxv)*2-1 >= cnt){
    val[e-k] = cnt/2;
    for(int i = e-k*2; i > max(s,-1); i -= k)
      val[i] = val[i+k]-1;
      }else{
    for(int i = e-k; i > max(s,-1); i -= k)
      val[i] = val[i+k]-1;
      }      
    }

    while(s < e && s < n){
      if(s>=0) isq[s] = false;
      s += k;
    }
  }

  rep(i,n){
    if(i) cout << ' ';
    cout << val[i] ;
  }
  cout << endl;

  return 0;
}
