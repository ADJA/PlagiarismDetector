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
const int N = 5005;
int n;
vector <int> E[N];
bool f[N];
int size[N];
bool tmp[N][N];

void dfs(int x, int fa) {
    memset(tmp[x], 0, sizeof(tmp[x]));
    tmp[x][0] = 1;
    size[x] = 1;
    foreach (it, E[x]) {
        int y = *it;
        if (y == fa) continue;
        dfs(y, x);
        size[x] += size[y];
        for (int j = n; j >= 0; j--) {
            if (tmp[x][j]) {
                tmp[x][j + size[y]] = 1;
            }
        }
    }
    for (int j = n; j >= 0; j--) {
        if (tmp[x][j]) {
            tmp[x][j + n - size[x]] = 1;
        }
    }
    for (int j = 0; j <= n; j++)
        f[j] |= tmp[x][j];
}


int main() {
    scanf("%d", &n);
    for (int i = 1; i < n; i++) {
        int x, y;
        scanf("%d%d", &x, &y);
        E[x].push_back(y);
        E[y].push_back(x);
    }
    dfs(1, 0);
    set <int> ret;
    int ans = n - 1;
    for (int i = 1; ans - i >= 1; i++) {
        if (f[i])
        ret.insert(i);
    }
    printf("%d\n", ret.size());
    foreach (it, ret) {
        printf("%d %d\n", *it, ans - *it);
    }
}
