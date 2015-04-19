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

const int maxn = 200500;

const ull T = (ull)1e9 + 7;
//const ull T = 10;

ull t[maxn], needHash;
int n, m;
ll a[maxn];
vector<ll> answer;

struct state {
    int v, dir;
    state() {}
    state(int v, int dir) : v(v), dir(dir) {}
    void next() {
        if (v + dir < 1 || v + dir > n) {
            dir *= -1;
        }
        v += dir;
    }
};

void calcT() {
    t[0] = 1;
    for (int i = 1; i < maxn; i++)
        t[i] = t[i - 1] * T;
}

int main() {
    //freopen("input.txt", "r", stdin);
    ios_base::sync_with_stdio(0);

    calcT();

    cin >> n;

    for (int i = 1; i <= n; i++) {
        cin >> a[i];
    }

    calcT();

    cin >> m;

    for (int i = 1; i <= m; i++) {
        int idx;
        cin >> idx;
        needHash += t[idx];
    }

    state L = state(1, 1);
    state R = L;

    ull curH = t[1];
    ll curD = 0;

    int it = m - 1;

    while (it--) {
        state tmp = R;
        R.next();
        curH += t[R.v];
        curD += abs(a[tmp.v] - a[R.v]);
    }

    if (curH == needHash) {
        answer.push_back(curD);
    }

    for (int i = 2; i <= n * 2; i++) {
        state tmp = L;
        curH -= t[L.v];
        L.next();
        curD -= abs(a[L.v] - a[tmp.v]);
        tmp = R;
        R.next();
        curH += t[R.v];
        curD += abs(a[R.v] - a[tmp.v]);
        if (curH == needHash) answer.push_back(curD);
    }

    sort(answer.begin(), answer.end());
    answer.erase(unique(answer.begin(), answer.end()), answer.end());

    if (answer.size() != 1) cout << "-1\n";
    else cout << answer.back() << "\n";

    return 0;
}
