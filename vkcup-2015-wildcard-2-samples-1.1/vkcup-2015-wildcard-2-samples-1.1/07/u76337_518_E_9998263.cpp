/*
    Look at me!
    Look at me!
    Look at how large the monster inside me has become!
*/

#include<fstream>
#include<iostream>
#include<cstdio>
#include<map>
#include<set>
#define FIT(a,b) for(vector<int >::iterator a=b.begin();a!=b.end();a++)
#define FITP(a,b) for(vector<pair<int,int> >::iterator a=b.begin();a!=b.end();a++)
#define RIT(a,b) for(vector<int>::reverse_iterator a=b.end();a!=b.begin();++a)
#include<stack>
#define ROF(a,b,c) for(int a=b;a>=c;--a)
#include<vector>
#include<algorithm>
#define FOR(a,b,c) for(int a=b;a<=c;++a)
#define REP(a,b) for(register int a=0;a<b;++a)
#include<cstring>
#include<ctime>
#include<bitset>
#include<cmath>
#include<iomanip>
#include<set>
#define f cin
#define g cout
#include<queue>
#define debug cerr<<"OK";
#define pii pair<int,int>
#define mp make_pair
#define pb push_back
#define fi first
#define se second
#define ll long long
#define ull unsigned long long
#define mod 1000000009LL
#define N 100100
#define SQR 350
#define inf 1<<30
#define div fdasfasd
#define hash dsafdsfds
#define od 666013
#define mod 1000000007
#define DIM 600100
using namespace std;
/*
    int dx[]={0,0,0,1,-1};
    int dy[]={0,1,-1,0,0};
*/

ll v[N],s[N];
int n,k,len,a[N],b[N];
char se[30];
int main ()
{
    #ifndef ONLINE_JUDGE
    freopen("a.in","r",stdin);
    freopen("a.out","w",stdout);
    #endif

    f>>n>>k;
    FOR(i,1,n)
    {
        f>>se;
        if(se[0]=='?')
            b[i]=1;
        else
        {
            int r=strlen(se);
            int semn=1;
            REP(j,r)
            {
                if(j==0&&se[j]=='-')
                {
                    semn=-1;
                    continue;
                }
                v[i]=v[i]*10+se[j]-'0';
            }
            v[i]*=semn;
        }
    }
    FOR(i,1,k)
    {
        int t=0;
        for(int j=i;j<=n;j+=k)
        {
            ++t;
            a[t]=0;
            if(b[j])
                a[t]=b[j];
            s[t]=v[j];
        }
        int p=1;
        ll mi=-1100000001;
        FOR(j,1,t)
        {
            int p=j;
            while(a[j]&&j<=t)
                ++j;
            if(j==t+1&&a[j-1])
            {
                --j;
                if(mi<0)
                {
                    len=j-p+1;
                    len/=2;
                    len=-len;
                    if(mi+1>len)
                        len=mi+1;
                    FOR(k,p,j)
                    s[k]=len++;
                }
                else
                    FOR(k,p,j)
                        s[k]=++mi;
                break;
            }
            if(j==p)
             {
                 mi=s[j];
                 continue;
             }
            if(s[j]>=0)
            {
                if(mi>=0)
                {
                    FOR(k,p,j-1)
                    s[k]=++mi;
                }
                else
                {
                    len=j-1-p+1;
                    len/=2;
                    len=-len;
                    if(mi+1>len)
                        len=mi+1;
                    if(len+j-1-p>=s[j])
                        len-=len+j-1-p-s[j]+1;
                    FOR(k,p,j-1)
                    s[k]=len++;
                }
                mi=s[j];
            }
            else
            {
                len=j-1-p+1;
                mi=s[j]-len-1;
                FOR(k,p,j-1)
                s[k]=++mi;
                mi=s[j];
            }
        }
        t=0;
        for(int j=i;j<=n;j+=k)
        {
            ++t;
            v[j]=s[t];
        }
    }
    FOR(i,k+1,n)
    if(v[i]<=v[i-k])
    {
        g<<"Incorrect sequence";
        return 0;
    }
    FOR(i,1,n)
    g<<v[i]<<" ";
    return 0;
}
