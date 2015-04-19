#include<iostream>
#include <cmath>
#include <vector>
#include <cstdlib>
#include <algorithm>
#include <map>
#include <memory.h>
#include <set>
#include <bitset>
#include <string.h>
#include <cstdio>
using namespace std;
typedef long long ll;
const ll N = 100005;
const ll mod = 2e9 + 1;
ll n, k;
char c;
vector<pair<ll, ll> > group[N];
ll used[N];
ll sz[N];
ll tr(string & s)
{
    ll ans = 0;
    int st;
    if(s[0] == '-') st = 1;
    else st = 0;
    for(ll i = st; i < (ll)s.size(); ++i)
    {
        ans = ans * 10 + s[i] - '0';
    }
    if(st) ans = -ans;
    return ans;
}
ll a[N];
ll num[N];
vector<ll> cur;
ll f(ll val)
{
    ll sz = cur.size();
    ll res = 0;
    for(ll i = 0; i < sz; ++i)
    {
        ll cr = cur[i] + val;
        if(cr < 0) cr = -cr;
        res -= cr;
    }
    return res;
}
void cn(ll l, ll r, ll cnt, ll lef, ll rig, ll le, ll re)
{
    if(cnt <= 0) return;
    cur.clear();
    for(ll i = lef, j = le; i <= rig; ++i, j += k)
    {
        a[j] = l + i - lef;
        cur.push_back(a[j]);
    }
    ll bin_l = 0;
    ll bin_r = r - l - cnt + 1;
    while (bin_r - bin_l > 3)
    {
        ll m1 = bin_l + (bin_r - bin_l) / 3;
        ll m2 = bin_r - (bin_r - bin_l) / 3;
        if (f (m1) < f (m2))
            bin_l = m1;
        else
            bin_r = m2;
    }
    ll mx = -1e18;
    ll val = 0;
    for(ll i = bin_l; i <= bin_r; ++i)
    {
        ll dop = f(i);
        if(dop > mx)
        {
            mx = dop;
            val = i;
        }
    }
    for(ll i = lef, j = le; i <= rig; ++i, j += k)
    {
        a[j] += val;
    }
    return;
}

int main()
{
    ios_base::sync_with_stdio(false);
    cin >> n >> k;
    string s;
    for(ll i = 0; i < k; ++i)
    {
        group[i].push_back(make_pair(-mod, -1));
    }
    for(ll i = 0; i < n; ++i)
    {
        cin >> s;
        if(s != "?")
        {
            ll cur = tr(s);
            a[i] = cur;
            group[i % k].push_back(make_pair(cur, i / k));
        }
        sz[i % k]++;
    }
    for(ll i = 0; i < k; ++i)
    {
        group[i].push_back(make_pair(mod, sz[i]));
    }
    for(ll i = 0; i < k; ++i)
    {
        for(ll j = 0; j < (ll)group[i].size() - 1; ++j)
        {
            ll first = group[i][j + 1].first - group[i][j].first;
            ll second = group[i][j + 1].second - group[i][j].second;
            if(first < second)
            {
                cout << "Incorrect sequence" << endl;
                return 0;
            }
        }
    }
    for(ll i = 0; i < k; ++i)
    {
        for(ll j = 0; j < (ll)group[i].size() - 1; ++j)
        {
            ll l = group[i][j].first + 1;
            ll r = group[i][j + 1].first - 1;
            ll lef = group[i][j].second + 1;
            ll rig = group[i][j + 1].second - 1;
            ll cnt = rig - lef + 1;
            ll le = lef * k + i;
            ll re = rig * k + i;
            cn(l, r, cnt, lef, rig, le, re);
        }
    }
    for(ll i = 0; i < n; ++i)
    {
        cout << a[i] << " ";
    }
    return 0;
}
