#include <iostream>
#include <math.h>
#include <string.h>
#include <string>
#include <cmath>
#include <stdio.h>
#include <vector>
#include <map>
#include <list>
#include <queue>
#include <functional>
#include <algorithm>
#include <bitset>
#include <set>
#include <stack>
#include <limits>
#include <sstream>
#include <ctime> 
#define endl '\n'
#pragma warning (disable : 4996)

using namespace std;

#define lli long long int
#define ull unsigned long long int
#define MP make_pair

const int N = (int)(2e6 + 20);
const int L = 20;
const lli M = 1000000007;
const double E = 1e-7;

vector<int> path;

pair<int, int> startFrom;

lli n, m, ans = 0, d[N];

void check(int start, int dir)
{
    vector<int> p(m);
    lli dist = 0;
    lli last = start;
    for (int i = 0; i < m; ++i) {
        int cur = start;
        p[i] = start;
        dist += max(d[start] - d[last], d[last] - d[start]);
        if (start + dir == -1) {
            dir = 1;
            start = 1;
        } else if (start + dir == n) {
            dir = -1;
            start = n - 2;
        } else start += dir;
        last = cur;
    }
    sort(p.begin(), p.end());
    if (p == path) {
        if (startFrom.first >= 0 && ans != dist) {
            cout << -1;
            exit(0);
        }
        startFrom.first = start;
        startFrom.second = dir;
        ans = dist;
    }
}

int cnt[N];

int main()
{
    ios_base::sync_with_stdio(0);
#ifdef FILE_IO
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
#endif      
    startFrom.first = -1;
    cin >> n;
    for (int i = 0; i < n; ++i) cin >> d[i];
    cin >> m;
    for (int i = 0; i < m; ++i) {
        int t;
        cin >> t;
        t--;
        path.push_back(t);
        cnt[t]++;
    }
    if (n == 1) cout << 0;
    else {
        check(0, 1); check(0, -1);
        check(n-1, 1); check(n-1, -1);
        for (int i = 1; i < n - 1; ++i) {
            if (cnt[i] && ((cnt[i] - cnt[i - 1]) || (cnt[i] - cnt[i + 1]))) {
                check(i, 1); check(i, -1);
            }
        }
    }
    if (startFrom.first >= 0)
        cout << ans;
    else
        cout << -1;
}