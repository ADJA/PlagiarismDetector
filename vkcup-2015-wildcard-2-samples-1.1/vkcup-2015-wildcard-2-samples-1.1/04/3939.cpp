#include <iostream>
#include <fstream>
#include <sstream>
#include <cstdio>
#include <algorithm>
#include <cstring>
#include <cmath>
#include <vector>
#include <set>
#include <map>
#include <queue>
#include <stack>
#include <string>
#include <bitset>
#include <deque>
#define P push_back
#define S size()
#define B begin()
#define E end()
#define For(i,a) for(typeof(a.B) i=a.B;i!=a.E;i++)
typedef long long int64;
using namespace std;

const int MaxN=10000;

struct edge
{
	int vj,size;
	edge *next;
}da[MaxN*2],*g[MaxN],*cur=da;

void add(int u,int v)
{
	cur->vj=v;
	cur->size=0;
	cur->next=g[u];
	g[u]=cur++;
}

int n;
bool vis[MaxN];

int dfs(int now)
{
	int sum=1;

	vis[now]=true;
	for(edge *p=g[now];p!=NULL;p=p->next)
	{
		if(!vis[p->vj]) 
		{
			p->size=dfs(p->vj);
			da[(p-da)^1].size=n-p->size;
			sum+=p->size;
		}
	}
	return sum;
}

bool f[MaxN],ans[MaxN];

void dp(int no)
{
	for(int i=0;i<=n/2;i++) f[i]=false;
	f[0]=true;
	for(edge *p=g[no];p!=NULL;p=p->next)
	{
		for(int j=n/2-p->size;j>=0;j--)
			if(f[j])
			{
				f[j+p->size]=true;
				//if(j+p->size==5) cerr<<no<<endl;
			}
	}
	for(int i=1;i<=n/2;i++) if(f[i]) ans[i]=true;
}

int main()
{
	scanf("%d",&n);
	for(int i=1;i<n;i++)
	{
		int u,v;

		scanf("%d%d",&u,&v);
		add(u,v);add(v,u);
	}

	dfs(1);

	for(int i=1;i<=n;i++)
		if(g[i]->next!=NULL)
		{
			//cerr<<i<<endl;
			dp(i);
		}
	
	for(int i=1;i<=n;i++)
		if(ans[i]) ans[n-1-i]=true;
	
	int total=0;

	for(int i=1;i<=n;i++)
		if(ans[i]) total++;

	printf("%d\n",total);
	for(int i=1;i<=n;i++)
		if(ans[i]) printf("%d %d\n",i,n-1-i);
	return 0;
}

