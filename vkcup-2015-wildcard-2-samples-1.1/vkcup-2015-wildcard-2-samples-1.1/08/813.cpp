#include <iostream>
#include <iomanip>
#include <cstring>
#include <string>
#include <algorithm>
#include <queue>
#include <map>
#include <deque>
#include <set>
#include <vector>
#include <cstdlib>
#include <ctime>
#include <fstream>

#define pb push_back
#define mp make_pair
#define F first
#define S second

#define foreach(i, c) for (typeof(c.begin()) i = c.begin(); i != c.end(); ++i)

#ifdef LOCAL
#define debug(...) fprintf(stderr, __VA_ARGS__)
#else
#define debug(...)
#endif // LOCAL

using namespace std;

typedef long long ll;
typedef pair<int, int> pii;
typedef vector<int> vi;
typedef long double ld;

const int INF = int(1e9);
const ll INFll = 1ll * INF * INF;
const int MOD = 1000000007;

int main() {
    cin.tie(0);
    ios_base::sync_with_stdio(0);
#ifdef LOCAL
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
#endif // LOCAL
    int n;
    cin >> n;
    vi a(n);
    for (int i = 0; i < n; ++i)
        cin >> a[i];
    int m;
    cin >> m;
    vi q(n);
    ll ans = -1;
    for (int i = 0; i < m; ++i) {
        int x;
        cin >> x;
        q[x - 1]++;
    }
    vi cur(n);
    int l = 0, r = -1;
    ll dist = 0;
    int nice = 0;
    for (int i = 0; i < n; ++i)
        if (!q[i])
            nice++;
    int dirr = 1;
    int dirl = 1;
    for (int i = 0; i < m; ++i) {
        r += dirr;
        if (i) {
            if (r == n)
                r -= 2, dist += (a[r + 1] - a[r]), dirr = -1;
            else
                if (r == -1)
                    r += 2, dirr = 1, dist += (a[r] - a[r - 1]);
                else
                    if (dirr == 1)
                        dist += a[r] - a[r - 1];
                    else
                        dist += a[r + 1] - a[r];
        }
        if (cur[r] == q[r])
            nice--;
        cur[r]++;
        if (cur[r] == q[r])
            nice++;
    }
    for (int i = 0; i < 2 * n + 1; ++i) {
        if (nice == n) {
            if (ans != -1 && ans != dist) {
                cout << -1;
                return 0;
            }
            ans = dist;
        }
        if (q[l] == cur[l])
            nice--;
        cur[l]--;
        if (q[l] == cur[l])
            nice++;
        l += dirl;
        if (l == n)
            l -= 2, dist -= (a[l + 1] - a[l]), dirl = -1;
        else
            if (l == -1)
                l += 2, dirl = 1, dist -= (a[l] - a[l - 1]);
            else
                if (dirl == 1)
                    dist -= a[l] - a[l - 1];
                else
                    dist -= a[l + 1] - a[l];
        r += dirr;
        if (r == n)
            r -= 2, dist += (a[r + 1] - a[r]), dirr = -1;
        else
            if (r == -1)
                r += 2, dirr = 1, dist += (a[r] - a[r - 1]);
            else
                if (dirr == 1)
                    dist += a[r] - a[r - 1];
                else
                    dist += a[r + 1] - a[r];
        if (cur[r] == q[r])
            nice--;
        cur[r]++;
        if (cur[r] == q[r])
            nice++;
    }
    cout << ans;
    debug("%ld\n", clock());
    return 0;
}

