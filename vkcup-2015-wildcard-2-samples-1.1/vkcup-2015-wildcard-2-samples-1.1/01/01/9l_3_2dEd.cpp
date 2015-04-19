#include <bits/stdc++.h>

using namespace std;

#define dbgs(x) cerr << (#x) << " --> " << (x) << ' '
#define dbg(x) cerr << (#x) << " --> " << (x) << endl

#define foreach(i,x) for(type(x)i=x.begin();i!=x.end();i++)
#define FOR(ii,aa,bb) for(int ii=aa;ii<=bb;ii++)
#define ROF(ii,aa,bb) for(int ii=aa;ii>=bb;ii--)

#define type(x) __typeof(x.begin())

#define orta (bas + son >> 1)
#define sag (k + k + 1)
#define sol (k + k)

#define pb push_back
#define mp make_pair

#define nd second
#define st first

#define endl '\n'

typedef pair < int ,int > pii;

typedef long long ll;

const int inf = 1e9, mod = 1e9+7;
const int N = 1e6+5;

int fail[N], x, i, j, k, n, m, h[N], dp[N];

char str[N];

int main(){

	scanf("%d %d %s",&n,&m,str+1);
	
	k = strlen(str+1);

	int q = 0;

	FOR(i,2,k){
		while(q && str[q+1] != str[i]) q = fail[q];
		if(str[q+1] == str[i]) q++;
		fail[i] = q;
	}

	int t = k;

	while(t){ h[t] = 1; t = fail[t]; }

	int last = 0;

	FOR(i,1,m){
		scanf("%d",&x);
		if(last && last+k-1 >= x && !h[last+k-x]){ cout << 0 << endl; return 0; }
		dp[x]++; dp[x+k]--;
		last = x;
	}
	
	int s = 0;

	FOR(i,1,n){ dp[i] += dp[i-1]; if(!dp[i]) s++; }

	int ans = 1;

	FOR(i,1,s) ans = ans * 26LL % mod;

	cout << ans << endl;

	return 0;
}
