#include <bits/stdc++.h>
using namespace std;
typedef long long i64;
typedef pair<int,int> pii;

#define DB(v) cerr << #v << ": " << v << endl
#define forn(i, n) for (int i = 0; i < (int)n; ++i)
#define fore(i, a, b) for (int i = a; i <= (int)b; ++i)
#define ford(i, n) for (int i = (int)n - 1; i >= 0; --i)
#define clr(x) memset(x, 0, sizeof(x))
#define mp make_pair
#define pb push_back
#define fi first
#define se second

const int MAXN = 2e5 + 7;
const int INF = 1e9 + 1e7;
const int MARK = INF + 5;

int a[MAXN];

bool NO()
{
    cout << "Incorrect sequence";
    exit(0);
}

int main()
{
    cin.tie(NULL);
    ios_base::sync_with_stdio(0);
#ifdef HOME
    //freopen("input.txt", "r", stdin);
    //freopen("output.txt", "w", stdout);
#endif

    int n, k;
    cin >> n >> k;
    forn(i, n)
    {
        string s;
        cin >> s;
        if (s[0] != '?')
            a[i] = atoi(s.c_str());
        else
            a[i] = MARK;
    }

    forn(t, k)
    {
        vector<int> c;
        int cmin = -INF - 1, cnt = 0;
        for (int i = t; i < n; i += k)
        {
            if (a[i] != MARK)
            {
                int cmax = a[i];
                vector<int> b;
                if (cmax - cmin - 1 < cnt)
                {
                    //DB("here");
                    //DB(i);
                    //DB(cmax); DB(cmin);
                    //DB(cnt);
                    NO();
                }
                int k = min(abs(cmin), abs(cmax));
                if (cmin <= 0 && cmax >= 0) k = 0;
                for (; b.size() < cnt; ++k)
                {
                    if (b.size() < cnt && cmin < k && k < cmax) b.pb(k);
                    if (k > 0 && b.size() < cnt && cmin < -k && -k < cmax) b.pb(-k);
                }
                sort(b.begin(), b.end());
                forn(j, c.size())
                    a[c[j]] = b[j];

                c.clear();
                cmin = a[i];
                cnt = 0;
            }
            if (a[i] == MARK)
            {
                ++cnt;
                c.pb(i);
            }
        }
        if (cnt)
        {
            vector<int> b;
            int cmax = INF + 1;
            if (cmax - cmin - 1 < cnt) NO();
            int k = min(abs(cmin), abs(cmax));
            if (cmin <= 0 && cmax >= 0) k = 0;
            for (; b.size() < cnt; ++k)
            {
                if (b.size() < cnt && cmin < k && k < cmax) b.pb(k);
                if (k > 0 && b.size() < cnt && cmin < -k && -k < cmax) b.pb(-k);
            }
            sort(b.begin(), b.end());
            forn(j, c.size())
                a[c[j]] = b[j];
        }
    }

    forn(i, n) cout << a[i] << ' ';

#ifdef HOME
    cerr << "\nTime elapsed: " << clock() / 1000 << " ms" << endl;
#endif
    return 0;
}
