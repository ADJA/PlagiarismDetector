#include <cstdio>
#include <cstring>
#include <iostream>
#include <cstdlib>
#include <algorithm>
#include <vector>
#include <set>
#include <map>
#include <queue>
#include <cmath>
using namespace std;

#define foreach(it, a) for (__typeof((a).begin()) it = (a).begin(); it != (a).end(); it++)

template <class T> void checkmin(T &t, T x) {
    if (x < t) {
		t = x;
    }
}
template <class T> void checkmax(T &t, T x) {
	if (x > t) {
		t = x;
	}
}
int n;
long long f[105][2][2];
char s[105];
long long ans;

int trans(int x) {
    x = x & 3;
    if (x == 1) x = 2;
    return x;
}

void gao1() {
    memset(f, 0, sizeof(f));
    f[1][0][0] = 1;
//    f[1][1][1] = 1;
//    f[2][2][2] = 1;
//    f[2][3][3] = 1;
    for (int i = 2; i <= n; i++) {
        for (int m1 = 0; m1 < 2; m1++) {
            for (int m2 = 0; m2 < 2; m2++) {
                {
                    if (m2 == s[i - 1]) {
                        f[i][0][0] += f[i - 1][m1][m2];
                    }
                }
                {
                    if (!m1) {
                        if (1 == s[i - 1] ) {
                            f[i][1][0] += f[i - 1][m1][m2];
                        }
                    } else {
                        if (m2 == s[i - 1]) {
                            f[i][1][1] += f[i - 1][m1][m2];
                        }
                    }
                }
            }
        }
    }
    for (int m1 = 0; m1 < 2; m1++) {
        for (int m2 = 0; m2 < 2; m2++) {
            if (m2 == s[n]) ans += f[n][m1][m2];
        }
    }
}

void gao2() {
    memset(f, 0, sizeof(f));
    f[2][0][0] = 1;
    f[2][1][1] = 1;
    for (int i = 3; i <= n; i++) {
        for (int m1 = 0; m1 < 2; m1++) {
            for (int m2 = 0; m2 < 2; m2++) {
                {
                    if (m2 == s[i - 1]) {
                        f[i][0][0] += f[i - 1][m1][m2];
                    }
                }
                {
                    if (!m1) {
                        if (1 == s[i - 1] ) {
                            f[i][1][0] += f[i - 1][m1][m2];
                        }
                    } else {
                        if (m2 == s[i - 1]) {
                            f[i][1][1] += f[i - 1][m1][m2];
                        }
                    }
                }
            }
        }
    }
    for (int m1 = 0; m1 < 2; m1++) {
        for (int m2 = 0; m2 < 2; m2++) {
            if (m1 == 0) {
                if (s[n] && !s[1]) {
                    ans += f[n][m1][m2];
                }
            } else {
                if (m2 == s[n] && s[1] == 1) {
                    ans += f[n][m1][m2];
                }
            }
        }
    }
}

int main() {
    scanf("%s", s + 1);
    n = strlen(s + 1);
    for (int i = 1; i <= n; i++) s[i] = (s[i] == 'B');
    gao1();
    gao2();
    cout << ans << endl;
}
