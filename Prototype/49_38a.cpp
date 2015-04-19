#include <stdio.h>
#include <string.h>
#include <algorithm>
#include <iostream>
#include <math.h>

using namespace std;
#define mod  1000000007LL 
char str[1111111],p[1111111];
int next[1111111],poi[1111111];
bool kt[1111111];
__int64 pow(__int64 d,int s)
{
    if(s==0)return 1;
    else if(s%2==1) return d*(pow(d,s-1)%mod)%mod;
    else if(s%2==0)return pow((d*d)%mod,s/2)%mod;
}
void getint(int &s)
{
    char ch;
    while(ch=getchar())
    {
        if(ch>='0'&&ch<='9')
        break;
    }
    s=ch-'0';
    while(ch=getchar())
    {
        if(ch>='0'&&ch<='9')s=s*10+ch-'0';
        else break;
    }
}
int main()
{
    int n,m;
    scanf("%d%d%*c",&n,&m);
    memset(str,'\0',sizeof(str));
    memset(kt,false,sizeof(kt));
    scanf("%s",p+1);
    next[0]=1;
    next[1]=0;
    kt[1]=true;
    for(next[0]=2;p[next[0]]!='\0';next[0]++)
    {
        int j=next[next[0]-1];
        while(j>0&&p[j+1]!=p[next[0]])j=next[j];
        next[next[0]]=j;
        if(p[j+1]==p[next[0]])
        {
            next[next[0]]++;
        }
        if(next[next[0]]==1||kt[next[next[0]]]==true)kt[next[0]]=true;
    }
    next[0]--;
    for(int i=1;i<=m;i++)
    getint(poi[i]);
    poi[m+1]=11111111;
    int tp=1;
    int ts=next[0]+1;
    bool key=true;
    int cnt=0;
    for(int i=1;i<=n;i++)
    {
        if(!key)break;
        if(ts>next[0])
        {
            if(poi[tp]==i)
            {
                ts=1;
                tp++;
            }
        }
        else if(ts<=next[0])
        {
            if(poi[tp]==i)
            {
                int len=next[0]-ts+1;
                int b=next[0];
                int d=next[b];
                if(kt[ts]==true)
                {
                    if(d-next[ts]+1==len)ts=1;
                    else key=false;
                }
                else key=false;
                tp++;
            }
        }
        if(ts<=next[0])
        {
            str[i]=p[ts];
        }
        else cnt++;
        ts++;
    }
    if(!key)printf("0\n");
    else {
        __int64 ans=pow(26LL,cnt)%mod;
        printf("%I64d\n",ans);
    }
    
}
/*
12 2
acdacd
1 7
*/