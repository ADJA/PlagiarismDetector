#include <cstdio>
#include <cstdlib>
#include <algorithm>
#include <iostream>
#include <cstring>
using namespace std;
#define wenhao 2100000000
#define N 101111
typedef long long LL;
inline int geti() {
    static char pp;
    static int res;
    pp = getchar();
    while (pp < '0' || pp > '9') pp = getchar();
    res = 0;
    while (pp >= '0' && pp < '9')
        res = res * 10 - '0' + pp, pp = getchar();
    return res;
}
void Fail() {
    printf("Incorrect sequence\n");
    exit(0);
}
char fuck[1111];
int n, k, tot, Siz;
int sl[N], sr[N], haha[N], p[N];
void orzvfk(int siz, int l, int r) {
    Siz = siz;
    int nr = siz / 2, nl = nr - siz + 1;
    if (l > nl) {
        nr += l - nl;
        nl = l;
    }
    else if (r < nr){
        nl -= nr - r;
        nr = r;
    }
    for (int i = 1; i <= siz; i++)
        haha[i] = nl++;
}
void Solve() {
    int toc = 0;
    for (int i = 1; i <= tot; i++) {
        if (sl[i] != wenhao)
            sr[++toc] = i;
    }
    if (toc == 0) {
        orzvfk(tot, -wenhao, wenhao);
        for (int i = 1; i <= tot; i++)
            sl[i] = haha[i];
        return;
    }
    for (int i = 2; i <= toc; i++)
        if (sl[sr[i]] - sl[sr[i - 1]] < sr[i] - sr[i - 1])
            Fail();
    orzvfk(sr[1] - 1, -wenhao, sl[sr[1]] - 1);
    for (int i = 1; i <= Siz; i++)
        sl[i] = haha[i];
    for (int i = 2; i <= toc; i++) {
        orzvfk(sr[i]-sr[i-1]-1, sl[sr[i-1]]+1,sl[sr[i]]-1);
        for (int j = 1; j <= Siz; j++)
            sl[sr[i-1] + j] = haha[j];
    }
    orzvfk(tot - sr[toc], sl[sr[toc]] + 1, wenhao);
    for (int i = 1; i <= Siz; i++)
        sl[sr[toc] + i] = haha[i];
}
int main() {
    scanf("%d%d", &n, &k);
    for (int i = 1; i <= n; i++) {
        scanf("%s", fuck);
        if (fuck[0] == '?')
            p[i] = wenhao;
        else
            p[i] = atoi(fuck);
    }
    for (int i = 1; i <= k; i++) {
        tot = 0;
        for (int j = i; j <= n; j += k)
            sl[++tot] = p[j];
        Solve();
        tot = 0;
        for (int j = i; j <= n; j += k)
            p[j] = sl[++tot];
    }
    for (int i = 1; i <= n; i++)
        printf("%d ", p[i]);
    return 0;
}