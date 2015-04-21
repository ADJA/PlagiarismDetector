#include<cstdio>
#include<cstring>
#include<algorithm>
#include<cmath>
using namespace std;
#define N 100005
#define ll __int64
ll max(ll x,ll y){return x>y?x:y;}
ll min(ll x,ll y){return x<y?x:y;}

char str[N];
ll dp[N][4][2];//aa ab ba bb
ll ans1,ans2;

int main()
{
    int T;
    int w;
    scanf("%s",str);
    int len=strlen(str);
    int i;
    for(i=0;str[i];i++)
    {
        if(i!=0)
        {
            if(str[i]=='a')
            {
                dp[i][0][0]+=dp[i-1][0][1]+dp[i-1][1][1];//aa
                dp[i][2][0]+=dp[i-1][2][1]+dp[i-1][3][1];//ba
                dp[i][0][1]+=dp[i-1][0][0]+dp[i-1][1][0];//aa
                dp[i][2][1]+=dp[i-1][2][0]+dp[i-1][3][0];//ba
            }
            else
            {
                dp[i][3][0]+=dp[i-1][2][1]+dp[i-1][3][1];//bb
                dp[i][1][0]+=dp[i-1][0][1]+dp[i-1][1][1];//ab
                dp[i][3][1]+=dp[i-1][2][0]+dp[i-1][3][0];//bb
                dp[i][1][1]+=dp[i-1][0][0]+dp[i-1][1][0];//ab
            }
        }
        if(str[i]=='a')
        {
            dp[i][0][1]++;
        }
        else dp[i][3][1]++;
    }
    for(i=0;i<len;i++)
    {
        ans1+=dp[i][0][0]+dp[i][3][0];
        ans2+=dp[i][0][1]+dp[i][3][1];
    }
    printf("%I64d %I64d\n",ans1,ans2);
    return 0;
}
