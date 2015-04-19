#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <vector>
#include <algorithm>
using namespace std;
#define FOR(i,s,e) for (int i=(s);i<(e);++i)
#define FOE(i,s,e) for (int i=(s);i<=(e);++i)
#define CLR(a,x) memset(a,x,sizeof(a))
typedef long long LL;

int N, r, a[5005], M;
int cnt[5005][5005];

vector<int> v[5005];
bool vis[5005];
bool ok[5005];
bool b[5005];

int dfs(int u, int f){
	int ch = 1;
	
	for (int i=0;i<v[u].size();++i){
		if (v[u][i] == f) continue;
		int cnt = dfs(v[u][i], u);
		if (cnt && r==u){
			a[M++] = cnt;
		}
		ch += cnt;
	}
	
	return ch;
}

int main(){
	scanf("%d", &N);
	
	for (int i=1;i<N;++i){
		int x, y;
		scanf("%d%d", &x, &y);
		v[x].push_back(y);
		v[y].push_back(x);
	}
	
	for (int i=1;i<=N;++i){
		r = i;
		CLR(vis,false);

		CLR(b,false);
		M = 0;
				dfs(i, -1);
		b[0] = true;
		for (int j=0;j<M;++j){
			for (int k=(N+1)/2;k>=0;--k){
				if (b[k]) ok[k+a[j]] = b[k+a[j]] = 1;
			}
		}
	}	
	
	int ans = 0;
	for (int i=1;i<=N-2;++i){
		int x = i; int y = N-1-i;
		if (x>y) swap(x,y);
		if (ok[x]) ++ans;
	}
	printf("%d\n",ans);
	for (int i=1;i<=N-2;++i){
		int x = i; int y = N-1-i;
		if (x>y) swap(x,y);
		if (ok[x]){
			printf("%d %d\n", i, N-1-i);
		}
	}
	return 0;
}
