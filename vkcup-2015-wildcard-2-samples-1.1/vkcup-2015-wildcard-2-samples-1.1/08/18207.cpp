#include <cstdio>
#include <cstring>
#include <iostream>
#include <algorithm>
#define M 200200
using namespace std;
int n,m;
int a[M],cnt[M];
int main()
{
    int i,x;
    cin>>n;
    for(i=1;i<=n;i++)
        scanf("%d",&a[i]);
    cin>>m;
    for(i=1;i<=m;i++)
        scanf("%d",&x),cnt[x]++;
    if(cnt[1]>cnt[n])
    {
        cnt[1]<<=1;cnt[n]<<=1;
        int temp1=0,temp2=0;
        for(i=2;i<=n;i++)
        {
            if(cnt[i-1]>cnt[i])
                (temp1?temp2:temp1)=i-1;
            if(cnt[i-1]-cnt[i]==2)
                (temp1?temp2:temp1)=i-1;
        }
        cout<<(long long)cnt[n]*(a[n]-a[1])+(a[temp1]-a[1])+(a[temp2]-a[1])<<endl;
        return 0;
    }
    if(cnt[1]<cnt[n])
    {
        cnt[1]<<=1;cnt[n]<<=1;
        int temp1=0,temp2=0;
        for(i=1;i<n;i++)
        {
            if(cnt[i+1]>cnt[i])
                (temp1?temp2:temp1)=i+1;
            if(cnt[i+1]-cnt[i]==2)
                (temp1?temp2:temp1)=i+1;
        }
        cout<<(long long)cnt[1]*(a[n]-a[1])+(a[n]-a[temp1])+(a[n]-a[temp2])<<endl;
        return 0;
    }
    cnt[1]<<=1;cnt[n]<<=1;
    int temp1=0,temp2=0;
    for(i=1;i<=n;i++)
    {
        if(i!=1&&cnt[i]<cnt[i-1])
            temp1=i-1;
        if(i!=n&&cnt[i]<cnt[i+1])
            temp2=i+1;
    }
    if(temp1&&temp2)
    {
        cout<<(long long)(cnt[n]-1)*(a[n]-a[1])+(a[temp1]-a[1])+(a[n]-a[temp2])<<endl;
        return 0;
    }
    for(i=1;i<n;i++)
        if(a[i+1]-a[i]!=a[2]-a[1])
        {
            puts("-1");
            return 0;
        }
    cout<<(long long)cnt[n]*(a[n]-a[1])-(a[2]-a[1])<<endl;
    return 0;
}
