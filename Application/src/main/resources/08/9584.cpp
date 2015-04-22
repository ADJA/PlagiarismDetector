#include <bits/stdc++.h>

using namespace std;

const int MN = 1000111;

long long a[MN];
long long dist(int u, int v) {
    if (u < v) return a[v] - a[u];
    else return a[u] - a[v];
}

int n, m, b[MN], cnt[MN], bad, id[MN];
set<long long> res;

void init() {
    for (int i = 1; i <= n; i++) id[i] = i;

    int dir = -1;
    for (int i = n + 1; i <= MN - 1; i++) {
        id[i] = id[i-1] + dir;
        if (id[i] == 1) dir = 1;
        else if (id[i] == n) dir = -1;
    }

    for (int i = n + 1; i <= MN - 1; i++) {
        a[i] = a[i-1] + dist(id[i], id[i-1]);
    }
}

void reduce(int u) {
    if (cnt[u] == 0) ++bad;
    --cnt[u];
    if (cnt[u] == 0) --bad;
}

void add(int u) {
    if (cnt[u] == 0) ++bad;
    ++cnt[u];
    if (cnt[u] == 0) --bad;
}

int main() {
    while (scanf("%d", &n) == 1) {
        for (int i = 1; i <= n; i++) scanf("%d", &a[i]);
        init();

        memset(cnt, 0, sizeof cnt);
        scanf("%d", &m);
        for (int i = 1; i <= m; i++) {
            scanf("%d", &b[i]);
            cnt[b[i]]++;
        }
        res.clear();

        bad = 0;
        for (int i = 1; i <= n; i++) if (cnt[i]) ++bad;

        int from = 1, to = m;
        for (int i = 1; i <= m; i++) {
            reduce(id[i]);
        }

        if (bad == 0) res.insert(a[to] - a[from]);
        for (int i = 2; i <= n + n + n; i++) {
            add(id[from]);
            ++from;
            ++to;
            reduce(id[to]);

            if (bad == 0) res.insert(a[to] - a[from]);
        }

        if (res.size() == 1) cout << *res.begin() << endl;
        else cout << -1 << endl;
    }
    return 0;
}
