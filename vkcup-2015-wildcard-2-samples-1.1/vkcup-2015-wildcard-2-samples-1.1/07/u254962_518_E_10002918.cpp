#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef vector < int > vi;
typedef pair< int ,int > pii;
#define SIZE(X) ((int)(X.size()))
#define X first
#define Y second
#define LENGTH(X) ((int)(X.length()))
#define PB push_back
#define MP(X,Y) make_pair(X,Y)
#define MEM(a,b) memset(a,(b),sizeof(a))
#define tr(c,it) for(typeof((c).begin()) it = (c).begin(); it != (c).end(); it++)
#define present(c,x) ((c).find(x) != (c).end()) 
#define cpresent(c,x) (find(all(c),x) != (c).end())
#define ain(a,n) int ((a)[(n)]); for(int i=0; i<(n); i++) cin>>((a)[i])
typedef long long int int64;
typedef unsigned long long uLL;
#define FOR(i,n) for(int i=0;i<n;i++)
#define FU(i,a,n) for(int i=a;i<=n;i++)
#define FD(i,a,n) for(int i=n;i>=a;i--)
#define GI(n) scanf("%d",&n)
#define GS(n) scanf("%s"&s)
#define GII(n,m) scanf("%d %d",&n,&m)
#define PI(n) printf("%d\n",n)
#define PII(n,m) printf("%d %d\n",n,m)
#define PL(n) printf("%I64d\n",n)
#define PLL(n) printf("%I64d\n",n)
#define GLL(n) scanf("%I64d",&n)
#define GL(n) scanf("%I64d",&n)
#define PN printf("\n")
#define N 2007
#define MAX 200007

const int inf = 1e9+1;

int main(){
    ios_base::sync_with_stdio(false);
    int n,k;
    cin >> n >>k;
    vector<vector<int> > a(k);
    for(int i=0;i<n;i++){
        char b[20];
        cin >> b;
        int x = inf;
        if(b[0]!='?') sscanf(b,"%d",&x);
        a[i%k].push_back(x);
    }

    for(int i=0;i<k;i++)
    {
        if(a[i].size()==0) continue;
        int l =0 ;
        while(l<a[i].size() && a[i][l]==inf) l++;
        if(l==a[i].size())
        {
            l/=2;
            l*=-1;
            for(int j =0; j<a[i].size();j++)
                a[i][j] = l++;
            continue;
        }
        if(l>0)
        {
            if(a[i][l]>(l-1)/2)
            {
                int v = l/2;
                v*=-1;
                for(int j =0; j<l;j++)
                    a[i][j] = v++;
            }else
            {
                for(int j = l-1;j>=0;j--)
                    a[i][j] = a[i][j+1]-1;
            }
        }
        int prev = a[i][l];
        while(l<a[i].size()-1)
        {
            int r = l+1;
            while(r< a[i].size() && a[i][r]==inf) r++;

            int count = r-l-1;

            if(r==a[i].size())
            {
                if(prev< -(count-1)/2)
                {
                    int v = count/2;
                    for(int j=a[i].size()-1;j>l;j--)
                        a[i][j]=v--;
                }else
                {
                    for(int j=l+1;j<a[i].size();j++)
                        a[i][j]=a[i][j-1]+1;
                }
                break;
            }
            count/=2;
            if(prev + r-l >a[i][r]) {cout <<"Incorrect sequence"; return 0;}

            if(prev>= - count)
            {
                for(int j = l+1;j<=r-1;j++)
                    a[i][j] = a[i][j-1]+1;
            }else
            if(a[i][r]<=count)
            {
                for(int j = r-1;j>l;j--)
                    a[i][j] = a[i][j+1]-1;
            }else
            {
                int v = -count;
                for(int j=l+1;j<=r-1;j++)
                    a[i][j] = v++;
            }
            l=r;
            prev = a[i][r];
        }

    }


    int x=0;
    int y=0;
    for(int i=0;i<n;i++)
    {
        cout<<a[x][y]<<" ";
        x++;
        if(x==k) {x=0; y++;}
    }

    return 0;
}
