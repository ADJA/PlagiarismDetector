#include <bits/stdc++.h>
using namespace std;

#define forn(i,n) for(int i = 0; i < (int)(n); ++i)
#define MAPADD(m,a,b) if (m.count(a)) m[a] = m[a] + b; else m[a] = b;

int const inf = 1001000009;

int main()
{
//    freopen("in.txt", "r", stdin);
//    freopen("out.txt", "w", stdout);
//    cout << fixed << setprecision(10);
    ios_base::sync_with_stdio(false);

    int n, k;
    cin >> n >> k;
    vector<int> a(n, 0);
    vector<bool> has(n, true);
    forn(i, n)
    {
        string s;
        cin >> s;
        if (s[0] == '?')
            has[i] = false;
        else
            a[i] = atoi(s.c_str());
    }

//    cerr << "ok" << endl;
    forn(i, k)
    {
        int last = -inf;
        int cnt = 0;
        for(int j = i; j < n; j += k)
            if (has[j])
            {
                if (a[j] <= last + cnt)
                {
                    cout << "Incorrect sequence\n";
                    return 0;
                }
                last = a[j];
                cnt = 0;
            }
            else
                ++cnt;
    }

    forn(i, k)
    {
        int last = -inf;
        int cnt = 0;
        int j = i;
        for(; j < n; j += k)
            if (has[j])
            {
                if (a[j] <= 0)
                {
                    int cur = a[j] - 1;
                    for(int t = j - k; t >= 0 && !has[t]; t -= k)
                        a[t] = cur--;
                }
                else if (last >= 0)
                {
                    int cur = last + cnt;
                    for(int t = j - k; t >= 0 && !has[t]; t -= k)
                        a[t] = cur--;
                }
                else
                {
                    int left = -cnt/2;
                    int right = cnt/2;
                    if (left <= last)
                    {
                        int sh = last - left + 1;
                        left += sh;
                        right += sh;
                    }
                    if (right >= a[j])
                    {
                        int sh = right - a[j] + 1;
                        left -= sh;
                        right -= sh;
                    }
                    for(int t = j - k; t >= 0 && !has[t]; t -= k)
                        a[t] = right--;

                }
                last = a[j];
                cnt = 0;
            }
            else
                ++cnt;
        if (last >= 0)
        {
            int cur = last + cnt;
            for(int t = j - k; t >= 0 && !has[t]; t -= k)
                a[t] = cur--;
        }
        else
        {
            int left = -cnt/2;
            int right = cnt/2;
            if (left <= last)
            {
                int sh = last - left + 1;
                left += sh;
                right += sh;
            }
            for(int t = j - k; t >= 0 && !has[t]; t -= k)
                a[t] = right--;

        }
    }

    forn(i, n)
        cout << a[i] << " \n"[i == n-1];

    return 0;
}
