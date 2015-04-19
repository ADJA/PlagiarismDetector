//include
//------------------------------------------
#include <vector>
#include <list>
#include <map>
#include <set>
#include <deque>
#include <stack>
#include <bitset>
#include <algorithm>
#include <functional>
#include <numeric>
#include <utility>
#include <sstream>
#include <iostream>
#include <iomanip>
#include <cstdio>
#include <cmath>
#include <cstdlib>
#include <cctype>
#include <string>
#include <cstring>
#include <ctime>
#include <climits>
#include <queue>

using namespace std;

//typedef
//------------------------------------------
typedef vector<int> VI;
typedef vector<VI> VVI;
typedef vector<string> VS;
typedef pair<int, int> PII;
typedef long long LL;

//container util
//------------------------------------------
#define ALL(a)  (a).begin(),(a).end()
#define RALL(a) (a).rbegin(), (a).rend()
#define PB push_back
#define MP make_pair
#define SZ(a) int((a).size())
#define EACH(i,c) for(typeof((c).begin()) i=(c).begin(); i!=(c).end(); ++i)
#define EXIST(s,e) ((s).find(e)!=(s).end())
#define SORT(c) sort((c).begin(),(c).end())

//repetition
//------------------------------------------
#define FOR(i,a,b) for(int i=(a);i<(b);++i)
#define REP(i,n)  FOR(i,0,n)

//constant
//--------------------------------------------
const double EPS = 1e-10;
const double PI  = acos(-1.0);
const LL INF = 1e+15;

vector<LL> a;
bool f(LL l, LL r, VI& pos){
  LL n = SZ(pos);
  if(r-l-1 < n) return false;
  if(0 <= l) l++;
  else if(r <= 0) l = r - n;
  else
	l = min(max(l+1, -n/2), r-n);

  REP(i,n)
	a[pos[i]] = l + i;
  return true;
}


int main(){
  cin.tie(0);
  ios_base::sync_with_stdio(false);

  int N, K; cin >> N >> K;
  a.assign(N, 0LL);
  vector<bool> nd(N, false);
  REP(i,N){
	string s; cin >> s;
	if(s == "?")
	  nd[i] = true;
	else
	  a[i] = atoi(s.c_str());
  }

  bool ng = false;
  for(int i=0;i<K;++i){
	LL left = -INF;
	VI pos;
	for(int j=i;j<N;j+=K){
	  if(!nd[j]){
		if(left >= a[j]) ng = true;
		if(!pos.empty() && !f(left, a[j], pos))
		  ng = true;
		pos.clear();
		left = a[j];
	  }
	  else
		pos.PB(j);
	}
	if(!pos.empty() && !f(left, INF, pos))
	  ng = true;
  }

	

  if(ng)
	cout << "Incorrect sequence" << endl;
  else{
	cout << a[0];
	REP(i,N-1) cout << " " << a[i+1];
	cout << endl;
  }  
  
  return 0;
}
