#include <stdio.h>
#include <algorithm>
#include <iostream>
#include <string.h>

using namespace std;
int a[2001000];
int sum[2001000],k,t;
int n,q;
void getint(int &c)
{
    char ch;
    while(ch=getchar())
    {
        if(ch>='0'&&ch<='9'){
            c=ch-'0';
            break;
        }
    }
    while(ch=getchar())
    {
        if(ch>='0'&&ch<='9')
        {
            c=c*10+ch-'0';
        }
        else break;
    }
}
int play(int start)
{
    int i,sum=0,s=1;
    t=start;
    for(i=start;i<start+n;i++)
    {
        sum+=a[i];
        if(sum>k){
            sum=a[i];
            s++;
            t=i;
        }
    }
    return s;
}
int main()
{
    
    while(~scanf("%d%d",&n,&q))
    {
        for(int i=1;i<=n;i++)
        {
            getint(a[i]);
            a[i+n]=a[i];
        }
        while(q--)
        {
            getint(k);
            if(n>1)
            {int ans=play(1);
            ans=min(ans,play(t));
            ans=min(ans,play(2));
            ans=min(ans,play(t));
            printf("%d\n",ans);}
            else printf("1\n");
        }
    }
    int aaa=0;
    aaa++;
}