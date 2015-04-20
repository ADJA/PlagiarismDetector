#include <bits/stdc++.h>
#define MOD 1000000007
#define Nmax 1000005
#define INF 2000000000
#define eps 0.000000000001

using namespace std;

int n;
char a[Nmax];
int pi[Nmax];
bool fr[Nmax];

inline void Pi()
{
    int k=0,i;
    pi[1]=0;
    for(i=2;i<=n;++i)
    {
        while(k && a[k+1]!=a[i])
            k=pi[k];
        if(a[k+1]==a[i])
            ++k;
        pi[i]=k;
    }
}

inline int Pow_Log(int x, int p)
{
    int sol=1;
    while(p)
    {
        if(p&1)
        {
            sol=(1LL*sol*x)%MOD;
            --p;
        }
        p>>=1;
        x=(1LL*x*x)%MOD;
    }
    return sol;
}

int main()
{
    int i,j,k,x,cnt=0,len,m;
    #ifndef ONLINE_JUDGE
        freopen ("date.in","r",stdin);
        freopen ("date.out","w",stdout);
    #endif
    cin.sync_with_stdio(0);
    cin>>len>>m>>(a+1);
    n=strlen(a+1);
    Pi();
    k=pi[n];
    while(k)
    {
        fr[k]=true; k=pi[k];
    }
    int dr=0;
    for(i=1;i<=m;++i)
    {
        cin>>x;
        if(x>dr) cnt+=x-dr-1;
        else
        {
            if(!fr[dr-x+1])
            {
                cout<<0;
                return 0;
            }
        }
        dr=x+n-1;
    }
    cout<<Pow_Log(26,cnt+len-dr);
    return 0;
}
