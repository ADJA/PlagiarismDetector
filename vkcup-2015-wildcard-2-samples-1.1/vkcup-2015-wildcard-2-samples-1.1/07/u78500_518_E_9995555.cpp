#include <bits/stdc++.h>
using LL = long long;

const int INF = 0x3f3f3f3f;
const int N = 100000 + 5;
int A[N],B[N];
int n,K;

bool calc(int tot) {
    for (int i = 0,j = 1; i < tot && j < tot; i = j ++ ) {
        while (j < tot && B[j] == -INF) ++ j;
        if (B[j] - B[i] < j - i) return false;
        int count = j - i - 1;
        if (count == 0) continue;
        B[count / 2 + i + 1] = 0;
        for (int k = count / 2 + i + 1 - 1; k > i; -- k) {
            B[k] = B[k+1] - 1;
        }
        for (int k = count / 2 + i + 1 + 1; k < j; ++ k) {
            B[k] = B[k-1] + 1;
        }
        if (B[i] >= B[i+1]) {
            int delta = B[i]+1 - B[i+1];
            for (int k = i+1; k < j; ++ k) {
                B[k] += delta;
            }
        }
        if (B[j-1] >= B[j]) {
            int delta = B[j-1] - (B[j] - 1);
            for (int k = i + 1; k < j; ++ k) {
                B[k] -= delta;
            }
        }
    }
    return true;
}

bool solve() {
    for (int i = 0; i < K; ++ i) {
        int tot = 0;
        B[tot++] = -INF+1;
        for (int j = i; j < n; j += K) {
            B[tot++] = A[j];
        }
        B[tot++] = INF-1;
        if (!calc(tot)) return false;
        for (int j = 1; j < tot-1; ++ j) {
            int p = (j-1) * K + i;
            A[p] = B[j];
        }
    }
    return true;
}

int main() {
    scanf("%d%d",&n,&K);
    for (int i = 0; i < n; ++ i) {
        char str[20];
        scanf("%s",str);
        if (str[0] == '?') {
            A[i] = -INF;
        } else {
            A[i] = atoi(str);
        }
    }
    if (!solve()) {
        puts("Incorrect sequence");
    } else {
        for (int i = 0; i < n; ++ i) {
            printf("%d%c",A[i]," \n"[i==n-1]);
        }
    }
    return 0;
}
