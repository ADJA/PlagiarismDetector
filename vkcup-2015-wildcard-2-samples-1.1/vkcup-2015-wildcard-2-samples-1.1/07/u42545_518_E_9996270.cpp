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

const int maxn = 100003;
int a[maxn];
vector < int > v;
int INF = 1010000000;

int toint(string s)
{
	bool flag = false;
	int pr = 0;
	if (s[0] == '-')
		pr++, flag = true;
	int ans = 0;
	for (int i = pr; i < s.length(); i++)
		ans = ans * 10 + s[i] - '0';
	if (flag)
		ans = -ans;
	return ans;
}

int getans(int cnt, int left, int right)
{
	int nl = - (cnt / 2), nr = (cnt - 1) / 2;
	int deltal = nl - (left + 1), deltar = right - 1 - nr;
	if (deltal < 0)
		nl -= deltal, nr -= deltal;
	if (deltar < 0)
		nl += deltar, nr += deltar;
	//cout << left << " " << right << " " << deltal << " " << deltar << "\n";
	return nl;
}

int main()
{
	int n, k;
	cin >> n >> k;
	for (int i = 1; i <= n; i++)
	{
		string s;
		cin >> s;
		if (s == "?")
			a[i] = -INF;
		else
			a[i] = toint(s);
	}
	bool flag = true;
	for (int i = 1; i <= k; i++)
	{
		v.clear();
		v.pb(-INF + 1);
		for (int j = i; j <= n; j += k)
			v.pb(a[j]);
		v.pb(INF-1);
		int cnt = 0;
		int left;
		for (int j = 0; j < v.size(); j++)
		{
			if (v[j] == -INF)
			{
				cnt++;
			}
			else
			{
				if (j != 0 && v[j] - v[j-cnt-1] < cnt + 1)
					flag = false;
				if (cnt)
				{
					int x = getans(cnt, left, v[j]);
					for (int g = j - cnt; g < j; g++)
						v[g] = x + (g - (j - cnt));
				}
				cnt = 0;
				left = v[j];
			}
		}
		for (int j = 0; j < v.size() - 2; j++)
			a[k * j + i] = v[j+1];
	}
	if (flag)
	{
		for (int i = 1; i <= n; i++)
			cout << a[i] << " ";
		cout << "\n";
	}
	else
	{
		cout << "Incorrect sequence\n";
	}
	return 0;
}
