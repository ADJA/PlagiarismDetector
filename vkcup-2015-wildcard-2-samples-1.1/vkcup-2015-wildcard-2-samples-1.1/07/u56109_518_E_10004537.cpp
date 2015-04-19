#include <set>
#include <map>
#include <cmath>
#include <cstdio>
#include <vector>
#include <cstring>
#include <cstdlib>
#include <iostream>
#include <algorithm>
using namespace std;

#define inf (1<<30)
#define ll long long
#define sz(x) ((int) (x.size()))
#define mp make_pair
#define pb push_back
#define fi first
#define se second
#define d(x) cout << x << endl
#define REP(i,x) for (int i = 0; i < (int)(x); ++i)
#define rep(i,a,b) for (int i = (int) a; i <= (int) b; ++i)
#define dep(i,a,b) for (int i = (int) a; i >= (int) b; --i)
#define foreach(it,x) for (typeof((x).begin()) it=(x).begin();it!=(x).end();++it)
#define PII pair<int,int>

const int nn=1000100;
int a[nn],l[nn],r[nn],q[nn],v[nn],res[nn],n,k;
int read()
{
	char ch=getchar();
	for (;!(ch=='?'||ch>='0'&&ch<='9'||ch=='-');ch=getchar());
	if (ch=='?') return inf;
	int x=0,f=1;
	if (ch=='-') f=-1,ch=getchar();
	for (;ch>='0'&&ch<='9';ch=getchar())
		x=x*10+ch-'0';
	return x*f;
}
bool cmp(int x, int y)
{
	if (y==x+1) return 1;
	if (x==y&&(x==inf||x==-inf)) return 1;
	return 0;
}
int main()
{
	scanf("%d%d",&n,&k);
	rep(i,1,n) a[i]=read(),l[i]=-inf,r[i]=inf;
	rep(i,1,n)
	{
		if (a[i]!=inf)
		{
		//	v[i]=1;
			l[i]=max(l[i],a[i]);
		}
		if (l[i]!=-inf)
			if (i+k<=n)
				l[i+k]=max(l[i+k],l[i]+1);
	}
	dep(i,n,1)
	{
		if (a[i]!=inf)
		{
		//	v[i]=1;
			r[i]=min(r[i],a[i]);
		}
		if (r[i]!=inf)
			if (i>k)
				r[i-k]=min(r[i-k],r[i]-1);
	}
	rep(i,1,n)
		if (l[i]>r[i])
		{
			puts("Incorrect sequence");
			return 0;
		}
	rep(_,1,n)
	{
		if (v[_]) continue;
		q[0]=0;
		q[++q[0]]=_;
		v[_]=1;
		while (1)
		{
			int j=q[q[0]]+k;
			if (j>n||!cmp(l[q[q[0]]],l[j])||!cmp(r[q[q[0]]],r[j]))
				break;
			q[++q[0]]=j;
			v[j]=1;
		}
		int L=l[q[1]],R=r[q[q[0]]];
		if (L>=0)
		{
			rep(t,1,q[0]) res[q[t]]=L++;
		}
		else if (R<=0)
		{
			dep(t,q[0],1) res[q[t]]=R--;
		}
		else
		{
			int mx;
			for (int i=(q[0]+1)/2,j=i;;++i,--j)
			{
				if (l[q[i]]<=0&&0<=r[q[i]]) {mx=i;break;}
				if (l[q[j]]<=0&&0<=r[q[j]]) {mx=j;break;}
			}
			int o=0;
			dep(i,mx,1) res[q[i]]=o--;
			o=0;
			rep(i,mx,q[0]) res[q[i]]=o++;
		}
	}
	rep(i,1,n) printf("%d ",res[i]);
	return 0;
}

