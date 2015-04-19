/* Pranet Verma */
/* Yeh mera template hai. Apna khud banao =_= */
#include <bits/stdc++.h>
using namespace std;
#define infinity (1000000007)
#define ll long long
#define ull unsigned long long
#define pii pair<int,int>
#define ppi pair<pii,int>
#define ppp pair<pii,pii>
#define pip pair<int,pii>
#define pb push_back
#define mp make_pair
#define s(n) scanf("%d",&n)
#define s2(n,m) scanf("%d%d",&n,&m)
#define s3(n,m,l) scanf("%d%d%d",&n,&m,&l)
#define rep(i,n) for(int i=0;i<n;++i)
ll pwr(ll a,ll b,ll mod) {a%=mod;if(a<0)a+=mod;ll ans=1; while(b) {if(b&1) ans=(ans*a)%mod; a=(a*a)%mod; b/=2; } return ans; }
ll pwr(ll a,ll b) {ll ans=1; while(b) {if(b&1) ans*=a; a*=a; b/=2; } return ans; }
ll gcd(ll a,ll b) {while(b) {ll temp=a; a=b; b=temp%b; } return a; }
ll lcm(ll a,ll b) {return (a/gcd(a,b))*b; }
ll modularInverse(ll a,ll m) {/*reminder: make sure m is prime*/ assert(false); return pwr(a,m-2,m); }
const int mod=1000000007;

int inRow[25];
int inCol[25];
int n,m;
vector<int> masks[432];

string toString(int n)
{
  string ans;
  do
  {
    ans+='0'+n%2;
    n/=2;
  }
  while(n);
  reverse(ans.begin(),ans.end());
  return ans;
}

int eval(int mask)
{
  string temp=toString(mask);
  int ans=0;
  bool state=false;
  for(int i=0;i<temp.size();++i)
  {
    if(temp[i]=='1' && state==false)
    {
      state=true;
      ++ans;
    }
    else if(temp[i]=='0')
      state=false;
  }
  return ans;
}
void generateMasks()
{
  for(int i=0;i<(1<<n);++i)
  {
      int type=eval(i);
      masks[type].pb(i);
  }
}
bool DP[21][1<<5][11][11][11][11][11];
bool DONE[21][1<<5][11][11][11][11][11];
int ans[25];
void trace(int col,int prevmask,int l0,int l1,int l2,int l3,int l4)
{
  if(col==m)
    return;
  bool foundSomething=false;
  int req=inCol[col];
  // cout<<req<<endl;
  for(int i=0;i<masks[req].size();++i)
  {
    int newMask=masks[req][i];
    int change=prevmask^newMask;
    int t0=l0;
    int t1=l1;
    int t2=l2;
    int t3=l3;
    int t4=l4;
    // cout<<newMask<<endl;
     if( (change&0b00001) && (newMask&0b00001) )
      --t0;
    if( (change&0b00010) && (newMask&0b00010) )
      --t1;
    if( (change&0b00100) && (newMask&0b00100) )
      --t2;
    if( (change&0b01000) && (newMask&0b01000) )
      --t3;
    if( (change&0b10000) && (newMask&0b10000) )
      --t4;
    if(t0>=0 && t1>=0 && t2>=0 && t3>=0 && t4>=0)
    {
      if(DP[col+1][newMask][t0][t1][t2][t3][t4]==true)
    {
      foundSomething=true; 
      ans[col]=newMask;
      trace(col+1,newMask,t0,t1,t2,t3,t4);
      return;
    }

  }
  }

  assert(foundSomething==true);
}
char op[42][423];
int main()
{

  std::ios::sync_with_stdio(false);
  
  cin>>n>>m;
  for(int i=0;i<n;++i)
    {
      cin>>inRow[i];
      assert(inRow[i]<=10);
    }
  for(int i=0;i<m;++i)
      cin>>inCol[i];

  generateMasks();


  for(int i=0;i<(1<<n);++i)
    DP[m][i][0][0][0][0][0]=true;

  for(int col=m-1;col>=0;--col)
  for(int prevmask=0;prevmask<(1<<n);++prevmask)
  for(int l0=0;l0<=inRow[0];++l0)
  for(int l1=0;l1<=inRow[1];++l1)
  for(int l2=0;l2<=inRow[2];++l2)
  for(int l3=0;l3<=inRow[3];++l3)
  for(int l4=0;l4<=inRow[4];++l4)
  {

      bool ans=false;
      int req=inCol[col];
      for(int i=0;i<masks[req].size();++i)
      {
            int newMask=masks[req][i];
            int change=prevmask^newMask;
            int t0=l0;
            int t1=l1;
            int t2=l2;
            int t3=l3;
            int t4=l4;
            if( (change&0b00001) && (newMask&0b00001) )
              --t0;
            if( (change&0b00010) && (newMask&0b00010) )
              --t1;
            if( (change&0b00100) && (newMask&0b00100) )
              --t2;
            if( (change&0b01000) && (newMask&0b01000) )
              --t3;
            if( (change&0b10000) && (newMask&0b10000) )
              --t4;
            if(t0>=0 && t1>=0 && t2>=0 && t3>=0 && t4>=0)
            {
              ans=ans|DP[col+1][newMask][t0][t1][t2][t3][t4];
              if(ans==1)
                break;
            }
      }
      DP[col][prevmask][l0][l1][l2][l3][l4]=ans;      

  }

  bool a=DP[0][0][inRow[0]][inRow[1]][inRow[2]][inRow[3]][inRow[4]];
  assert(a==1);
  trace(0,0,inRow[0],inRow[1],inRow[2],inRow[3],inRow[4]);


  for(int i=0;i<m;++i)
  {
    int mask=ans[i];
    for(int j=0;j<n;++j)
    {
      if(mask&(1<<j))
        op[j][i]='*';
      else
        op[j][i]='.';
    }
  }

  for(int i=0;i<n;++i,cout<<endl)
    for(int j=0;j<m;++j)
      cout<<op[i][j];
}