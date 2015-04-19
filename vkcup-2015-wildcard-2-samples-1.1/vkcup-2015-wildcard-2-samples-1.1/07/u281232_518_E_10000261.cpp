#include <bits/stdc++.h>
using namespace std;
typedef pair<int, int> pii;
typedef vector<int> vi;
#define mp make_pair
#define pb push_back
#define all(x) (x).begin(), (x).end()
#define sz(x) (int)((x).size())
#define sqr(x) ((x) * (x))
#define abs(x) ((x) < 0 ? -(x) : (x))
#define clr(x) memset((x), 0, sizeof(x));
template<typename T> void pv(T a, T b) { for (__typeof(a) __ = a; __ <= b; ++__) cout << *__ << " "; cout << "\n"; }
template<typename T> inline bool chmin(T &a, T b) { if (a <= b) return false; a = b; return true; }
template<typename T> inline bool chmax(T &a, T b) { if (a >= b) return false; a = b; return true; }

const int LIM = 800000;

int rb,z,j, n, k, len, uk, i, chains, chainSize;
int a[LIM], b[LIM];
bool native[LIM];
bool started[LIM];
int res[LIM];
int idx[LIM];
bool bNative[LIM];
string s, t;
int SequenceLen;
vi chain[LIM];

long long leftBound, rightBound;

const long long INF = (long long)6e18;

int Num(string s) {
        int Le = (s[0] == '-' ? 1 : 0);
        int P = (s[0] == '-' ? -1 : 1);
        int ret = 0;
        for (int i = Le; i < (int)s.length(); ++i) 
                ret = 10 * ret + s[i] - 48;
        return ret * P;
}


int main(int argc, const char *argv[]) {
       // freopen("data.in", "r", stdin);
        ios_base::sync_with_stdio(0);
        cin >> n >> k; getline(cin, s);
        getline(cin, s);
        len = (int)s.length();
        uk = 0;
        for (i = 0; i < len; ++i) {
                if (s[i] == ' ') {
                        if (t == "?") {
                                a[++uk] = -1;
                        } else {
                                a[++uk] = Num(t);
                                native[uk] = true;
                        }
                        t.clear();
                } else {
                        t += s[i];
                }
        }
        a[++uk] = (t == "?" ? -1 : Num(t));
        if (t != "?") {
                native[uk] = true;
        }
        for (i = 1; i + k <= n; ++i)
                if (native[i] && native[i + k] && a[i] >= a[i + k]) {
                        cout << "Incorrect sequence\n";
                        return 0;
                }
        for (i = 1; i <= n; ++i) {
                if (!started[i]) {

                        chainSize = 0;
                        for (j = 0; i + j * k <= n; ++j) {
                                started[i + j * k]=true;
                                b[++chainSize] = a[i + j * k];
                                bNative[chainSize] = native[i + j * k];
                                idx[chainSize] = i + j * k;
                        }

                        j = 1;
                        while (j <= chainSize) {
                                if (bNative[j]) {
                                        ++j;
                                        continue;
                                }
                                rb = j;
                                for (z = j + 1; z <= chainSize; ++z) {
                                        if (!bNative[z]) {
                                                ++rb;
                                        } else {
                                                break;
                                        }
                                }

                                // [j..rb]


                                leftBound = (j == 1 ? -INF : b[j - 1]+1);
                                rightBound = (rb == chainSize ? +INF : b[rb + 1]-1);

                                SequenceLen = rb - j + 1;

                                long long OptimalPoint = 0 - (SequenceLen / 2);
                                OptimalPoint = max(OptimalPoint, leftBound);
                                OptimalPoint = min(OptimalPoint, rightBound - SequenceLen + 1);
                                if (OptimalPoint < leftBound || OptimalPoint + SequenceLen - 1 > rightBound) {
                                        cout << "Incorrect sequence\n";
                                        return 0;
                                }

                                for (z = j; z <= rb; ++z) {
                                        a[idx[z]] = OptimalPoint++;
                                }

                                j = rb + 1;

                        }

                }
        }
        for (i = 1; i <= n; ++i) {
                cout << a[i] << " ";
        }
        cout << "\n";
        return 0;
} 