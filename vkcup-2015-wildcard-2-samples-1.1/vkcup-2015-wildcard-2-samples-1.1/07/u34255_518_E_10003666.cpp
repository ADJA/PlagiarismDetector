#include <functional>
#include <algorithm>
#include <iostream>
#include <memory.h>
#include <sstream>
#include <fstream>
#include <iomanip>
#include <bitset>
#include <string>
#include <cstdio>
#include <complex>
#include <vector>
#include <queue>
#include <stack>
#include <cmath>
#include <ctime>
#include <set>
#include <map>
#include <unordered_set>
using namespace std;

#define int64 long long
#define mp make_pair
const int64 inf = 2e9;


#ifdef _DEBUG
    const int N = 310;
#else
    const int N = 300010;
#endif

int n, k;
int64 a[N];
bool q[N];
vector <pair<int64, int> > g[N];
vector <int64> cur;

int main()
{
#ifdef _DEBUG
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
#endif
    scanf("%d%d\n", &n, &k);
    memset(q, false, sizeof(q));
    for (int i = 0; i < n; i++)
    {
        string s;
        cin >> s;
        a[i] = 0;
        if (s[0] == '?')
        {
            q[i] = true;
            continue;
        }
        bool f = false;
        int c = 0;
        if (s[0] == '-')
        {
            f = true;
            c = 1;
        }
        for (int j = c; j < s.length(); j++) a[i] = 10 * a[i] + s[j] - '0';
        if (f) a[i] *= -1;
    }
    for (int i = 0; i < k; i++) g[i].push_back(mp(-inf, i - k));
    for (int i = 0; i < n; i++)
        if (!q[i]) g[i % k].push_back(mp(a[i], i));
    for (int i = n - 1; i >= n - k; i--) g[i % k].push_back(mp(inf, i + k));
    for (int i = 0; i < k; i++)
    {
        for (int j = 0; j < (int)g[i].size() - 1; j++)
        {
            int64 x1 = g[i][j].first, x2 = g[i][j + 1].first;
            int j1 = g[i][j].second, j2 = g[i][j + 1].second;
            if (x1 >= x2)
            {
                cout << "Incorrect sequence";
                return 0;
            }
            int s = (j2 - k) / k - (j1 + k) / k + 1;
            if (x2 <= 0)
            {
                int val = x2;
                for (int ind = j2 - k; ind >= j1 + k; ind -= k)
                {
                    val--;
                    a[ind] = val;
                }
                if (val <= x1)
                {
                    cout << "Incorrect sequence";
                    return 0;
                }
                continue;
            }
            if (x1 >= 0)
            {
                int val = x1;
                for (int ind = j1 + k; ind <= j2 - k; ind += k)
                {
                    val++;
                    a[ind] = val;
                }
                if (val >= x2)
                {
                    cout << "Incorrect sequence";
                    return 0;
                }
                continue;
            }
            if (x2 - x1 - 1 < s)
            {
                cout << "Incorrect sequence";
                return 0;
            }
            int val1 = 0, val2 = 0;
            cur.clear();
            while (cur.size() < s)
            {
                if (val1 < x2) cur.push_back(val1);
                if (cur.size() >= s) break;
                if (val2 != 0 && val2 > x1) cur.push_back(val2);
                val1++;
                val2--;
            }
            sort(cur.begin(), cur.end());
            int r = 0;
            for (int ind = j1 + k; ind <= j2 - k; ind += k)
            {
                a[ind] = cur[r];
                r++;
            }
        }
    }
    for (int i = 0; i < n; i++) printf("%I64d ", a[i]);
    return 0;
}