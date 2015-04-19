#include<bits/stdc++.h>
#define MA(a,b) ((a)>(b)?(a):(b))
#define MI(a,b) ((a)<(b)?(a):(b))
#define AB(a) (-(a)<(a)?(a):-(a))
#define X first
#define Y second
#define mp make_pair
#define pb push_back
#define pob pop_back
#define ep 0.000001
#define pi 3.1415926535897932384626433832795
#define na(x) ((x)<P?(x):(x)-P)
using namespace std;
const long long N=200202;
const long long P=1000000007;
long long a[N],b[N],s,x,n,k;
char C;
void ge(long long I){
    s=1;
    x=0;
    C=getchar();
    while (C!='-' && C!='?' && (!('0'<=C && C<='9'))) C=getchar();
    if (C=='?') {b[I]=1; return;}
     else
    if (C=='-') s=-1;
     else
        x=C-'0';

    C=getchar();
    while ('0'<=C && C<='9'){
        x=x*10+C-'0';
        C=getchar();
    }
    a[I]=x*s;
}
long long go(long long y){
    if (y>n) return y;
    if (b[y]==0) return y;
    return go(y+k);
}
vector <long long> ge(long long l,long long r,long long x){
    if (r-l+1<x) { cout<<"Incorrect sequence"<<endl; exit(0);}
    vector <long long> R;
    if (l<=0 && 0<=r) {
        R.pb(0);

        long long xx=1;
        while (R.size()<x){
            if (xx<=r)
            R.pb(xx);
            if (l<=-xx)
            if (R.size()<x) R.pb(-xx);
            xx++;
        }
        sort(R.begin(),R.end());
        return R;
    }
    if (l>=0) {
        for (int i=0;i<x;i++)
            R.pb(i+l);
        return R;
    }

    for (int  i=0;i<x;i++)
    R.pb(r-i);
     sort(R.begin(),R.end());
    return R;
 }
 bool ch(){
    for (int i=1;i<=k;i++){
        for (int j=i+k;j<=n;j+=k)
            if (a[j]<=a[j-k]) {return 1;}
    }
    return 0;
 }
int main(){
    scanf("%I64d%I64d",&n,&k);
    for (int i=1;i<=n;i++)
    ge(i);
    long long fin=0,li,las=-101000000001ll;
    vector <long long> v;
    for (int i=1;i<=k;i++){
        fin=0;
        li=i;
        las=-101000000001ll;
        while (li<=n){
                if (b[li]==1) {
            fin=go(li+k);
            if ((fin-li)/k>0){
            if (fin<=n){
                v=ge(las+1,a[fin]-1,(fin-li)/k);
                las=a[fin];
            } else v=ge(las+1,101000000001ll,(fin-li)/k);
                for (int i=0;i<(fin-li)/k;i++)
                    a[li+i*k]=v[i];
            }
            li=fin+k;
            } else las=a[li],li+=k;
        }
    }

    if (ch()) {
            cout<<"Incorrect sequence"<<endl;
        return 0;
    }
    for (int i=1;i<=n;i++) printf("%I64d ",a[i]);
    bolo:
   return 0;
}
