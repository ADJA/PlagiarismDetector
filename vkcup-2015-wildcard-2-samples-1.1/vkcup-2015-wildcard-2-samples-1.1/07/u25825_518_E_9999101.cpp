#include <iostream>
#include <cmath>
#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <cassert>
#include <ctime>
#include <sstream>
#include <algorithm>
#include <functional>
#include <numeric>
#include <string>
#include <vector>
#include <queue>
#include <stack>
#include <map>
#include <set>

using namespace std;

#define f first
#define s second
#define pb push_back
#define mp make_pair
#define ll long long
#define pii pair < int, int >
#define pll pair < long long, long long>
#define ull unsigned long long
#define y1 stupid_cmath
#define left stupid_left
#define right stupid_right
#define vi vector <int>
#define sz(a) (int)a.size()
#define forit(it, s) for(__typeof(s.begin()) it = s.begin(); it != s.end(); it++)
#define all(a) a.begin(), a.end()
#define sqr(x) ((x) * (x))

const int inf = (int)2e9;
const int mod = inf + 7;
const double eps = 1e-9;
const double pi = acos(-1.0);

int n, k;
int a[100100];

int toInt(string s) {
    if(s[0] == '-') return -1 * toInt(s.substr(1));
    else {
        int ans = 0;
        for(int i = 0; i < sz(s); i++) ans = 10 * ans + s[i] - '0';
        return ans;
    }
}

void fail() {
    cout << "Incorrect sequence" << endl;
    exit(0);
}

void solve(vector <pair <int, int> > &v) {
    int cur = -inf;
    for(int i = 0, j = 0; i < sz(v); i = j) {
        if(v[i].f != inf) {
            cur = v[i].f;
            j = i+1;
        } else {
            j = i;
            while(j < sz(v) && v[j].f == inf) j++;
            int nxt = inf;
            if(j < sz(v)) nxt = v[j].f;
            int cnt = j - i;
            if(1LL * cnt > nxt - 1ll - cur) fail();
            if(cur >= 0) {
                int st = cur+1;
                for(int t = i; t < j; t++) {
                    a[v[t].s] = st++;
                }
            } else if(nxt <= 0) {
                int st = nxt - 1;
                for(int t = j-1; t >= i; t--) a[v[t].s] = st--;
            } else {
                int l1 = -((cnt - 1) / 2), r1 = (cnt - 1 + 1) / 2;
                int l2 = -((cnt - 1 + 1) / 2), r2 = (cnt - 1) / 2;
                if(l1 > cur && r1 < nxt) {
                    int st = l1;
                    for(int t = i; t < j; t++) a[v[t].s] = st++;
                } else if(l2 > cur && r2 < nxt) {
                    int st = l2;
                    for(int t = i; t < j; t++) a[v[t].s] = st++;
                } else {
                    ll sum1 = 0, sum2 = 0;
                    int st = cur+1;
                    for(int t = i; t < j; t++) {
                        sum1 += abs(st);
                        st++;
                    }
                    st = nxt - 1;
                    for(int t = i; t < j; t++) {
                        sum2 += abs(st);
                        st--;
                    }
                    if(sum1 <= sum2) {
                        st = cur + 1;
                        for(int t = i; t < j; t++) a[v[t].s] = st++;
                    } else {
                        st = nxt - 1;
                        for(int t = j-1; t >= i; t--) a[v[t].s] = st--;
                    }
                }
            }
        }
    }
}

int main(){

    string s;

    cin >> n >> k;
    for(int i = 0; i < n; i++) {
        cin >> s;
        if(s == "?") a[i] = inf;
        else a[i] = toInt(s);
    }

    for(int i = 0; i < k; i++) {
        int mx = -inf;
        for(int j = i; j < n; j += k) {
            if(a[j] != inf) {
                if(mx >= a[j]) {
                    cout << "Incorrect sequence" << endl;
                    return 0;
                }
                mx = max(mx, a[j]);
            }
        }
    }

    for(int i = 0; i < k; i++) {
        vector <pair<int, int> > v;
        for(int j = i; j < n; j += k) {
            v.pb(mp(a[j], j));
        }
        solve(v);
    }

    for(int i = 0; i < n; i++) printf("%d ", a[i]);
        
    return 0;
}
