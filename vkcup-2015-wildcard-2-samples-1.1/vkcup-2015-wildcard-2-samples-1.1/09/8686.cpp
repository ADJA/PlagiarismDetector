#include <cstdio>
#include <cstdio>
#include <cstdlib>
#include <vector>
#include <cmath>
#include <iostream>
#include <algorithm>

using namespace std;

typedef long long ll;
typedef unsigned long long ull;

const int maxn = 5;
const int maxm = 20;

int n, nn, m;
int lines[maxn], columns[maxm];

int matrix[1 << maxn][1 << maxn][maxn];
int cntBlocks[1 << maxn];
bool f[21][1 << maxn][11][11][11][11][11];
char p[21][1 << maxn][11][11][11][11][11];

char res[maxn + 1][maxm + 1];

void calcMatrix() {
    for (int x = 0; x < (1 << maxn); x++)
        for (int y = 0; y < (1 << maxn); y++)
            for (int i = 0; i < maxn; i++)
                if ((x & (1 << i)) == 0 && (y & (1 << i))) matrix[x][y][i] = -1;
}

void calcCntBlocks() {
    for (int x = 0; x < (1 << maxn); x++)
        for (int i = 0; i < maxn; i++) {
            bool b1 = (x & (1 << i));
            bool b2 = (i - 1 >= 0 ? (x & (1 << (i - 1))) : 0);
            if (!b2 && b1) cntBlocks[x]++;
        }
}

int main() {
    //freopen("input.txt", "r", stdin);
    ios_base::sync_with_stdio(0);

    cin >> n >> m;

    for (int i = 0; i < n; i++)
        cin >> lines[i];

    for (int i = 0; i < m; i++)
        cin >> columns[i];

    nn = n;

    calcMatrix();
    calcCntBlocks();

    f[0][0][lines[0]][lines[1]][lines[2]][lines[3]][lines[4]] = true;

    for (int j = 0; j < m; j++) {
        for (int x = 0; x < (1 << n); x++) {
            for (int a = 0; a <= 10; a++)
                for (int b = 0; b <= 10; b++)
                    for (int c = 0; c <= 10; c++)
                        for (int d = 0; d <= 10; d++)
                            for (int e = 0; e <= 10; e++) {
                                if (!f[j][x][a][b][c][d][e]) continue;
                                for (int y = 0; y < (1 << n); y++) {
                                    if (cntBlocks[y] != columns[j]) continue;
                                    int na, nb, nc, nd, ne;
                                    int delta[maxn];
                                    for (int it = 0; it < maxn; it++)
                                        delta[it] = matrix[x][y][it];
                                    na = a + delta[0];
                                    nb = b + delta[1];
                                    nc = c + delta[2];
                                    nd = d + delta[3];
                                    ne = e + delta[4];
                                    if (min(na, min(nb, min(nc, min(nd, ne)))) < 0) continue;
                                    if (f[j + 1][y][na][nb][nc][nd][ne] == false) {
                                        f[j + 1][y][na][nb][nc][nd][ne] = true;
                                        p[j + 1][y][na][nb][nc][nd][ne] = x;
                                    }
                                }
                            }
        }
    }

    int j = m, a, b, c, d, e;
    a = b = c = d = e = 0;
    int mask = 0;

    for (int y = 0; y < (1 << n); y++)
        if (f[m][y][a][b][c][d][e]) {
            mask = y;
        }

    while (j != 0) {
        int pa, pb, pc, pd, pe;
        int x = p[j][mask][a][b][c][d][e];
        int delta[5];
        for (int it = 0; it < maxn; it++)
            delta[it] = -matrix[x][mask][it];
        pa = a + delta[0];
        pb = b + delta[1];
        pc = c + delta[2];
        pd = d + delta[3];
        pe = e + delta[4];
        for (int it = 0; it < maxn; it++)
            res[it][j - 1] = ((mask & (1 << it)) ? '*' : '.');
        mask = x;
        a = pa, b = pb, c = pc, d = pd, e = pe;
        j--;
    }

    n = nn;

    for (int i = 0; i < n; i++)
        cout << res[i] << "\n";

    //double zzz = (sizeof(p) + sizeof(f)) / 1024 / 1024;

    //cerr << zzz << endl;

    return 0;
}
