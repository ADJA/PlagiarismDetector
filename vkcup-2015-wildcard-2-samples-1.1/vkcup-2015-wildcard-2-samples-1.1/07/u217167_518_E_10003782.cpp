#include<cstdio>
#include<iostream>
#include<vector>
#include<cstring>
#include<algorithm>
#include<queue>
#include<set>
#include<cmath>
#include<bitset>
#include<stack>
#include<map>
#include<queue>
#define test(t) while(t--)
#define cin(n) scanf("%d",&n)
#define cinl(n) scanf("%lld",&n)
#define cout(n) printf("%d\n",n)
#define rep(i,a,n) for(i=a;i<=n;i++)
#define vi vector<int>
#include<assert.h>
#define vii vector< vector<int> >
#define vpii vector< pair<int,int> >
#define mii map<int,int>
#define pb push_back
#define inf 10000009
#define mp make_pair
#define imax (int) 1000000007
//#define inf 98765432
#define ill long long
#define getchar_unlocked() getchar()
#define inp(x) fi(&x)using namespace std;
#define mod 1000000007
#define gc getchar_unlocked
int fcin(){register int c = gc();int x = 0;for(;(c<48 || c>57);c = gc());for(;c>47 && c<58;c = gc()) {x = (x<<1) + (x<<3) + c - 48;}return x;}
using namespace std;

long long power(ill a,ill b)
{
ill ans=1LL;
while(b)
{
if(b&1)
ans=(ans*a)%mod;
a=(a*a)%mod;
b/=2;
}
return ans;


}
ill a[100008];
int mrk[100008];
ill f(ill mid,ill ci,ill x)
{
    long long ans=(x+mid)*1LL*ci+ci*(ci+1)/2;
    return ans;
}    
int main()
{

    int m,n,t,i,j,k,l;
    cin(n);
    cin(m);
    memset(mrk,0,sizeof(mrk));
    
    for(i=0;i<n;i++)
    {
        string s;
        cin>>s;
        if(s=="?")
        {
            mrk[i]=1;
            a[i]=0;
        }
        else
        {
            ill vl=0,fg=1,st=0;
            if(s[0]=='-')
            {
                fg=-1;
                st++;
            }
            for(j=st;j<s.length();j++)
                vl=(vl*10+s[j]-'0');
            vl*=fg;
            a[i]=vl;
        }
    }
    int anss=1;
    for(i=0;i<m;i++)
    {
         vector<pair<ill,int> >v;
        vector<int>vv;
        vv.clear();
        v.clear();
         ill coun=0,c=0,st,fg;
         fg=0;
         for(j=i;j<n;j+=m)
         {
             c++; 
             if(mrk[j])
                 coun++;
             else
                 fg=1;
             
             if(!mrk[j])
             {
                 vv.pb(j);
                 v.pb(mp(a[j],c));
             }
         }
         //cout<<c<<"\n";
       
         if(coun==c)
         {
             int vl=-(coun/2);
             for(j=i;j<n;j+=m)
                 a[j]=vl++;
            continue;
         }    
         c=0,fg=0;
        
         ill las,firs,lc,fc;
        
         for(j=i;j<n;j+=m)
         {
             c++;
             if(!mrk[j])
                 las=j,lc=c;
             
             if(mrk[j]&&!fg)
                 continue;
             
             if(!fg)
                 st=a[j],firs=j,fc=c;
             fg=1;
             
             
             if(!mrk[j]&&st>a[j])
                 anss=0;
             else if(!mrk[j])
                 st=a[j];
             else{}
             
             a[j]=st++;
             if(!anss)
                 break;
         }
         if(!anss)
            break;
         for(j=0;(j+1)<v.size();j++)
         {
             ill ci=v[j+1].second-v[j].second-1;
             ill x,y;
             x=v[j].first;
             y=v[j+1].first;
             //cout<<x<<" "<<y<<"\n";
             ill lo=0;
             ill high=y-(x+ci);
             if(high<lo)
                 anss=0;
             ill shif=0;
             int iter=0;
             //cout<<high<<"\n";
             //out<<f(1,ci,x)<<"\n";
             while(lo<high)
             {
                 iter++;
                 if(iter>500)
                     break;
                 ill m1=(2*lo+high)/3;
                 ill m2=(lo+2*high)/3;
                 //cout<<lo<<" "<<high<<"\n";
                 if(abs(f(m1,ci,x))>abs(f(m2,ci,x)))
                 {
                     lo=m1;
                     shif=m2;
                 }   
                 else
                 {
                     high=m2;
                     shif=m1;
                 }    
             } 
             
             for(k=vv[j]+m;k<vv[j+1];k+=m)
                 a[k]=(++shif)+x;
         }    
        int tc=0;
        for(j=i;j<n;j+=m)
            tc++;
        
         ill vl=min(a[firs]-1,(fc-1)/2);
         if(a[firs]<0)
             vl=a[firs]-1;
         for(j=firs-m;j>=0;j-=m)
             a[j]=vl--;
             
         vl=max(a[las]+1,-(tc-lc)/2);
         if(a[las]>0)
            vl=a[las]+1;
         
         for(j=las+m;j<n;j+=m)
             a[j]=vl++;
                 
         if(!anss)
            break;
    }
    if(!anss)
        cout<<"Incorrect sequence\n";
    else
    {
        for(i=0;i<n;i++)
            cout<<a[i]<<" ";
        cout<<"\n";
    }    



    
return 0;
}