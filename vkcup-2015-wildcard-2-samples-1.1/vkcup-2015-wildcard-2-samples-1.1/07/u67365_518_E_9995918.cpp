#include <iostream>
#include <cstdio>
#include <vector>
#include <set>
#include <map>
#include <queue>
#include <deque>
#include <stack>
#include <algorithm>
#include <cstring>
#include <functional>
#include <cmath>
#include <sstream>
using namespace std;
#define rep(i,n) for(int i=0;i<(n);++i)
#define rep1(i,n) for(int i=1;i<=(n);++i)
#define all(c) (c).begin(),(c).end()
#define fs first
#define sc second
#define pb push_back
#define show(x) cout << #x << " " << x << endl
typedef long long ll;
int To_ll(string s){
	istringstream is(s);
	ll ret;
	is>>ret;
	return ret;
}
ll q=1e16,a[100000];
vector<ll> vc,vs;
bool solve(){
	int K,N;
	cin>>N>>K;
	rep(i,N){
		string s;
		cin>>s;
		if(s[0]=='?'){
			a[i]=q;
		}else{
			a[i]=To_ll(s);
		}
	}
	rep(t,K){
		vc.clear();
		for(int i=t;i<N;i+=K) vc.pb(a[i]);
		vc.pb(q+1);
		int M=vc.size();
		int cnt=0,p=-q;
		rep(i,M){
			if(vc[i]==q){
				cnt++;
			}else{
				if(p+cnt>=vc[i]) return 0;
				if(p<0&&vc[i]>0){
					vs.clear();
					vs.pb(0);
					int now=1;
					rep(j,cnt-1){
						if(p<now&&now<vc[i]){
							vs.pb(now);
							if(now>0) now=-now;
							else now=-now+1;
						}
						else{
							if(now>0) now=-now;
							else now=-now+1;
							vs.pb(now);
							if(now>0) now=-now;
							else now=-now+1;
							
						}
					}
					sort(all(vs));
					for(int j=i-cnt;j<i;j++) vc[j]=vs[j-(i-cnt)];
				}else if(p>=0){
					for(int j=i-cnt;j<i;j++) vc[j]=p+j-(i-cnt)+1;
				}else{
					for(int j=i-1;j>=i-cnt;j--) vc[j]=vc[i]-(i-j);
				}
				cnt=0;
				p=vc[i];
			}
		}
		rep(i,M-1) a[t+i*K]=vc[i];
	}
	rep(i,N) cout<<a[i]<<" ";
	cout<<endl;
	return 1;
}
int main(){
	if(!solve()) cout<<"Incorrect sequence"<<endl;
}