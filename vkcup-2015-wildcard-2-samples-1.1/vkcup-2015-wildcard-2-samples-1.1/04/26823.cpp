#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <cmath>
#include <vector>
#include <algorithm>
#define FOR(it, c) for(__typeof((c).begin()) it = (c).begin(); it != (c).end(); it++)
using namespace std;

typedef long long LL;
//I64d
int n;
int a[5005][5005], na[5005]={};
int c[5005][5005], child[5005];
int dp[5005], tmp[5005];
int go(int x, int from=-1) {
	int cnt = 1, idx = -1;
	for(int i=0;i<na[x];i++) {
		int y = a[x][i];
		if(y == from) { idx = i; continue; }
		c[x][i] = go(y, x);
		cnt += c[x][i];
	}
	if (from > 0) { c[x][idx] = n - cnt; }
	memset(tmp, 0, sizeof(tmp));
	tmp[0] = 1;
	int sum = 0;
	for(int i=0;i<na[x];i++) {
		for(int j=sum;j>=0;j--) tmp[j+c[x][i]] |= tmp[j];
		sum += c[x][i];
	}
	for(int i=1;i<n-1;i++) dp[i] |= tmp[i];
	return cnt;
}
int main(void) {
	scanf("%d", &n);
	for(int i=1;i<n;i++) {
		int x, y;
		scanf("%d%d", &x, &y);
		a[x][na[x]++] = y;
		a[y][na[y]++] = x;
	}
	go(1);
	vector<int> ans;
	for(int i=1;i<n-1;i++) if(dp[i]) ans.push_back(i);
	printf("%d\n", (int)ans.size());
	for(int i=0;i<(int)ans.size();i++)
		printf("%d %d\n", ans[i], n-ans[i]-1);
	return 0;
}
