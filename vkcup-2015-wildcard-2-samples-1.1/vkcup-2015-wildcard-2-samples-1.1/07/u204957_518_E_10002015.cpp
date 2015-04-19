#include<cstdio>
#include<cstring>
#include<iostream>
#include<algorithm>
#include<cmath>
using namespace std;
typedef long long ll;
int T,t,n,m,k;
char s[110];
bool flag=true;
ll num[100010];
bool vis[100010];
void Solve(int a,int b,ll l,ll r)
{

    int i,j;
    ll ret,k2;
    ret=(b-a)/k+1;
    //printf("solve %d %d %d %d %I64d\n",a,b,l,r,ret);
    if(r-l-1<ret)
    {
        //printf("return %I64d %I64d\n",r-l-1,ret);
        flag=false;
        return;
    }
    //printf("solve %d %d %d %d %I64d\n",a,b,l,r,ret);
    k2=max(-ret/2,l+1);
    k2=min(k2,r-ret);
    for(;a<=b;a+=k)
    {
        num[a]=k2++;
        vis[a]=1;
    }
}
void solve()
{
    int i,j,a,b,pos;
    ll l,r,L,R;
    scanf("%d%d",&n,&k);
    for(i=1;i<=n;i++)
    {
        scanf("%s",s);
        if(s[0]=='?')
          continue;
        else
        {
            sscanf(s,"%I64d",&num[i]);
            vis[i]=1;
        }
    }
        L=-2000000000;
        R=2000000000;
    //printf("ok\n");
    for(i=1;i<=k;i++)
    {
        for(pos=i;pos<=n;pos+=k)
        {
            if(vis[pos])
            {
                if(pos>k && num[pos]<=num[pos-k])
                {
                    flag=false;
                    return;
                }
            }
            else
            {
                a=pos;b=pos;
                if(pos>k)
                  l=num[pos-k];
                else
                  l=L;
                while(true)
                {
                    pos+=k;
                    if(pos>n)
                    {
                        b=pos-k;
                        r=R;
                        Solve(a,b,l,r);
                        break;
                    }
                    if(vis[pos])
                    {
                        b=pos-k;
                        r=num[pos];
                        Solve(a,b,l,r);
                        break;
                    }
                }
            }
            //printf("%d %d %d\n",i,pos,flag);
            if(!flag)
              return;
        }
    }
}
int main()
{
    int i,j;
    solve();
    if(!flag)
      printf("Incorrect sequence\n");
    else
    {
        for(i=1;i<=n;i++)
           printf("%d ",num[i]);
        printf("\n");
    }
}
