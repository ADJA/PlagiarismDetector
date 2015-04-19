#include <cstdio>
#include <iostream>
#include <string>
#include <cstring>
#include <cmath>
#include <cstdlib>
#include <vector>
#include <algorithm>
#include <stack>
#include <queue>
#include <map>
#include <set>

using namespace std;

typedef long long ll;
typedef pair<int, int> ii;

const int N = 1000010, inf = 1000000007;
int n, k, x, y, z, p, a[N], b[N];
string s;
vector<ii> v[N];

void iz()
{
    printf("Incorrect sequence");
    exit(0);
}

int main()
{
    cin.sync_with_stdio(false);
    cout.sync_with_stdio(false);

    cin >> n >> k;
    for (int i = 0; i < n; i++)
    {
        int x;
        cin >> s;

        b[i % k]++;
        if (s == "?") continue;
        //printf("dsasaddsadsadsadsads %d\n", i);
        a[i] = atoi(s.c_str());
        v[i % k].push_back(ii(a[i], i));
    }


    /*cout << endl;
    for (int i = 0; i < k; i++) cout << b[i] << endl;
    cout << endl;


    cout << endl;
    for (int i = 0; i < k; i++)
    {
        cout << "sad: " << i << " ";
        for (auto j : v[i]) cout << j.first << " ";
        cout << endl;
    }
    cout << endl;*/

    for (int i = 0; i < k; i++) if (v[i].empty())
    {
        x = b[i] >> 1; y = b[i] - 1 >> 1;
        for (int j = -x, g = i; j <= y; j++, g += k) a[g] = j;
    } else
    {
        x = v[i][0].first, y = v[i][0].second / k;
        int z0 = y - 1 >> 1, z1 = y >> 1;

        //printf("sad sam na %d\n", i);
        //printf("vrednosti x, y i z: %d %d %d\n", x, y, z);

        if (z0 < x)
        {
            for (int j = -z1, g = i; j <= z0; j++, g += k) a[g] = j;
        } else
        {
            for (int j = x - y, g = i; j < x; j++, g += k) a[g] = j;
        }
        for (int it = 0; it < v[i].size() - 1; it++)
        {
            int r = v[i][it].first, l = v[i][it + 1].first, p = v[i][it].second + k, d = (v[i][it + 1].second - v[i][it].second) / k - 1;
            if (l - r < d + 1) iz();
            x = d >> 1, y = d - 1 >> 1;
            if (x < l && -r > y)
            {
                for (int j = -y, g = p; j <= x; j++, g += k) a[g] = j;
            } else
            if (y < l && -r > x)
            {
                for (int j = -x, g = p; j <= y; j++, g += k) a[g] = j;
            } else
            if (l < -r)
            {
                for (int j = l - d, g = p; j < l; j++, g += k) a[g] = j;
            } else
            {
                for (int j = r + 1, g = p; j <= r + d; j++, g += k) a[g] = j;
            }
        }
        x = v[i].back().first, y = b[i] - v[i].back().second / k - 1, p = v[i].back().second + k;
        z0 = y - 1 >> 1; z1 = y >> 1;
        if (-z0 > x)
        {
            for (int j = -z0, g = p; j <= z1; j++, g += k) a[g] = j;
        } else
        {
            for (int j = x + 1, g = p; j <= x + y; j++, g += k) a[g] = j;
        }
    }
    for (int i = 0; i < n; i++) cout << a[i] << " ";
    return 0;
}
