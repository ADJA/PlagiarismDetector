#include <iostream>
#include <cstdio>
#include <algorithm>
#include <cmath>
#include <string>
#include <string.h>
#include <stack>
#include <queue>
#include <map>
#include <vector>
#include <set>
#include <cassert>
#include <ctime>
#include <cstdlib>

using namespace std;

#define ll long long
#define ld long double
#define ull unsigned long long
#define uint unsigned int
#define fst first
#define snd second
#define pb push_back
#define mp make_pair
#define y0 alfdjasldfjeao
#define y1 safiodjafis

const int maxn = 200003;
int n;
int m;
ll a[maxn], b[maxn], c[maxn], d[maxn];

void check(int x, int v)
{
	for (int i = 1; i <= n; i++)
		c[i] = b[i];
	int cur = x;
	int k = 0;
	ll curans = 0;
	for (int i = 1; i <= m; i++)
	{
		curans += k;
		if (c[cur] == 0)
		{
			return;
		}
		c[cur]--;
		if (cur == 1 && v == -1)
			v = 1;
		if (cur == n && v == 1)
			v = -1;
		k = abs(a[cur+v] - a[cur]);
		cur += v;
	}
	d[x] = curans;
}

int main()
{
	//freopen("input.txt", "r", stdin);
	cin >> n;
	for (int i = 1; i <= n; i++)
		cin >> a[i];
	for (int i = 1; i <= n; i++)
		d[i] = -1;
	
	cin >> m;
	for (int i = 1; i <= m; i++)
	{
		int x;
		cin >> x;
		b[x]++;
	}
		
	bool flag = true;
	for (int i = 2; i < n; i++)
	{
		if (a[i] - a[i-1] != a[i+1] - a[i])
			flag = false;
	}
	if (flag)
	{
		cout << (a[2] - a[1]) * 1ll * (m - 1) << "\n";
		return 0;
	}
	
	flag = true;
	for (int i = 2; i < n; i++)
		if (b[i] != b[1] * 2)
			flag = false;
	if (b[n] != b[1])
		flag = false;
	if (flag)
	{
		cout << -1 << "\n";
		return 0;
	}
	check(1, 1);
	check(n, -1);
	for (int i = 2; i < n; i++)
	{
		if (b[i] != b[i-1])
			check(i, 1), check(i, -1), check(i - 1, 1), check(i - 1, -1);
		if (b[i] != b[i+1])
			check(i, 1), check(i, -1), check(i + 1, 1), check(i + 1, -1);
	}
	for (int i = 1; i <= n; i++)
		if (d[i] != -1)
		{
			cout << d[i] << "\n";
			break;
		}
	return 0;
}




