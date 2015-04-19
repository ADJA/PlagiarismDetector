/*************************************************************************
    > File Name: E.cpp
    > Author: wmg_1001
    > Mail: wmg_1007@163.com 
    > Created Time: 2015年02月26日 星期四 01时36分21秒
 ************************************************************************/

#include <iostream>
#include <fstream>
#include <cstring>
#include <cmath>
#include <cstdio>
#include <cstdlib>
#include <climits>
#include <ctime>
#include <iomanip>
#include <algorithm>
#include <deque>
#include <queue>
#include <map>
#include <set>
using namespace std;

const int inf = INT_MAX;
const int iinf = INT_MIN;

int n, K;
int a[100005];

int input_num(void) {
    char ch;
    ch = getchar();
    while ((ch < '0' || ch > '9') && ch != '?' && ch != '-') ch = getchar();
    if (ch == '?') return inf;
    int dir = 1;
    if (ch == '-') {
        dir = -1;
        ch = getchar();
    }
    int re = 0;
    while (ch >= '0' && ch <= '9') {
        re *= 10;
        re += ch - '0';
        ch = getchar();
    }
    return re * dir;
}

int b[100005];
int c[100005];

void ppp(int ll, int rr, int tot) {
    if (ll >= 0) {
        c[0] = ll + 1;
        for (int i = 1; i < tot; i++) c[i] = c[i - 1] + 1;
        return ;
    }
    if (rr <= 0) {
        c[tot - 1] = rr - 1;
        for (int i = tot - 2; i >= 0; i--) c[i] = c[i + 1] - 1;
        return ;
    }
    c[0] = 0;
    int tl, tr;
    tl = -1, tr = 1;
    for (int i = 1; i < tot; i++) {
        if (tl <= ll) {
            c[i] = tr++;
            continue;
        }
        if (tr >= rr) {
            c[i] = tl--;
            continue;
        }
        if (-tl < tr) {
            c[i] = tl;
            tl--;
        } else {
            c[i] = tr;
            tr++;
        }
    }
    sort(c, c + tot);
}

int main() {
    cin >> n >> K;
    for (int i = 0; i < n; i++) a[i] = input_num();
    for (int i = 0; i < K; i++) {
        int tot = 0, cnt = 0;
        for (int j = i; j < n; j += K) {
            cnt++;
            if (a[j] != inf) b[tot++] = j;
        }
        if (tot == 0) {
            ppp(iinf, inf, cnt);
            for (int j = i, tmp = 0; j < n; j += K, tmp++) a[j] = c[tmp];
            continue;
        }
        if (b[0] > i) {
            ppp(iinf, a[b[0]], (b[0] - i) / K);
            for (int j = i, tmp = 0; j < b[0]; j += K, tmp++) a[j] = c[tmp];
        }
        if (b[tot - 1] + K < n) {
            ppp(a[b[tot - 1]], inf, cnt - 1 - (b[tot - 1] - i) / K);
            for (int j = b[tot - 1] + K, tmp = 0; j < n; j += K, tmp++) a[j] = c[tmp];
        }
        for (int j = 1; j < tot; j++) {
            if ((b[j] - b[j - 1]) / K > a[b[j]] - a[b[j - 1]]) {
                cout << "Incorrect sequence" << endl;
                return 0;
            }
            if ((b[j] - b[j - 1]) / K == 1) continue;
            ppp(a[b[j - 1]], a[b[j]], (b[j] - b[j - 1]) / K - 1);
            for (int k = b[j - 1] + K, tmp = 0; k < b[j]; k += K, tmp++)
                a[k] = c[tmp];
        }
    }
    for (int i = 0; i < n - 1; i++) printf("%d ", a[i]);
    cout << a[n - 1] << endl;
    return 0;
}

