#include <cstdio>
#include <iostream>
#include <cstring>
#include <cmath>
#include <string>
#include <vector>
#include <map>
#include <set>
#include <queue>
#include <deque>
#include <ctime>
#include <cstdlib>
#include <sstream>
#include <bitset>
#define zero(a) (abs(a)<eps)
#define lowbit(a) ((a)&(-(a)))
#define abs(a) ((a)<0?(-(a)):(a))
#define cj(x1,y1,x2,y2) ((x1)*(y2)-(x2)*(y1))
#define dj(x1,y1,x2,y2) ((x1)*(x2)+(y1)*(y2))
#define dis(x1,y1,x2,y2) (((x2)-(x1))*((x2)-(x1))+((y2)-(y1))*((y2)-(y1)))
const double pi = acos(-1);
const double E = 2.7182818284590452353602874713527;
const double eps = 1e-9;
const int oo = 1000000000;
const int mod = 1000000007;
using namespace std;

vector<int> l[5001];
int s[5001],ans[5001];
bool f[5001],g[5001];
int n;

void dfs(int now,int last)
{
   s[now]=1;
   for (int i=0;i<l[now].size();i++)
      if (l[now][i]!=last)
      {
         dfs(l[now][i],now);
         s[now]+=s[l[now][i]];
      }
   if (l[now].size()>1)
   {
      memset(g,0,sizeof(g));
      g[0]=1;
      for (int i=0;i<l[now].size();i++)
         if (l[now][i]!=last)
            for (int j=n-s[l[now][i]];j>=0;j--)
               g[j+s[l[now][i]]]|=g[j];
      for (int i=n-(n-s[now]);i>=0;i--)
          g[i+(n-s[now])]|=g[i];
      for (int i=1;i<n-1;i++)
         f[i]|=g[i];
   }
}

int main()
{
   int o=0;
   cin>>n;
   for (int i=1;i<n;i++)
   {
      int a,b;
      scanf("%d%d",&a,&b);
      l[a].push_back(b);
      l[b].push_back(a);
   }
   dfs(1,0);
   for (int i=1;i<n-1;i++)
      if (f[i])
         ans[++o]=i;
   cout<<o<<endl;
   for (int i=1;i<=o;i++)
      cout<<ans[i]<<' '<<n-ans[i]-1<<endl;
   return 0;
}