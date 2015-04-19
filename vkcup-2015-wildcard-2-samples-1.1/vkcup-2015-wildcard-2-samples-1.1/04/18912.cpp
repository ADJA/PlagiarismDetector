#include <cstdio>
#include <algorithm>
#include <cstring>
#define FOR(i,s,e) for (int i=(s); i<(e); i++)
#define FOE(i,s,e) for (int i=(s); i<=(e); i++)
#define FOD(i,s,e) for (int i=(s)-1; i>=(e); i--)
#define CLR(a,x) memset(a, x, sizeof(a))
#define N 5050
using namespace std;

int n, m, ret, cnt, ed, x, y;
int l[N], qd[N+N], qn[N+N], sz[N], can[N], dp[N], par[N];


void dfs(int x){
	sz[x] = 1;
	for (int i=l[x]; i; i=qn[i])
		if (!sz[qd[i]]){
			par[qd[i]] = x;
			dfs(qd[i]);
			sz[x] += sz[qd[i]];
		}

	CLR(dp, 0);
	dp[0] = 1;
	for (int i=l[x]; i; i=qn[i])
		if (par[qd[i]] == x){
			for (int j=n; j>=sz[qd[i]]; j--) dp[j] |= dp[j-sz[qd[i]]];
		}
	

	for (int j=n; j>=(n-sz[x]); j--) dp[j] |= dp[j-(n-sz[x])];

	FOR(j,0,n-1)
		if (dp[j]) can[j] = can[n-1-j] = 1;
}

void bd(int x, int y){
	qd[++ed] = y, qn[ed] = l[x], l[x] = ed;
}


int main(){
	scanf("%d", &n);
	FOR(i,1,n) scanf("%d%d", &x, &y), bd(x, y), bd(y, x);

	dfs(1);
	FOR(i,1,n-1) cnt += can[i];
	printf("%d\n", cnt);
	FOR(i,1,n-1)
		if (can[i]) printf("%d %d\n", i, n - i - 1);
	return 0;
}
