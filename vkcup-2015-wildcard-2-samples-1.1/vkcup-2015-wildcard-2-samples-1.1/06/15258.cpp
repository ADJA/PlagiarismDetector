#include <cmath>
#include <cstdio>
#include <cstdlib>
#include <iostream>
#include <algorithm>
#include <string>
#include <cstring>
#include <vector>
#include <map>
#include <set>
using namespace std;
long long S,sum,B;
int R[2000005],A[2000005],n,Q,i,MIN,X,L,now,ans,ANS;
int main()
{
    scanf("%d%d",&n,&Q);
    for (i=1; i<=n; i++) {scanf("%d",&A[i]);S+=A[i];}
    for (i=n+1; i<n+n; i++) A[i]=A[i-n];
    while (Q--)
    {
        cin>>B; sum=0; L=1;
        if (B>=S) {puts("1"); continue;}
        for (i=1; i<n+n; i++)
        {
            sum+=A[i];
            while (sum>B) {R[L]=i-1; sum-=A[L]; L++;}
        }
        for (i=L; i<n+n; i++) R[i]=n+n-1; MIN=n;
        for (i=1; i<=n; i++) if (R[i]-i+1<=MIN && R[i-1]!=R[i]) {MIN=R[i]-i+1; X=i;}
        ans=n;
        for (i=X; i<=R[X]; i++)
        {
            now=i; if (now>n) now-=n;ANS=0; sum=0;
            while (1)
            {
                ANS++;sum+=R[now]-now+1;
                now=R[now]+1;
                if (now>n) now-=n;
                if (sum>=n) break;
            }
            ans=min(ans,ANS);
        }
        printf("%d\n",ans);
    }
    return 0;
}
