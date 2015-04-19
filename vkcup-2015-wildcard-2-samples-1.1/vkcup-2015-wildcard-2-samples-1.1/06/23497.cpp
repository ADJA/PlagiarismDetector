#include <iostream>
#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <algorithm>
#include <queue>
#include <map>
#include <set>

using namespace std;

#define rep(a,b,c) for(int a=b;a<=c;++a)
#define per(a,b,c) for(int a=b;a>=c;--a)
#define X first
#define Y second
#define PII pair<int,int>
#define max(a,b) (((a)>(b))?(a):(b))
#define min(a,b) (((a)<(b))?(a):(b))
#define pb push_back
#define mp make_pair

typedef long long ll;

int n,q,ans;
ll a[2222222],k;
ll sum[2222222];
PII s[2222222];
char cc;

void read(int &x){
    for (cc=getchar();cc<'0' || cc>'9';cc=getchar());
    for (x=0;cc>='0' && cc<='9';cc=getchar())   x=x*10+cc-'0';
}

void read(ll &x){
    for (cc=getchar();cc<'0' || cc>'9';cc=getchar());
    for (x=0;cc>='0' && cc<='9';cc=getchar())   x=x*10+cc-'0';
}

int main(){
    read(n);read(q);
    rep(i,1,n)  read(a[i]);
    rep(i,1,n)  a[i+n]=a[i];
    rep(vv,1,q){
        read(k);
        ll cur=0;
        int fb=0,r=0,lt=1,ed,md;
        rep(i,1,n){
            if  (cur+a[i]>k){
                s[++r]=mp(lt,i-1);
                sum[r]=cur;
                cur=a[i];lt=i;
            }
            else    cur+=a[i];
        }
        if  (cur){
            s[++r]=mp(lt,n);
            sum[r]=cur;
        }
        ans=r;
        ed=s[1].Y;
        rep(j,1,ed){
            sum[1]-=a[j];
            s[1].X++;
            int i=1;
            do{
                if  (s[i].Y==n+j-1) break;
                md=0;
                while   (sum[i]+a[s[i].Y+1]<=k){
                    s[i].Y++;
                    sum[i]+=a[s[i].Y];
                    s[i+1].X++;
                    sum[i+1]-=a[s[i].Y];
                    if  (s[i].Y==n+j-1) break;
                    md=1;
                }
                if  (!md)   break;
                i++;
            }while  (1);    
            while   (sum[r]==0) r--;
            if  (sum[r]+a[j]<=k){
                sum[r]+=a[j];
                s[r].Y++;
            }
            else{
                r++;
                s[r].X=s[r].Y=n+j;
                sum[r]=a[j];
            }
            ans=min(ans,r);
        }
        cout <<ans <<endl;
    }
}
