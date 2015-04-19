#include <bits/stdc++.h>
using namespace std;
#define pb push_back
#define mp make_pair
typedef long long ll;
typedef vector<int> Vint;

const int Bad = (int)2e9;
const int small = -(int)1e9 - (int)2e6;
const int big = -small;

int getint()
{
    char ch;
    while (ch = getchar(), ch != '-' && ch != '?' && (ch < '0' || ch > '9'));

    if (ch == '?')
        return Bad;
    int sign = (ch == '-' ? -1 : 1);
    int x = 0;

    if (ch >= '0' && ch <= '9')
        x = ch - '0';

    while (true)
    {
        ch = getchar();
        if (ch < '0' || ch > '9')
            break;
        x *= 10, x += ch - '0';
    }

    return x * sign;
}

Vint solve_part(Vint part)
{
    int n = (int)part.size();

    Vint set_vals;
    Vint where_set;

    for (int i = 0; i < n; i++)
    if (part[i] != Bad)
        set_vals.pb(part[i]),
        where_set.pb(i);

    Vint other_vals;
    int len = (int)set_vals.size();

    for (int i = 0; i < len - 1; i++)
    {
        int x = set_vals[i];
        int y = set_vals[i + 1];
        int dist = where_set[i + 1] - where_set[i] - 1;

        if (y <= 0)
        {
            for (int j = dist; j >= 1; j--)
                other_vals.pb(y - j);
        }
        else if (x >= 0)
        {
            for (int j = 1; j <= dist; j++)
                other_vals.pb(x + j);
        }
        else
        {
            assert(x < 0 && y > 0);

            int righthalf = dist - dist / 2;
            int lefthalf = dist / 2;

            if (righthalf > y)
                lefthalf += righthalf - y, righthalf = y;
            else if (lefthalf >= abs(x))
                righthalf += lefthalf - (abs(x) - 1),
                lefthalf = abs(x) - 1;

            assert(lefthalf + righthalf == dist);
            for (int i = lefthalf; i >= 1; i--)
                other_vals.pb(-i);
            for (int i = 0; i < righthalf; i++)
                other_vals.pb(i);
        }
    }

    int h = 0;
    for (int i = 0; i < n; i++)
    if (part[i] == Bad)
    {
        assert(h < (int)other_vals.size());
        part[i] = other_vals[h], h++;
    }

    return part;
}

void solve(int n)
{
    int k;
    scanf(" %d", &k);

    vector<int> a(n);

    for (int i = 0; i < n; i++)
        a[i] = getint();

    vector<vector<int> > parts(k);

    for (int i = 0; i < k; i++)
        parts[i].pb(small);
    for (int i = 0; i < n; i++)
        parts[i % k].pb(a[i]);
    for (int i = 0; i < k; i++)
        parts[i].pb(big);

    for (int i = 0; i < k; i++)
    {
        Vint v = solve_part(parts[i]);
        parts[i] = v;
    }

    for (int i = 0; i < k; i++)
    for (int j = 1; j < (int)parts[i].size() - 1; j++)
    {
        assert(i + (j - 1) * k < n);
        a[i + (j - 1) * k] = parts[i][j];
    }

    bool ok = true;
    for (int i = 0; i < n; i++)
    if (i >= k && a[i] <= a[i - k])
        ok = false;

    if (!ok)
    {
        printf("Incorrect sequence\n");
        return;
    }

    for (int i = 0; i < n; i++)
    {
        assert(a[i] != Bad);
        assert(a[i] >= small && a[i] <= big);
        printf("%d ", a[i]);
    }
    printf("\n");
}

int main()
{
    #ifndef ONLINE_JUDGE
    freopen("input.txt", "rt", stdin);
    freopen("output.txt", "w", stdout);
    #endif

    int n;
    while (cin >> n)
        solve(n);
}
