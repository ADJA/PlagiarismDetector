#include <cstdio>
#include <cstring>
const int kVtxMax = 5010;
const int kEdgeMax = 2 * kVtxMax;

struct Edge {
	int to;
	Edge *next;
} edge[kEdgeMax], *begin[kVtxMax];
int edgeCnt=0;
int size[kVtxMax];
bool f[kVtxMax], g[kVtxMax];
int father[kVtxMax];
int n;

void addEdge(int u, int v) {
	Edge *e = edge + edgeCnt++;
	e->to = v, e->next = begin[u];
	begin[u] = e;
}

void dfs(int x, int fa) {
	size[x] = 1;
	for ( Edge *e = begin[x]; e; e = e->next ) {
		if ( e->to == fa ) continue;
		father[e->to] = x;
		dfs(e->to, x);
		size[x] += size[e->to];
	}
}

int main() {
	//freopen("t.in", "r", stdin);
	scanf("%d", &n);
	for ( int i = 0; i < n - 1; i ++ ) {
		int a, b;
		scanf("%d%d", &a, &b);
		a--, b--;
		addEdge(a, b);
		addEdge(b, a);
	}
	father[0] = -1;
	dfs(0, -1);

	for ( int i = 0; i < n; i ++ ) {
		memset(f, 0, sizeof(f));
		f[n-size[i]] = f[0] = true;
		for ( Edge *e = begin[i]; e; e = e->next ) {
			if ( e->to == father[i] ) continue;
			for ( int j = n-1; j >= size[e->to]; j -- )
				f[j] |= f[j-size[e->to]];
		}
		for ( int j = 0; j <= n-1; j ++ )
			g[j] |= f[j];
	}
	int ans = 0;
	for ( int j = 1; j < n-1; j ++ )
		if ( g[j] ) ans++;
	printf("%d\n", ans);
	for ( int j = 1; j < n-1; j ++ )
		if ( g[j] )
			printf("%d %d\n", j, n-1-j);
}
