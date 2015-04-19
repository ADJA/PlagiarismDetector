#include<cstring>
#include<cstdlib>
#include<cstdio>
#include<cmath>
#include<algorithm>
#include<map>
#include<set>
#include<string>
#include<vector>
#include<assert.h>
#define pb push_back
#define rep(i,j,k) for(int i=(j);i<=(int)k;i++)
#define per(i,j,k) for(int i=(j);i>=(int)k;i--)
#define lowbit(x) ((x)&(-(x)))
#define fi first
#define se second
#define pii pair<int,int>
#define VI vector<int>
#define S(x) x.size()
using namespace std;
typedef long long LL;
typedef double db;
int n,k;
const int N=110000;
const int inf=1e9;
int a[N];
int b[N];int m;
int read(){
	char p=getchar();
	while(p!='?'&&p!='-'&&(!(p<='9'&&p>='0')))p=getchar();
	if(p=='?')return inf+1;
	int sign=1;
	if(p=='-'){
		sign=-1;p=getchar();
	}
	int x=0;
	while(p<='9'&&p>='0'){
		x*=10;x+=p-48;p=getchar();
	}
	return x*sign;
}
void fail(){
	printf("Incorrect sequence");
	exit(0);
}
void work(){
	int lst=-inf-1;
	rep(i,1,m)if(b[i]<=inf){
		if(b[i]<=lst)fail();
		lst=b[i];
	}
	b[0]=-inf-1;
	b[m+1]=inf+1;
	for(int i=1;i<=m;i++)if(b[i]>inf){
		int j=i;
		while(j<m&&b[j+1]>inf)j++;
		int mid=(i+j)/2;
		int r,l;
		if(i==1)l=-inf-1000086;else l=b[i-1]+1;
		if(j==m)r=inf+1000086;else r=b[j+1]-1;
		if(r-l<j-i)fail();
		l+=mid-i;r-=j-mid;
		if(r<=0){
			int gt=r-(mid-i);
			rep(k,i,j){
				b[k]=gt;gt++;
			}
		}
		else if(l>=0){
			int gt=l-(mid-i);
			rep(k,i,j){
				b[k]=gt;gt++;
			}
		}
		else{
			int gt=0-(mid-i);
			rep(k,i,j){
				b[k]=gt;gt++;
			}
		}
		i=j;
	}
}
int main(){
	scanf("%d%d",&n,&k);
	rep(i,1,n)a[i]=read();
	rep(i,0,k-1){
		m=0;
		for(int j=i;j<=n;j+=k)if(j>0&&j<=n)b[++m]=a[j];
		work();
		m=0;
		for(int j=i;j<=n;j+=k)if(j>0&&j<=n)a[j]=b[++m];
	}
	rep(i,1,n)printf("%d ",a[i]);
	return 0;
}
