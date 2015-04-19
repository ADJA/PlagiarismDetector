#pragma comment(linker, "/STACK:640000000")
#include<iostream>
#include<cstdio>
#include<cassert>
#include<cstring>
#include<ctime>
#include<cstdlib>
#include<cmath>
#include<string>
#include<sstream>
#include<map>
#include<set>
#include<queue>
#include<stack>
#include<vector>
#include<bitset>
#include<algorithm>

#define pb push_back
#define ppb pop_back
#define mp make_pair
#define all(x) (x).begin(),(x).end()
#define sz(x) (int)(x).size()
#define ll long long
#define bit __builtin_popcountll
#define sqr(x) (x) * (x)
#define forit(it,S) for(__typeof((S).begin()) it = (S).begin(); it != (S).end(); it++)

using namespace std;

typedef pair<int, int> pii;

const double eps = 1e-9;
const double pi = acos(-1.0);

int a[22],b[22];
short dp[21][1 << 5][11][11][11][11][11];
int masks[22][1 << 5],cnt[22];
int id[22],id2[22];
int res[22];

int main() {
    #ifdef LOCAL
    freopen("input.txt","r",stdin);
    freopen("output.txt","w",stdout);
    #endif

    for (int mask = 0; mask < (1 << 5); mask++) {
        int tot = 0;
        for (int j = 0; j < 5; j++) {
            if ((mask & (1 << j)) != 0) {
                if (j == 0 || (mask & (1 << (j - 1))) == 0) {
                    tot++;
                }
            }
        }
        masks[tot][cnt[tot]] = mask;
        cnt[tot]++;
    }

    int n,m; cin >> n >> m;

    for (int i = 0; i < n; i++) {
        cin >> a[i];
    }

    for (int i = 0; i < m; i++) {
        cin >> b[i];
    }

    dp[0][0][0][0][0][0][0] = 1;

    for (int col = 0; col < m; col++) {
        int prev = col == 0 ? 0 : b[col - 1];
        for (int i = 0; i < cnt[prev]; i++) {
            int pmask = masks[prev][i];
            for (id[0] = 0; id[0] <= 10; id[0]++) {
                for (id[1] = 0; id[1] <= 10; id[1]++) {
                    for (id[2] = 0; id[2] <= 10; id[2]++) {
                        for (id[3] = 0; id[3] <= 10; id[3]++) {
                            for (id[4] = 0; id[4] <= 10; id[4]++) if (dp[col][pmask][id[0]][id[1]][id[2]][id[3]][id[4]] & 1) {
                                int cur = b[col];
                                for (int j = 0; j < cnt[cur]; j++) {
                                    int cmask = masks[cur][j];
                                    for (int e = 0; e < 5; e++) {
                                        id2[e] = id[e];
                                        if (((pmask >> e) & 1) == 0 && ((cmask >> e) & 1) != 0) {
                                            id2[e]++;
                                        }
                                    }
                                    dp[col + 1][cmask][id2[0]][id2[1]][id2[2]][id2[3]][id2[4]] = (pmask << 1) | 1;
                                }
                            }
                        }
                    }
                }
            }
        }
    }

    for (int mask = 0; mask < (1 << 5); mask++) {
        if (dp[m][mask][a[0]][a[1]][a[2]][a[3]][a[4]] & 1) {
            for (int i = m; i > 0; i--) {
                int dd = dp[i][mask][a[0]][a[1]][a[2]][a[3]][a[4]] >> 1;
                res[i - 1] = mask;
                for (int j = 0; j < 5; j++) {
                    if ((dd & (1 << j)) == 0 && (mask & (1 << j)) != 0) {
                        a[j]--;
                    }
                }
                mask = dd;
            }
            for (int i = 0; i < n; i++) {
                for (int j = 0; j < m; j++) {
                    cout << ((res[j] & (1 << i)) != 0 ? '*' : '.');
                }
                cout << endl;
            }
            return 0;
        }
    }
    

    return 0;
}
