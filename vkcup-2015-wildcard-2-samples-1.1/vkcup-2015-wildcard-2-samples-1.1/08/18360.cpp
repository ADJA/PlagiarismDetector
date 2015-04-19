#include <bits/stdc++.h>
using namespace std;
#define For(i,a,b) for(long long i=a;i<b;i++)
#define pb push_back
#define mod 1000000007
#define reset(s,val) memset(s,val,sizeof(s))
#define eps 0.0000001
#define pi acos(-1)
#define sqr(x) (x)*(x)
#define maxn 32000

long long n,m,lis[200005],cnt[200005],val,rou,ans,l2,r2,l1,r1,each;

int main( ){
    //freopen("input.txt","r",stdin);
    //freopen("output.txt","w",stdout);
    cin>>n;
    ans=each=0;
    For(i,0,n) cin>>lis[i];
    for(int i=n-1;i;i--)
    {
        lis[i]-=lis[i-1];
        each+=lis[i];
    }
    cin>>m;
    while(m--)
    {
        cin>>val;
        cnt[val]++;
    }
    if(n==2)
    {
        cout<<each*(cnt[1]+cnt[2]-1);
        return 0;
    }
    rou=mod;
    For(i,2,n) rou=min(rou,cnt[i]/2);
    rou=min(rou,min(cnt[1],cnt[n]));
    cnt[1]-=rou;
    cnt[n]-=rou;
    ans=each*2*rou;
    For(i,2,n) cnt[i]-=2*rou;
    l2=l1=n+1;r2=r1=0;
    For(i,2,n)
    {
        if(cnt[i]==2)
        {
            l2=min(l2,i);r2=max(r2,i);
        }
        else if(cnt[i]==1)
        {
            l1=min(l1,i);r1=max(r1,i);
        }
    }
    if(cnt[1]&&cnt[n])
    {
        ans+=each;
        //cout<<ans<<endl;
        int cur=2;
        while(cnt[cur]==2)
        {
            ans+=lis[cur-1];
            cur++;
        }
        if(cur<n-1)
        {
            cur=n-1;
            while(cnt[cur]==2)
            {
                ans+=lis[cur];
                cur--;
            }
        }
        cout<<ans;
        return 0;
    }
    if(cnt[1])
    {
        if(cnt[2]==0)
        {
            cout<<ans;
            return 0;
        }
        if(r2)
        {
            For(i,1,r2) ans+=lis[i]*2;
            if(r1) For(i,r2,r1) ans+=lis[i];
            cout<<ans;return 0;
        }
        if(r1)
        {
            For(i,1,r1) ans+=lis[i];
            cout<<ans;return 0;
        }
    }
    if(cnt[n])
    {
        if(cnt[n-1]==0)
        {
            cout<<ans;return 0;
        }
        if(l2!=n+1)
        {
            For(i,l2,n) ans+=2*lis[i];
            if(l1) For(i,l1,l2) ans+=lis[i];
            cout<<ans;return 0;
        }
        if(l1)
        {
            For(i,l1,n) ans+=lis[i];
            cout<<ans;return 0;
        }
    }
    if(r1)
    {
        For(i,l1,r1) ans+=lis[i];
        cout<<ans;return 0;
    }
    int com=lis[1];
    For(i,2,n) if(com!=lis[i])
    {
        cout<<-1;return 0;
    }
    cout<<ans-com;
}
