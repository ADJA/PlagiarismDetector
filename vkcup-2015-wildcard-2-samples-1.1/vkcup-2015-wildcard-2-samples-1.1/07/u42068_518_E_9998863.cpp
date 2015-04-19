#include <cstdio>
#include <iostream>
#include <vector>
#include <cmath>
#include <algorithm>
#include <string>
#include <set>
#include <map>
#include <ctime>
#include <cstring>
#include <cassert>
#include <bitset>
#include <sstream>
#include <queue>

#define pb push_back
#define mp make_pair
#define fs first
#define sc second
#define sz(a) ((int) (a).size())
#define eprintf(...) fprintf(stderr, __VA_ARGS__)

using namespace std;

typedef long long int64;
typedef long double ldb;

const long double eps = 1e-9;
const int inf = (1 << 30) - 1;
const long long inf64 = ((long long)1 << 62) - 1;
const long double pi = acos(-1);

template <class T> T sqr (T x) {return x * x;}
template <class T> T abs (T x) {return x < 0 ? -x : x;}

const int MAXN = 320 * 1000;

int a[MAXN];
bool q[MAXN];
char s[100];
string::size_type sz;

void bad() {
    printf ("Incorrect sequence\n");
    exit(0);
}

int main () {
//  ios_base::sync_with_stdio(0);
//  freopen("input.txt", "rt", stdin);
//  freopen("output.txt", "wt", stdout);

    int n, k;
    scanf ("%d%d", &n, &k);

    for (int i = 0; i < n; ++i) {
        scanf ("%s", s);
        if (s[0] == '?') {
            q[k + i] = true;
        } else {
            a[k + i] = atoi(s);
        }
    }

    for (int i = 0; i < k; ++i) {
        a[i] = -inf;
        a[n + k + i] = inf;
    }
    n = n + 2 * k;

    for (int r = 0; r < k; ++r) {
        for (int i = r; i < n;) {
            int j = i;
            if (q[i]) {
                int num = 1;
                while (q[j + k]) {
                    j += k;
                    num++;
                }

                if (a[j + k] - a[i - k] <= num) {
                    bad();
                }

                if (a[i - k] >= -(num / 2)) {
                    for (int t = i; t <= j; t += k) {
                        a[t] = a[t - k] + 1;
                    }
                } else if (a[j + k] <= (num / 2)) {
                    for (int t = j; t >= i; t -= k) {
                        a[t] = a[t + k] - 1;
                    }
                } else {
                    a[i] = -(num / 2);
                    for (int t = i + k; t <= j; t += k) {
                        a[t] = a[t - k] + 1;
                    }
                }
            }
            i = j + k;
        }
    }

    for (int i = 0; i + k < n; ++i) {
        if (a[i] >= a[i + k]) {
            bad();
        }
    }

    for (int i = k; i < n - k; ++i) {
        printf ("%d%c", a[i], (i == n - k - 1 ? '\n' : ' '));
    }
    return 0;
}
