#include <cstdio>
#include <iostream>
#include <algorithm>
#include <cstring>
#include <complex>
#include <vector>
#include <string>
#include <queue>
#include <stack>
#include <deque>
#include <map>
#include <set>
using namespace std;

typedef pair <int, int> ii;
typedef long long ll;

#define X first
#define Y second
#define REP(i, n) for(int i = 0; i < int(n); i ++)
#define FOR(i, a, b) for(int i = (a); i <= (b); i ++)

const int N = 200032;

int n, m, a[32], b[32];
char f[22][11][11][11][11][11][32];
char s[100][100];


int main(){
    //freopen("input.txt", "r", stdin);
    scanf("%d %d", &n, &m);
    FOR(i, 1, n) scanf("%d", a + i);
    FOR(i, 1, m) scanf("%d", b + i);
    int nn = n;
    n = 5;
    memset(f, 0xff, sizeof f);
    f[0][0][0][0][0][0][0] = 0;
    vector <int> could;
    could.push_back(0);
    for(int i = 1; i <= m+1; i ++){
        vector <int> can;
        for(int j = 0; j < 32; j ++){
            int cnt = 0;
            for(int k = 1; k < 7; k ++) if((j&1<<k-1) && !(j&1<<k)) cnt ++;
            if(cnt == b[i]){
                can.push_back(j);

            }
        }
        FOR(i1, 0, i>>1)
        FOR(i2, 0, i>>1)
        FOR(i3, 0, i>>1)
        FOR(i4, 0, i>>1)
        FOR(i5, 0, i>>1)
        REP(t, could.size()){int mask = could[t]; if(f[i-1][i1][i2][i3][i4][i5][mask] != -1){
            //printf("%d %d %d %d %d %d %d\n", i-1, i1, i2, i3, i4, i5, mask);
            REP(j, can.size()){
                int nmask = can[j];
                int j1 = i1, j2 = i2, j3 = i3, j4 = i4, j5 = i5;
                REP(l, 5) if(!(mask&1<<l) && (nmask&1<<l)){
                    if(l == 0) j1 ++;
                    else if(l == 1) j2 ++;
                    else if(l == 2) j3 ++;
                    else if(l == 3) j4 ++;
                    else if(l == 4) j5 ++;
                }
                if(j1 <= a[1] && j2 <= a[2] && j3 <= a[3] && j4 <= a[4] && j5 <= a[5])
                   f[i][j1][j2][j3][j4][j5][nmask] = mask;
            }
        } }
        could = can;
    }

    int i1 = a[1], i2 = a[2], i3 = a[3], i4 = a[4], i5 = a[5], i = m + 1, mask = 0;
    while(i > 1){
        int nmask = f[i][i1][i2][i3][i4][i5][mask];

        REP(j, 5) if(nmask & 1 << j) s[j][i-2] = '*';
        else s[j][i-2] = '.';
        REP(j, 5) if(!(nmask & 1 << j) && (mask & 1 << j)){
            if(j == 0) i1 --;
            else if(j == 1) i2 --;
            else if(j == 2) i3 --;
            else if(j == 3) i4 --;
            else if(j == 4) i5 --;
        }
        i--;
        mask = nmask;
    }
    REP(i, nn) printf("%s\n", s[i]);
    return 0;
}
