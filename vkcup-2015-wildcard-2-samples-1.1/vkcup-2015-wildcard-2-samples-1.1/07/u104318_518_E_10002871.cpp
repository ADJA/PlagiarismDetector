// Smile please :)

#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <cmath>
#include <ctime>
#include <cassert>
#include <cctype>
#include <sstream>
#include <iostream>
#include <algorithm>
#include <string>
#include <iomanip>
#include <numeric>
#include <vector>
#include <queue>
#include <stack>
#include <deque>
#include <set>
#include <map>
#include <list>
#include <bitset>
#include <unordered_map>
#include <unordered_set>
using namespace std;

#ifdef KVARK
    #include "debug.h"
#else
#define dbg(...) (void(1))
#define dbg2(...) (void(1))
#define dbg3(...) (void(1))
#define dbg4(...) (void(1))
#define dbg5(...) (void(1))
#define dbgp(...) (void(1))
#define dbg_range(...) (void(1))
#endif
#define endl "\n"

template <typename T>
struct Pt {
    T x, y;
    void scan() {cin >> x >> y;}
};

typedef Pt<int> Pti;
typedef Pt<double> Ptd;
typedef Pt<long long> Ptll;
typedef pair<int, int> pii;
typedef pair<long long, long long> pll;
typedef vector<int> vi;
typedef vector<pii> vpii;
typedef vector<pll> vpll;
typedef vector<vector<int> > vvi;
typedef vector<vector<long long> > vvll;
typedef vector<long long> vll;
typedef long long int llint;

#define all(v) (v.begin()), (v.end())
#define sz(v) ((int)((v).size()))

template <typename T>
inline T sqr(const T& a) {
    return a * a;
}

template <typename T>
inline int sign(const T& a) {
    return a < 0 ? -1 : a > 0;
}

void task();

int main() {
#ifdef KVARK
    freopen("input.txt", "r", stdin);
    //freopen("debug.txt", "w", stderr);
    //freopen("output.txt", "w", stdout);
#else
    //freopen("input.txt", "r", stdin);
    //freopen("output.txt", "w", stdout);
#endif

    task();

#ifdef KVARK
    my_debug::printProcessInfo();
#endif
    return 0;
}

const int INF = 1e9 + 5e5 + 100;

struct S {
    int real_pos;
    int value;
};

int n, k;

int a[int(1e5)+10];

bool can_trans(vector<S>& v) {
    int is_free = 1;
    for (int i = 0; i < (int)v.size(); ++i)
        if (v[i].value != INF) {
            is_free = 0;
            break;
        }
    if (is_free) {
        int mn = - ((int)v.size() / 2);
        for (int i = 0; i < (int)v.size(); ++i)
            v[i].value = mn, mn++;
        return true;
    }

    int id = 0;
    while (v[id].value == INF)
        ++id;

    if (id) {
        int mn = -id / 2;
        if (mn + id - 1 > v[id].value - 1)
            mn = v[id].value - id;
        for (int i = 0, val = mn; i < id; ++i, ++val)
            v[i].value = val;
    }

    int left_ = id;
    id = v.size() - 1;
    while (v[id].value == INF)
        --id;
    if (id != (int)v.size() - 1) {
        int len = (int)v.size() - id - 1;
        int mn = - (len / 2);
        if (mn < v[id].value + 1)
            mn = v[id].value + 1;
        for (int i = id + 1, val = mn; i < (int)v.size(); ++i, ++val)
            v[i].value = val;
    }
    int right_ = id;

    while (left_ != right_) {
        int id = left_ + 1;
        while (v[id].value == INF)
            ++id;
        if (v[id].value - v[left_].value < id - left_)
            return false;
        int len = id - left_ - 1;
        int mn = - (len / 2);
        if (mn < v[left_].value + 1)
            mn = v[left_].value + 1;
        if (mn + len - 1 > v[id].value - 1)
            mn = v[id].value - len;
        for (int i = left_ + 1, val = mn; i < id; ++i, ++val )
            v[i].value = val;
        left_ = id;
    }
    return true;
}

void task(){
    ios_base::sync_with_stdio(0);
    cin >> n >> k;
    for (int i = 0; i < n; ++i) {
        string s;
        cin >> s;
        if (s == "?")
            a[i] = INF;
        else
            a[i] = atoi(s.c_str());
    }

    for (int j = 0; j < k; ++j) {
        vector<S> v;
        for (int i = j; i < n; i += k)
            v.push_back({i, a[i]});
        if (!can_trans(v)) {
            cout << "Incorrect sequence";
            return;
        }
        for (auto& x: v)
            a[x.real_pos] = x.value;
    }

    for (int i = 0; i < n; ++i)
        cout << a[i] << ' ';
}
