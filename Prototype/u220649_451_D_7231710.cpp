#include <algorithm>
#include <queue>
#include <iostream>
#include <vector>
#include <deque>
#include <cstdio>
#include <cstring>
#include <cctype>
#include <ctime>
#include <cmath>
#include <set>
#include <map>
#include <bitset>
#include <stack>
#define pb push_back
#define mp make_pair
#define A first
#define B second
#define clr(a,b) memset(a,b,sizeof(a))
#define rep(i,n) for(int i = 0; i < n; i++)
#define FOR(i,a,b) for(int i = a; i <= b; i++)
using namespace std;

int l;
char ch[110000];

int main()
{
 //   freopen("in.txt","r",stdin);
    while (gets(ch)){
        int l=strlen(ch);
        long long a1=0,cnta2=0,b1=0,cntb2=0;
        long long ans=0;
        long long res=0;

        for (int i=0;i<l;i++)
        {
            if (ch[i]=='a')
            {
                if (i%2)
                {
                       a1++;
                    res+=a1;
                    ans+=cnta2;

                }
                else
                {
                    cnta2++;
                    res+=cnta2;
                    ans+=a1;

                }
            }
            else
            {
                if (i%2)
                {
                    b1++;
                    res+=b1;
                    ans+=cntb2;

                }
                else
                {
                     cntb2++;
                    res+=cntb2;
                    ans+=b1;

                }

            }
        }
        printf("%I64d %I64d\n",ans,res);
    }

    return 0;
}
