#include <stdio.h>
#include <string.h>
#include <stdbool.h>

#define clr(ar) memset(ar, 0, sizeof(ar))
#define read() freopen("lol.txt", "r", stdin)

char str[100][100];
int len[32], adj[32][32];
int n, m, lim, row[5], col[20];
bool visited[20][32][11][11][11][11][11] = {false}, dp[20][32][11][11][11][11][11];

bool F(int j, int lbit, int ar[5]){
    if (ar[0] < 0 || ar[1] < 0 || ar[2] < 0 || ar[3] < 0 || ar[4] < 0) return false;
    if (j == m) return (!ar[0] && !ar[1] && !ar[2] && !ar[3] && !ar[4]);
    if (visited[j][lbit][ar[0]][ar[1]][ar[2]][ar[3]][ar[4]]) return dp[j][lbit][ar[0]][ar[1]][ar[2]][ar[3]][ar[4]];

    bool res = false;
    int i, k, bitmask, cur = col[j], T[5] = {0};

    for (k = 0; k < len[cur]; k++){
        bitmask = adj[cur][k];
        T[0] = ar[0], T[1] = ar[1], T[2] = ar[2], T[3] = ar[3], T[4] = ar[4];

        for (i = 0; i < n; i++){
            if ((bitmask & (1 << i)) && !(lbit & (1 << i))) T[i]--;
        }

        res |= F(j + 1, bitmask, T);
        if (res) break;
    }

    visited[j][lbit][ar[0]][ar[1]][ar[2]][ar[3]][ar[4]] = true;
    return (dp[j][lbit][ar[0]][ar[1]][ar[2]][ar[3]][ar[4]] = res);
}

void backtrack(int j, int lbit, int ar[5]){
    bool res = false;
    int i, k, bitmask, cur = col[j], T[5] = {0};

    if (j){
        for (i = 0; i < n; i++){
            if (lbit & (1 << i)) str[i][j - 1] = '*';
            else str[i][j - 1] = '.';
        }

        if (j == m){
            for (i = 0; i < n; i++) str[i][j] = 0;
            return;
        }
    }

    for (k = 0; k < len[cur]; k++){
        bitmask = adj[cur][k];
        T[0] = ar[0], T[1] = ar[1], T[2] = ar[2], T[3] = ar[3], T[4] = ar[4];

        for (i = 0; i < n; i++){
            if ((bitmask & (1 << i)) && !(lbit & (1 << i))) T[i]--;
        }

        res |= F(j + 1, bitmask, T);
        if (res){
            backtrack(j + 1, bitmask, T);
            return;
        }
    }
}

int main(){
    int i, j, k, l, c, x, bitmask, ar[5] = {0};

    while (scanf("%d %d", &n, &m) != EOF){
        for (i = 0; i < n; i++) scanf("%d", &row[i]);
        for (i = 0; i < m; i++) scanf("%d", &col[i]);

        clr(len);
        lim = (1 << n) - 1;
        for (bitmask = 0; bitmask <= lim; bitmask++){
            c = 0, l = 0;
            for (i = 0; i < 5; i++){
                if ((bitmask & (1 << i)) && !l) c++;
                if (bitmask & (1 << i)) l = 1;
                else l = 0;
            }

            adj[c][len[c]++] = bitmask;
        }

        clr(ar);
        for (i = 0; i < n; i++) ar[i] = row[i];
        backtrack(0, 0, ar);
        for (i = 0; i < n; i++) puts(str[i]);
    }
    return 0;
}
