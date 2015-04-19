#include <iostream>
#include <cstring>
#include <vector>
#include <set>
#include <map>
#include <algorithm>
#include <iomanip>
#include <cstdio>
#include <ctime>
#include <functional>
#include <iterator>
#include <complex>
#include <queue>
#include <cassert>
#include <sstream>
#include <cstdlib>

using namespace std;

typedef long long LL;
typedef long double LD;

const LL MOD = (LL)1e18;
const int LEN = 18;

struct Number {
    LL l, h;

    Number(int x = 0)
        : l(x), h(0)
    {
    }

    Number& operator+= (Number o) {
        l += o.l;
        if (l >= MOD) {
            l -= MOD;
            h++;
        }
        h += o.h;
        return *this;
    }
    Number operator+ (Number b) {
        Number a = *this;
        a += b;
        return a;
    }
};

ostream& operator<< (ostream& ostr, Number n) {
    if (n.h) {
        ostr << n.h;
        ostr << setfill('0') << setw(LEN) << n.l;
    }
    else
        ostr << n.l;
    return ostr;
}

const int MAX_N = 110;
char s [MAX_N];
int n;
Number f [MAX_N][2];

int ok(int s0, int t0, int s1, int t1) {
    int ret = 1;
    if (s0 == 0) // A looks ahead
        ret &= (s0 == t0) == (s1 == 0);
    //else
    //    ret &= s0 == t0;
    if (s1 == 1) // A looks back
        ret &= (s1 == t1) == (s0 == 1);
    //else
    //    ret &= s1 == t1;
    return ret;
}

string path;
void rec(int i, int st, int c) {
    if (i == n)  {
        if (st == c)
            cerr << path << '\n';
        return;
    }
    for (int j = 0; j < 2; j++)
        if (ok(c, s[i], j, s[i + 1])) {
            path += 'A' + j;
            rec(i + 1, st, j);
            path = path.substr(0, path.size() - 1);
        }
}

int main() {
    scanf("%s", s);
    n = strlen(s);
    for (int j = 0; j < n; j++)
        s[j] -= 'A';
    s[n] = s[0];
    
#ifdef DEBUG
    path = 'A';
    rec(0, 0, 0);
    path = 'B';
    rec(0, 1, 1);
#endif

    Number ans = 0;
    for (int fst = 0; fst < 2; fst++) {
        memset(f, 0, sizeof(f));
        for (int j = 0; j < 2; j++)
            f[1][j] = ok(fst, s[0], j, s[1]);

        for (int i = 1; i < n; i++)
            for (int j = 0; j < 2; j++)
                for (int k = 0; k < 2; k++)
                    if (ok(j, s[i], k, s[i + 1]))
                        f[i + 1][k] += f[i][j];
#ifdef DEBUG
        cerr << "fst " << fst << '\n';
        for (int i = 1; i <= n; i++) {
            for (int j = 0; j < 2; j++)
                cerr << f[i][j] << ' ';
            cerr << '\n';
        }
#endif
        ans += f[n][fst];
   }


#ifdef DEBUG
    int brute = 0;
    for (int mask = 0; mask < (1 << n); mask++) {
        int x [100], y [100];
        for (int i = 0; i < n; i++)
            x[n - 1 - i] = (mask >> i) & 1;
        for (int i = 0; i < n; i++)
            if (x[i] == 0)
                y[i] = x[i] == x[(i + 1) % n] ? 0 : 1;
            else
                y[i] = x[i] == x[(i + n - 1) % n] ? 1 : 0;

        /*cerr << "x";
        for (int i = 0; i < n; i++)
            cerr << x[i];
        cerr << '\n';
        cerr << "y";
        for (int i = 0; i < n; i++)
            cerr << y[i];
        cerr << '\n';*/

        int add = 1;
        for (int j = 0; j < n; j++)
            if (y[j] != s[j]) {
                add = 0;
                //cerr << "fuck " << j << '\n';
                break;
            }

        brute += add;
    }
    cerr << "brute " << brute << '\n';
    //assert(brute == ans.l);
#endif

    cout << ans << '\n';
    return 0;
}
