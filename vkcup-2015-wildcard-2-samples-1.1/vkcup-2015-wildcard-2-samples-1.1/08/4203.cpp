//Done by Ferran Alet

#include<bits/stdc++.h>

#define INF 2147483647
#define LINF 1000000000000000000LL
#define EPS 1e-9
#define debug(x) cerr << #x << " = " << x << endl
#define Debug(v) cerr << #v << " = "; for(int wow=0;wow<v.size();++wow) cerr<<v[wow]<<' '; cerr<<endl
#define DEBUG(M) cerr << #M <<":"<<endl; for(int iM=0;iM<M.size();++iM) { for(int jM=0;jM<M[iM].size();++jM) cerr<<M[iM][jM]<<' '; cerr<<endl;} cerr<<endl
#define FOR(x,y) for(int x=0;x<y;x++)
#define FORS(x,y) for(int x=0;x<int(y.size());++x)
#define FORU(x,y) for(int x=1;x<=y;x++)
#define RFOR(x,y) for(int x=y-1;x>=0;--x)
#define DRI(x) int x; cin>>x
#define DRII(x,y) int x,y; cin>>x>>y
#define DRIII(x,y,z) int x,y,z; cin>>x>>y>>z
#define PB push_back
#define SZ(X) ((int)(X).size())
#define ALL(X) (X).begin(), (X).end()

using namespace std;

typedef long long ll;
typedef pair<int,int> PII;
typedef vector<int> VI;
typedef vector<VI> VVI;
typedef vector<double> VD;
typedef vector<VD> VVD;
typedef vector<bool> VB;
typedef vector<VB> VVB;
typedef vector<char> VC;
typedef vector<VC> VVC;
typedef vector<string> VS;
typedef map<int,int> MII;
typedef MII::iterator iMII;
typedef vector<PII > VP;
typedef vector<VP> VVP;

int obj = 0;

ll prova(vector<ll> &dist, vector<int> cont, int pos, int dir){
    int lolo=0;
    ll res=0;
    while(1){
        //cerr<<pos<<' ';
        if(cont[pos]==0) {
         //   debug(lolo);
            return (lolo!=obj ? LINF : res);
        }
        cont[pos]--;
        ++lolo;
        if(pos==dist.size()-1) dir-=2;
        if(pos==0) dir+=2;
        int posn = pos + dir;
        if(cont[posn]==0) {
        //    debug(lolo);
            return (lolo!=obj ? LINF : res);
        }
        res+=abs(dist[posn]-dist[pos]);
        pos = posn;
    }
    return LINF;
}

int main(){
    ios_base::sync_with_stdio(false);
    cin.tie(0);
//  freopen(".out","w",stdout);
//  freopen(".in","r",stdin);
    DRI(n);
    vector<ll> dist(n);
    FOR(i,n) cin>>dist[i];
    VI cont(n);
    DRI(m);
    int aux=0;
    FOR(i,m) {cin>>aux; cont[aux-1]++;}
    int maxim = cont[0], left =0, right=0;
    VI llocs;
    FOR(i,n) maxim = max(maxim,cont[i]);
    FOR(i,n){
        if(i==0 or i+1==n) continue;
        if(cont[i]==maxim && ((i==0 or cont[i]>cont[i-1]) or (i+1==n or cont[i]>cont[i+1]))) llocs.push_back(i);
    }
    obj =m;
    ll solucio=-2;
    vector<ll> solutions;
    /*Debug(cont);
    debug(left);
    debug(right);*/
    solutions.push_back(prova(dist,cont,0,-1));
    solutions.push_back(prova(dist,cont,n-1,1));
    FOR(i,llocs.size()){
        solutions.push_back(prova(dist,cont,llocs[i],-1));
        solutions.push_back(prova(dist,cont,llocs[i],1));
    }
 //   Debug(solutions);
    sort(solutions.begin(),solutions.end());
    while(solutions.size()>0 && solutions.back()==LINF) solutions.pop_back();
    cout<<((solutions.size()==0 or solutions[0]!=solutions.back()) ? -1LL : solutions[0])<<endl;
}
