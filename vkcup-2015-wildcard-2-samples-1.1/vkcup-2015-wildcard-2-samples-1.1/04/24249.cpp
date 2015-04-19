#include<cstdio>


int F[5100],b[5100],T(2),x[11000],y[11000],f[5100],Peo[5100],OK[5100][5100],Ans[5100],s[5100],n;

void IN(int a,int b){x[T]=f[a];y[T]=b;f[a]=T++;}

int main()
{	int i,j,k;
//	freopen("e.in","rb",stdin);
//	freopen("e.out","wb",stdout);
	scanf("%d",&n);
	for(i=1;i<n;i++)
	{	scanf("%d%d",&j,&k);
		IN(j,k);
		IN(k,j);
	}
	for(b[s[i=0]=1]=j=1;i<j;i++)
		for(k=f[s[i]];k;k=x[k])
			if(!b[y[k]])
			{	b[s[j++]=y[k]]=1;
				F[y[k]]=s[i];
			}
	for(i=n-1;i>=0;i--)Peo[F[s[i]]]+=Peo[s[i]]+1;
	for(i=1;i<=n;i++)OK[i][0]=1;
	for(i=n-1;i>=0;i--)
	{	for(j=0;j<=Peo[s[i]];j++)OK[s[i]][Peo[s[i]]-j]|=OK[s[i]][j];
		for(j=0;j<=Peo[s[i]];j++)
			if(OK[s[i]][j])
				Ans[j]=Ans[n-1-j]=1;
		for(j=Peo[F[s[i]]];j>=Peo[s[i]]+1;j--)
			OK[F[s[i]]][j]|=OK[F[s[i]]][j-Peo[s[i]]-1];
	}
	j=0;
	for(i=1;i+1<n;i++)if(Ans[i])j++;
	printf("%d\n",j);
	for(i=1;i+1<n;i++)if(Ans[i])printf("%d %d\n",i,n-1-i);
	return 0;
}
