#include<bits/stdc++.h>
using namespace std;
#define pb push_back
#define mp make_pair
#define y1 asdnqw
#define next mdamdamda
#define right praviy
#define endl "\n"
#define int long long
const int N=2200001;
const int B1=31,B2=27;
const int md1=1e9+7,md2=1e9+13;
const int md=1e9+7;
string s;
int n,m,p1[N],p2[N],h1[N],h2[N],l1,l2,r1,r2,ans,csum,ss[N],b[N];
int pl,q;
void fail(){
    cout<<0;
    exit(0);
}
main(){
    cin.tie(0);ios_base::sync_with_stdio(0);
    cin>>n>>m;
    cin>>s;
    pl=s.size();
    s='#'+s;
    p1[0]=p2[0]=1;
    for(int i=1;i<=n;++i){
        p1[i]=(p1[i-1]*B1)%md1;
        p2[i]=(p2[i-1]*B2)%md2;
    }
    for(int i=1;i<s.size();++i){
        h1[i]=(h1[i-1]+(s[i]-'a'+1)*p1[i])%md1;
        h2[i]=(h2[i-1]+(s[i]-'a'+1)*p2[i])%md2;
    }
    for(int i=1;i<=m;++i){
        cin>>b[i];
        ss[b[i]]++;
        ss[b[i]+pl]--;
    }
    for(int i=2;i<=m;++i){
        q=(b[i-1]+pl)-b[i];
        if(q<=0)continue;
        r1=(h1[pl]-h1[pl-q]+md1);if(r1>=md1)r1-=md1;
        r2=(h2[pl]-h2[pl-q]+md2);if(r2>=md2)r2-=md2;
        l1=(h1[q]*p1[pl-q])%md1;
        l2=(h2[q]*p2[pl-q])%md2;
       // cout<<l1<<' '<<r1<<' '<<l2<<' '<<r2<<' '<<q<<endl;
        if(l1!=r1||l2!=r2)fail();
    }
    ans=1;
    for(int i=1;i<=n;++i){
        csum+=ss[i];
        if(csum==0)ans=(ans*26)%md;
    }
    cout<<ans;


}
