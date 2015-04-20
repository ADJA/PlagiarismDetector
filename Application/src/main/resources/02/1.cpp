#include <bits/stdc++.h>
#define all(a) (a).begin(),(a).end()
#define ld long double
#define ll long long
#define sqr(a) (a)*(a)
#define mp make_pair
#define pb push_back
#define x first
#define y second
#define inf (int)1e9
#define pi pair<int,int>
#define y1 fdfs
#define int long long
using namespace std;
const int N=3e6;
const int B1=31,B2=27;
const int md1=1e9+7,md2=1e9+13;
const int md=1e9+7;
string s;
int n,m,P1[N],P2[N],H1[N],H2[N],l1,l2,r1,r2,ans,csum,ss[N],b[N];
int pl,q;
void gg(){
    cout<<0;
    exit(0);
}
main(){
    ios_base::sync_with_stdio(0);
    cin>>n>>m>>s;
    pl=s.size();
    s='#'+s;
    P1[0]=P2[0]=1;
    for(int i=1;i<=n;++i){
        P1[i]=(P1[i-1]*B1)%md1;
        P2[i]=(P2[i-1]*B2)%md2;
    }
    for(int i=1;i<s.size();++i){
        H1[i]=(H1[i-1]+(s[i]-'a'+1)*P1[i])%md1;
        H2[i]=(H2[i-1]+(s[i]-'a'+1)*P2[i])%md2;
    }
    for(int i=1;i<=m;++i){
        cin>>b[i];
        ss[b[i]]++;
        ss[b[i]+pl]--;
    }
    for(int i=2;i<=m;++i){
        q=(b[i-1]+pl)-b[i];
        if(q<=0)continue;
        r1=(H1[pl]-H1[pl-q]+md1);
        if(r1>=md1)r1-=md1;
        r2=(H2[pl]-H2[pl-q]+md2);
        if(r2>=md2)r2-=md2;
        l1=(H1[q]*P1[pl-q])%md1;
        l2=(H2[q]*P2[pl-q])%md2;
        if(l1!=r1||l2!=r2)gg();
    }
    ans=1;
    for(int i=1;i<=n;++i){
        csum+=ss[i];
        if(csum==0)ans=(ans*26)%md;
    }
    cout<<ans;
}
