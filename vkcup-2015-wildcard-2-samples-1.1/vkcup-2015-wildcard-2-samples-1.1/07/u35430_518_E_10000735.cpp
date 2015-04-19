#include <cstdio>
#include <iostream>
#include <vector>
#include <algorithm>
#include <stack>
#include <queue>
#include <set>
#include <cmath>
#include <iomanip>
#include <map>

#define pb push_back
#define mp make_pair
#define F first
#define S second

using namespace std;

const long double EPS = 0.00000001;
const int INF = 1100000007;
const long long w = 31;

int c[100100];

int stoi (string &s) {
    int r = 0;
    if (s[0] == '-') {
        for (int i = 1; i < s.size(); i++) {
            r = (r * 10) + (s[i] - '0');
        }
        return -r;
    }
    for (int i = 0; i < s.size(); i++) {
        r = (r * 10) + s[i] - '0';
    }
    return r;
}

int main(){
    ios_base::sync_with_stdio(0);
    #ifdef LOCAL //LOCAL
        freopen("input.txt", "r", stdin);
        freopen("output.txt", "w", stdout);
    #else
        //freopen("webbuy.in", "r", stdin);
        //freopen("webbuy.out", "w", stdout);
    #endif
    int n,m;
    cin >> n >> m;
    string l;
    for (int i = 0; i < n; i++) {
        cin >> l;
        if (l == "?") {
            c[i] = INF;
        } else c[i] = stoi(l);
    }
    vector<int> v;
    for (int i = 0; i < m; i++) {
        v.clear();
        v.pb(-1010000000);
        for (int j = i; j < n; j += m) {
            v.pb(c[j]);
            //cout << c[j] << endl;
        }
        //cout << "lelpas" << endl;
        int l = v.size();
        v.pb(1010000000);
        for (int j = l-1; j >= 0; j--) {
            if (v[j] != INF) {
                if (v[l] - v[j] - 1 < l - j - 1) {
                    cout << "Incorrect sequence";
                    return 0;
                }
                int k = l - j - 1;
                int t1 = -(k / 2);
                int t2 = t1 + k - 1;
                if (t1 == v[j] && k % 2 == 0) {
                    t1++;
                    t2++;
                }
                if (t1 > v[j] && t2 < v[l]) {
                } else {
                    if (abs(v[j]) < abs(v[l])) {
                        t1 = v[j] + 1;
                    } else {
                        t1 = v[l] - 1 - (k - 1);
                    }
                }
                for (int t = j + 1; t < l; t++) {
                    c[i + (t-1) * m] = t1;
                    t1++;
                }
                l = j;
            }
        }
    }
    for (int i = 0; i < n; i++) cout << c[i] << " ";
    return 0;
}
