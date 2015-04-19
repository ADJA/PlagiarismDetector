#include <cstdio>
#include <cstdlib>
#include <cmath>
#include <cstring>
#include <string>
#include <vector>
#include <map>
#include <set>
#include <queue>
#include <stack>
#include <utility>
#include <algorithm>
#include <iostream>
#include <sstream>
#include <iterator>

using namespace std;
typedef long long LL;

#define oo 1000000000
#define sqr(x) ((x)*(x))
#define lowbit(x) ((x)&(-(x)))

const double pi = acos(-1.0);

#define maxn 5000 + 10

int n,ans = 0;
int totm = 1,e[maxn<<1],last[maxn<<1],now[maxn];
int size[maxn];
bool hash[maxn],f[maxn];

void dfs( int i, int fa )
{
	size[i] = 1;
	for( int j = now[i] ; j ; j = last[j] )
		if( e[j] != fa )
			{
				dfs(e[j],i);
				size[i] += size[e[j]];
			}
}

int main()
{
	int i,j,k,u,v;

	scanf("%d",&n);
	for( i = 1 ; i < n ; ++i )
		{
			scanf("%d%d",&u,&v);
			++totm;
			e[totm] = v;
			last[totm] = now[u];
			now[u] = totm;
			++totm;
			e[totm] = u;
			last[totm] = now[v];
			now[v] = totm;
		}
	
	f[0] = 1;
	for( i = 1 ; i <= n ; ++i )
		{
			dfs(i,0);
			for( j = now[i] ; j ; j = last[j] )
				for( k = n ; k >= size[e[j]] ; --k )
					f[k] |= f[k-size[e[j]]];
			for( j = 1 ; j < n-1 ; ++j )
				hash[j] |= f[j], f[j] = 0;
		}

	for( i = 1 ; i < n-1 ; ++i )
		if( hash[i] )
			++ans;
	printf("%d\n",ans);
	for( i = 1 ; i < n-1 ; ++i )
		if( hash[i] )
			printf("%d %d\n",i,n-1-i);

	return 0;
}