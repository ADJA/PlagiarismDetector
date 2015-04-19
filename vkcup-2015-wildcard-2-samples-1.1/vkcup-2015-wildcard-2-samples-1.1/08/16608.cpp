#include <iostream>
#include <cstdio>
#include <algorithm>
#include <cstdlib>
#include <vector>
#include <set>
#include <map>
#include <cassert>
#include <ctime> 
#include <cmath>
#include <cstdio>
#include <string>
#include <cstring>
#include <queue>
using namespace std;

#define f first
#define s second
#define pb push_back
#define vi vector<int>
#define all(v) (v).begin(), (v).end()
#define sz(v) (int)(v).size()
#define f0(a) memset(a, 0, sizeof(a))
#define ll long long
#define mp make_pair
#define pii pair<int, int>
const int maxn = (int)4e6;

int n, m;
int cnt[maxn], d[maxn];
int  head, tail;
int q[maxn];

int main() {
    scanf("%d", &n);
    for (int i = 0; i < n; ++i) {
        scanf("%d", &d[i]);
    }
    scanf("%d", &m);
    for (int i = 0; i < m; ++i) {
        int x;
        scanf("%d", &x); --x;
        cnt[x]++;
    }


    if (m == 1) {
        puts("0");
        return 0;
    }

    int zero = 0;

    for (int i = 0; i < n; ++i)
        if (cnt[i] == 0) zero++;


    int c = 0, cd = 1;
    ll curlen = 0;
    set<ll> S;

    q[tail++] = 0;
    if (cnt[c] == 0) zero--;
    cnt[c]--;
    if (cnt[c] == 0) zero++;    

    for (int i = 0; S.size() < 2 && i < 2*n + 2*m; ++i) {

        if (tail - head == m) {
            curlen -= abs(d[q[head]] - d[q[head+1]]);

            if (cnt[q[head]] == 0) zero--;
            cnt[q[head]]++;
            if (cnt[q[head]] == 0) zero++;
            head++;

        }

        if (c == n - 1) 
            cd = -1;

        if (c == 0)
            cd = 1;

        curlen += abs(d[c + cd] - d[c]);
        c += cd;
        q[tail++] = c;

        if (cnt[c] == 0) zero--;
        cnt[c]--;
        if (cnt[c] == 0) zero++;    

        if (tail - head == m && zero == n) {
            S.insert(curlen);
        }
    }
    if (S.size() != 1) {
        puts("-1");
    } else {
        cout << *S.begin() << endl;
    }


    return 0;
}
