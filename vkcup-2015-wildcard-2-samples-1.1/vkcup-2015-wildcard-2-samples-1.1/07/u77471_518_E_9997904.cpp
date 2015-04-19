#include<bits/stdc++.h>

#define s(a) scanf("%d",&a)
#define ss(a) scanf("%s",a)

#define MP           make_pair
#define PB           push_back
#define REP(i, n)    for(int i = 0; i < n; i++)
#define INC(i, a, b) for(int i = a; i <= b; i++)
#define DEC(i, a, b) for(int i = a; i >= b; i--)
#define CLEAR(a)     memset(a, 0, sizeof a)

using namespace std;

typedef long long          LL;
typedef unsigned long long ULL;
typedef vector<int>        VI;
typedef pair<int, int>     II;
typedef vector<II>         VII;

int temp[100005];
bool f2[100005];

const int WRONG = 2e9+1;
inline int findstart(int f,int l,int sz)
{
      int m,be=f,ed=l-sz+1;
      if(ed<be)
            return WRONG;
      return max(be,min(-sz/2,ed));
}
inline bool fun(int len)
{
      int l = 2e9;
      DEC(i,len-1,0)
      {
            //printf("Here\n");
            if(!f2[i])
            {
                  if(temp[i]>l)
                        return false;
                  l = temp[i]-1;
                  continue;
            }
            int sz = 0;
            while(i>=0 && f2[i])
            {
                  i--;
                  sz++;
            }
            int start;
            if(i>=0)
                  start = findstart(temp[i]+1,l,sz);
            else
                  start = findstart(-2e9,l,sz);
            //printf("Returned %d\n",start);
            if(start==WRONG)
                  return false;
            i++;
            INC(j,i,i+sz-1)
                  temp[j] = start++;
      }
      return true;
}

int inp[100005];
bool f1[100005];
int main()
{
      int n,k;
      char str[100];
      s(n);s(k);
      CLEAR(f1);
      REP(i,n)
      {
            ss(str);
            if(str[0]=='?')
            {
                  f1[i] = true;
                  continue;
            }
            int num=0;
            for(int  j=0;str[j]!='\0';j++)
            {
                  if(str[j]=='-')
                        continue;
                  num = num*10 + (str[j]-'0');
            }
            if(str[0]=='-')
                  num = -num;
            inp[i] = num;
      }
      REP(i,k)
      {
            int len = 0,j=i;
            while(j<n)
            {
                  temp[len++] = inp[j];
                  if(f1[j])
                        f2[len-1] = true;
                  else f2[len-1]=false;
                  j+=k;
            }
            if(!fun(len))
            {
                  printf("Incorrect sequence\n");
                  return 0;
            }
            len = 0;
            j=i;
            while(j<n)
            {
                  inp[j] = temp[len++];
                  j+=k;
            }
      }
      REP(i,n)
            printf("%d ",inp[i]);
      printf("\n");
      return 0;
}
