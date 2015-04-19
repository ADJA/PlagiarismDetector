#include <cstdio>
#include <algorithm>
#include <cstring>
#define FOR(i,s,e) for (int i=(s); i<(e); i++)
#define FOE(i,s,e) for (int i=(s); i<=(e); i++)
#define FOD(i,s,e) for (int i=(s)-1; i>=(e); i--)
#define CLR(a,x) memset(a, x, sizeof(a))
#define LLD long long int
#define N 105
using namespace std;

int n;
LLD dp[N][2], ret = 0;
char s[N];

int main(){
	scanf("%s", s);
	n = strlen(s);

	FOR(k,0,2){
		CLR(dp, 0);
		dp[0][k] = 1;

		int a, b, c, d;

		FOR(i,0,n-1){
			if (s[i] == 'A' && s[i+1] == 'A') a = b = 1, c = d = 0;
			if (s[i] == 'A' && s[i+1] == 'B') a = b = d = 1, c = 0;
			if (s[i] == 'B' && s[i+1] == 'A') b = c = 1, a = d = 0;
			if (s[i] == 'B' && s[i+1] == 'B') b = d = 1, a = c = 0;
						
			dp[i+1][0] = a * dp[i][0] + b * dp[i][1];
			dp[i+1][1] = c * dp[i][0] + d * dp[i][1];			

		}

    	if (k == 1){			
			if (s[n-1] == 'A' && s[0] == 'A') ret += 0;
			if (s[n-1] == 'A' && s[0] == 'B') ret += dp[n-1][1];
			if (s[n-1] == 'B' && s[0] == 'A') ret += dp[n-1][0];
			if (s[n-1] == 'B' && s[0] == 'B') ret += dp[n-1][1];
		}

		if (k == 0){
			if (s[n-1] == 'A' && s[0] == 'A') ret += dp[n-1][0] + dp[n-1][1];
			if (s[n-1] == 'A' && s[0] == 'B') ret += dp[n-1][0] + dp[n-1][1];
			if (s[n-1] == 'B' && s[0] == 'A') ret += dp[n-1][1];
			if (s[n-1] == 'B' && s[0] == 'B') ret += dp[n-1][1];
		}
	}

	printf("%I64d\n", ret);
}
