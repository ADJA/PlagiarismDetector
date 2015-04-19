#include <stdio.h>
#include <iostream>
#include <string.h>
using namespace std;
#define fi first
#define se second
#define pb push_back
#define mp make_pair
typedef double du;
typedef long long ll;

ll f[104][2];
char s[104];

void solve(){
    int n, i;
    ll ans = 0;
    scanf("%s", s);
    n = strlen(s);
    for(i = 0; i < n; i++)
        s[i] -= 'A';
    s[n] = s[0];
    memset(f, 0, sizeof f);

    f[0][0] = 1;
    for(i = 1; i <= n; i++){
        if(s[i-1]){
            if(s[i]){
                f[i][0] += f[i-1][1];
                f[i][1] += f[i-1][1];
            }
            else{
                f[i][1] += f[i-1][0];
                f[i][0] += f[i-1][1];
            }
        }
        else{
            if(s[i]){
                f[i][0] += f[i-1][0];
                f[i][0] += f[i-1][1];
                f[i][1] += f[i-1][1];
            }
            else{
                f[i][0] += f[i-1][0];
                f[i][0] += f[i-1][1];
            }
        }
    }
    ans += f[n][0];
    memset(f, 0, sizeof f);
    f[0][1] = 1;
    for(i = 1; i <= n; i++){
        if(s[i-1]){
            if(s[i]){
                f[i][0] += f[i-1][1];
                f[i][1] += f[i-1][1];
            }
            else{
                f[i][1] += f[i-1][0];
                f[i][0] += f[i-1][1];
            }
        }
        else{
            if(s[i]){
                f[i][0] += f[i-1][0];
                f[i][0] += f[i-1][1];
                f[i][1] += f[i-1][1];
            }
            else{
                f[i][0] += f[i-1][0];
                f[i][0] += f[i-1][1];
            }
        }
    }
    ans += f[n][1];
    cout<<ans<<endl;
}

int main(){
    solve();
    return 0;
}