// Enjoy your stay.

#include <bits/stdc++.h>

#define long long long
#define LOOPVAR_TYPE long

#define all(x) (x).begin(), (x).end()
#define sz(x) ((LOOPVAR_TYPE)(x).size())
#define foreach(it, X) for(__typeof((X).begin()) it = (X).begin(); it != (X).end(); it++)
#define GET_MACRO(_1, _2, _3, NAME, ...) NAME
#define _rep(i, n) _rep2(i, 0, n)
#define _rep2(i, a, b) for(LOOPVAR_TYPE i = (LOOPVAR_TYPE)(a); i < (LOOPVAR_TYPE)(b); i++)
#define rep(...) GET_MACRO(__VA_ARGS__, _rep2, _rep)(__VA_ARGS__)

#define fir first
#define sec second
#define mp make_pair
#define mt make_tuple
#define pb push_back

const double EPS = 1e-9;
const double PI = acos(-1.0);
const long INF = 1070000000LL;
const long MOD = 1000000007LL;

using namespace std;

typedef istringstream iss;
typedef stringstream sst;
typedef pair<LOOPVAR_TYPE, LOOPVAR_TYPE> pi;
typedef vector<LOOPVAR_TYPE> vi;

int n,k;
vi v[100010];
vi val[100010];
int curs[100010];

void fail(){
	cout<<"Incorrect sequence"<<endl;
	exit(0);
}

int main(){
	cin.tie(0);
	ios_base::sync_with_stdio(0);
	
	cin>>n>>k;
	rep(i,n){
		string s;
		cin>>s;
		if(s[0] == '?')v[i%k].pb(INF);
		else{
			iss is(s);
			int a;
			is>>a;
			v[i%k].pb(a);
		}
	}
	rep(ind,k){
		//int m = sz(v[ind]);
		vi fixed;
		vi q(1);
		rep(i,sz(v[ind])){
			if(v[ind][i] != INF){
				fixed.pb(v[ind][i]);
				q.pb(0);
			}else{
				q.back()++;
			}
		}
		//
		//rep(i,sz(q))cout<<q[i]<<" ";cout<<endl;
		//
		if(sz(fixed) == 0){
			int from = - ((q[0] - 1) / 2);
			rep(i,from,from+q[0]){
				val[ind].pb(i);
			}
		}
		else{
			rep(i,sz(fixed) - 1){
				if(fixed[i] >= fixed[i+1]) fail();
			}
			rep(i,sz(q)){
				vi add;
				if(q[i] == 0) continue;
				if(i == 0){
					int from = min(fixed[0] - 1, 0LL);
					add.pb(from);
					int dif = 1;
					int dir = +1;
					while(sz(add) < q[i]){
						int cur = from + dif * dir;
						if(cur < fixed[0]){
							add.pb(cur);
						}
						if(dir == +1) dir = -1;
						else dir = +1, dif++;
					}
				}else if(i == sz(q) - 1){
					int from = max(fixed.back() + 1, 0LL);
					add.pb(from);
					int dif = 1;
					int dir = +1;
					//cout<<"!"<<endl;
					while(sz(add) < q[i]){
						int cur = from + dif * dir;
						//cout<<cur<<endl;
						if(cur > fixed.back()){
							add.pb(cur);
						}
						if(dir == +1) dir = -1;
						else dir = +1, dif++;
					}
				}else{
					int L = fixed[i-1] + 1, R = fixed[i] - 1;
					if(!(L <= R)) fail();
					int from = min(R, max(L, 0));
					add.pb(from);
					int dif = 1;
					int dir = +1;
					int failcombo = 0;
					while(sz(add) < q[i]){
						int cur = from + dif * dir;
						if(L <= cur && cur <= R){
							add.pb(cur);
							failcombo = 0;
						}else{
							failcombo++;
							if(failcombo == 2) fail();
						}
						if(dir == +1) dir = -1;
						else dir = +1, dif++;
					}
				}
				sort(all(add));
				rep(j,sz(add)) val[ind].pb(add[j]);
			}
		}
	}
	rep(i,n){
		if(v[i%k][i/k] != INF) cout<<v[i%k][i/k]<<" ";
		else{
			cout<<val[i%k][curs[i%k]++]<<" ";
		}
	}
	cout<<endl;
}
