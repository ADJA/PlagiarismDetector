#include <iostream>
#include <queue>
#include <vector>
#include <string>
#include <algorithm>
#include <set>
#include <map>
#include <cctype>
#include <sstream>
#include <memory.h>
#include <cstdio>
#include <complex>
#include <cstdlib>
using namespace std;

typedef long long ll;
typedef pair<int, int> P;
typedef complex<double> pt;

#define rep(i, n) for(int i = 0; i < (int)(n); i++)
#define rep2(i, m, n) for(int i = m; i < n; i++)
#define pb(v, b) v.push_back(b);

const double EPS = 1e-10;
const double INF = 1000 * 1000 * 1000 + 7;


vector<int> G[5010];

bool ok[5010];
bool f[5010];

int dfs(int v, int p, int e){
  int res = 1;
  rep(i, G[v].size()){
    int to = G[v][i];
    if(to != p && to != e){
      res += dfs(to, v, e);
    }
  }
  return res;
}

vector<int> calc(int v){
  vector<int> res;
  rep(i, G[v].size()){
    pb(res, dfs(G[v][i], v, -1));
  }
  return res;
}

int main(){
  int n, x, y;
  cin >> n;	    
  rep(i, n - 1){
    cin >> x >> y;
    x--, y--;
    pb(G[x], y);
    pb(G[y], x);
  }
  
  
  vector<int> res;
  
  memset(ok, false, sizeof(ok));
  rep(i, n){
    memset(f, false, sizeof(f));
    vector<int> v = calc(i);
    int m = v.size();
    f[0] = true;
    rep(j, m){
      for(int k = n; k >= 0; k--){
	if(f[k]){
	  f[v[j]+k] = true;
	}
      }
    }

    rep(j, n){
      if(f[j]){
	ok[j] = true; 
      }
    }
  }

  int cnt = 0;
  rep(i, n){
    if(i > 0 && i < n - 1 && ok[i]) cnt++;
  }
  cout << cnt << endl;
  rep(i, n){
    if(i > 0 && i < n - 1 && ok[i]){
      cout << i << " " << n - 1 - i << endl;
    }
  }
  return 0;
}


