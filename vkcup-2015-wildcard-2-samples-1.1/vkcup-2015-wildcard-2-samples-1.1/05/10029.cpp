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

#define rep(i, n) for(int i = 0; i < n; i++)
#define rep2(i, m, n) for(int i = m; i < n; i++)
#define pb(v, b) v.push_back(b);

const double EPS = 1e-10;
const double INF = 1000 * 1000 * 1000 + 7;

int n;
//0: left, 1 : right

// position, last, lastisvalid? fistcowboy's dir
ll memo[200][2][2][2][2];
int c[200];
string str;

ll calc(int pos, int l, int lv, int f, int fv){
  //  cout << pos << " " << l << " " << lv << " " << f << " " << fv << endl;
  if(pos == n){

    //    cout << l << " " << f << endl;
    //    cout << lv << " " << fv << endl;
    //    cout << endl;
    if(l == 1 && f == 0){
      return lv == 1 && fv == 1;
    }else{
      return lv == 0 && fv == 0;
    }
  }
  
  if(memo[pos][l][lv][f][fv] != -1){
    return memo[pos][l][lv][f][fv];
  }
  
  ll &res = memo[pos][l][lv][f][fv] = 0;
  int nvr = c[pos] == 1 ? 0 : 1;
  int nvl = c[pos] == 0 ? 0 : 1;
  
  
  if(pos != 1){
    if(lv){
      if(l == 0){
	return 0;
      }else{
	int nv = c[pos] == 1 ? 0: 1;
	res = calc(pos + 1, 0, nv, f, fv);
      }
    }else{
      res += calc(pos + 1, 1, nvr, f, fv);
      if(l == 0){
	res += calc(pos + 1, 0, nvl, f, fv);
      }
    }
  }else{
    
    int nfvr = fv;
    int nfvl = (f == 1 ? 1 - fv : fv);
    int nvl2 = (f == 1 ? 1 - nvl : nvl);
    res += calc(pos + 1, 0, nvl2, f, nfvl);
    res += calc(pos + 1, 1, nvr, f, nfvr);
  }
  return res;
}

int main(){
  cin >> str;
  n = str.size();
  rep(i, n){
    c[i] = str[i] == 'A' ? 1 : 0;
    //    cout << c[i];
  }
  //  cout << endl;
  memset(memo, -1, sizeof(memo));
  
  if(c[0] == 0){
    cout << calc(1, 0, 0, 0, 0) + calc(1, 1, 1, 1, 1) << endl;
  }else{
    cout << calc(1, 0, 1, 0, 1) + calc(1, 1, 0, 1, 0) << endl;
  }
  return 0;
}


