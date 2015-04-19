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
typedef vector<VVB> VVVB;
typedef vector<char> VC;
typedef vector<VC> VVC;
typedef vector<string> VS;
typedef map<int,int> MII;
typedef MII::iterator iMII;
typedef vector<PII > VP;
typedef vector<VP> VVP;

VVI v(5);
VI f,c;

VVVB DP;
int n,m,base,B;
VI sol;

bool solve(int pos, int S, int num){
    //cerr<<pos<<','<<m<<' '<<S<<' '<<num<<endl;
    if(DP[pos][S][num]==true) return false; //Ja visitat -->fail
    DP[pos][S][num]=true;
    if(pos==m){ //Cas base
        if(num==0) return true;
        else return false;
    }
    assert(v[c[pos]].size()>0);
    FOR(iii,v[c[pos]].size()){
        int A = v[c[pos]][iii];
        int C = A&(~S);
        /*cerr<<S<<'.'<<A<<'.'<<C<<endl;
        debug(A);
        debug(C);*/
        int cnum = num;
        int nou=0;
        bool ok=true;
        int pseudo_base = 1;
        /*debug(num);
        debug(C);*/
        RFOR(i,n){
            int a = num%base;
            num/=base;
            //cerr<<'('<<a<<',';
            if((C&(1<<i))!=0) --a;
            //cerr<<a<<"..";
            if(a<0) {ok=false; break;}
            //cerr<<pseudo_base*a<<") ";
            nou+= pseudo_base* a;
            pseudo_base*=base;
        }
        //cerr<<endl;
        //debug(nou);
        if(ok) {
            if(solve(pos+1,A,nou)){
                sol.push_back(A);
                return true;
            }
        }
        num = cnum;
    }
    return false;
}

int main(){
    ios_base::sync_with_stdio(false);
    cin.tie(0);
//  freopen(".out","w",stdout);
  //freopen("F.in","r",stdin);
    while(cin>>n>>m){
        f = VI(n);
        c = VI(m);
        FOR(i,n) cin>>f[i];
        FOR(i,m) cin>>c[i];
        FOR(S,(1<<n)){
            int seg=0;
            int last=0;
            FOR(i,S){
                if((S&(1<<i))!=0){
                    if(last==0) ++seg;
                    last=1;
                }
                else last=0;
            }
            v[seg].push_back(S);
        }
       // DEBUG(v);
        base=1;
        FOR(i,n) base = max(base,f[i]);
        ++base;
        B = 1;
        FOR(i,n) B*=base;
        int num=0;
        FOR(i,n) {num*=base; num+=f[i];}
        /*Debug(f);
        Debug(c);
        debug(B);
        debug(num);*/
        DP = VVVB(m+1,VVB((1<<n),VB(B)));
        //cerr<<"Party!"<<endl;
        bool espero_true = solve(0,0,num);
        //debug(espero_true);
        reverse(sol.begin(),sol.end());
        VVC solucio(n, VC(m,'.'));
       // Debug(sol);
        FOR(i,n){
            FOR(j,m) if((sol[j]&(1<<i))!=0) solucio[i][j]='*';
        }
        FOR(i,n){
            FOR(j,m) {
                cout<<solucio[i][j];
            }
            cout<<endl;
        }
    }
}
