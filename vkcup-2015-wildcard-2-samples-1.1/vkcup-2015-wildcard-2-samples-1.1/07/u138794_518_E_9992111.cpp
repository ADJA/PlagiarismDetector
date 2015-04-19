#include <vector>
#include <list>
#include <map>
#include <set>
#include <queue>
#include <deque>
#include <stack>
#include <bitset>
#include <algorithm>
#include <functional>
#include <numeric>
#include <utility>
#include <sstream>
#include <iostream>
#include <iomanip>
#include <cstdio>
#include <cmath>
#include <cstdlib>
#include <ctime>
#include <cstring>

using namespace std;

typedef pair<int, int> PP;
typedef long long LL;
#define pb push_back
#define fr first
#define sc second

int n, k;
LL p[100010], e[100010];


void fill(int x, int m, LL l, LL r) {
    if (r - l - 1 < m) {
        cout << "Incorrect sequence" << endl; exit(0);
    }
    if (m == 0) return;
    if (r <= 0) {
        for (int i = 0; i < m; i ++) 
            p[x + i * k] = r - (m - i), e[x + i * k] = 0;
    }
    else if (l >= 0) {
        for (int i = 0; i < m; i ++) 
            p[x + i * k] = l + 1 + i,   e[x + i * k] = 0;
    }
    else {
        int cnt = 1; LL ll = -1, rr = 1;
        while (cnt < m) {
            if ((rr >= r || abs(ll) < abs(rr)) && ll > l) ll --;
            else rr ++;
            cnt ++;
        }
        for (int i = 0; i < m; i ++) 
            p[x + i * k] = ll + 1 + i,  e[x + i * k] = 0;
    }
}

int main() {
    #ifdef _TEST_
    freopen("input.txt", "r", stdin);
    //freopen("out.txt", "w", stdout);
    #endif
    scanf("%d %d", &n, &k);
    char s[200];
    for (int i = 0; i < n; i ++) {
        scanf("%s ", s);
        if (s[0] == '?') e[i] = 1;
        else p[i] = atoi(s);
    }

    //for (int i = 0; i < n; i ++) cout << p[i] << " ";
    for (int i = 0; i < n; i ++) {
        int cnt = 0;
        while (i + cnt * k < n && e[i + cnt * k]) cnt ++;
        LL l = -10000000000LL, r = 10000000000LL;
        if (i + cnt * k < n) r = p[i + cnt * k];
        if (i >= k) l = p[i - k];
        fill(i, cnt, l, r);
    }

    for (int i = 0; i < n; i ++) cout << p[i] << ' ';
    cout << endl;

    return 0;
}
