#include <iostream>
#include <stdio.h>
#include <algorithm>
#include <vector>
#include <queue>
#include <stack>
#include <set>
#include <map>
#include <cmath>
#include <string>
#include <cstring>
#include <cassert>
#include <cstdlib>
#include <numeric>
#include <bitset>
#include <deque>
#define mp make_pair
#define mt make_tuple
#define pb push_back
#define y1 y1_dhs
#define NAME ""

using namespace std;

typedef long long ll;
typedef long double ld;

template<typename T1, typename T2>
ostream& operator << (ostream &out, pair<T1, T2> a)
{
	return (out << "(" << a.first << "; " << a.second << ")");
}

template<typename T1>
ostream& operator << (ostream &cout, vector<T1> &a)
{
	if ((int)a.size() == 0)
		return (cout << "()");
	cout << "(" << a[0];
	for (int i = 1; i < (int)a.size(); i++)
		cout << "; " << a[i];
	cout << ")";
	return cout;
}

const int nmax = 1000 * 1000;
const int inf = 1000 * 1000 * 1000;
const int mod = 1000 * 1000 * 1000 + 7;
const ld pi = acos(-1.0);
const ll infl = 1000ll * 1000ll * 1000ll * 1000ll * 1000ll * 1000ll;

int n, k;
char s[nmax];
vector<int> a[nmax];
int b[nmax];
bool used[nmax];
int top = 0;

int main()
{
	//freopen(NAME".in", "r", stdin);freopen(NAME".out", "w", stdout);
	cin >> n >> k;
	for (int i = 0; i < n; i++)
	{
		scanf("%s", s);
		if (s[0] == '?')
			b[i] = inf + 1;
		else
			b[i] = atoi(s);
	}
	for (int i = 0; i < n; i++)
	{
		if (used[i] || b[i] != inf + 1)
			continue;
		int ind = i, ind1 = i;
		while (ind >= 0 && b[ind] == inf + 1)
			ind -= k;
		if (ind < 0)
			ind += k;
		while (ind1 < n && b[ind1] == inf + 1)
			ind1 += k;
		if (ind1 >= n)
			ind1 -= k;
		for (int j = ind; j <= ind1; j += k)
		{
			used[j] = true;
			a[top].pb(j);
		}
		top++;
	}
	for (int i = 0; i < top; i++)
	{
		if (b[a[i][0]] == inf + 1)
		{
			if (b[a[i].back()] == inf + 1)
			{
				int len = a[i].size();
				for (int j = 0; j < (int)a[i].size(); j++)
					b[a[i][j]] = -len / 2 + j;
			}
			else
			{
				int len = (int)a[i].size() - 1;
				int qq = min(len / 2, b[a[i].back()] - 1);
				for (int j = (int)a[i].size() - 2; j >= 0; j--)
					b[a[i][j]] = qq--;
			}
		}
		else
		{
			if (b[a[i].back()] == inf + 1)
			{
				int len = (int)a[i].size() - 1;
				int qq = max(b[a[i][0]] + 1, -len / 2);
				for (int j = 1; j < (int)a[i].size(); j++)
					b[a[i][j]] = qq++;
			}
			else
			{
				int len = (int)a[i].size() - 2;
				if (b[a[i].back()] - b[a[i][0]] - 1 < len)
				{
					cout << "Incorrect sequence";
					return 0;
				}
				if (b[a[i][0]] >= -len / 2)
				{
					int qq = b[a[i][0]] + 1;
					for (int j = 1; j < (int)a[i].size() - 1; j++)
						b[a[i][j]] = qq++;
				}
				else
				{
					int qq = min(len / 2, b[a[i].back()] - 1);
					for (int j = (int)a[i].size() - 2; j > 0; j--)
					{
						b[a[i][j]] = qq--;
					}
				}
			}
		}
	}
	for (int i = 0; i < n; i++)
	{
		if (i - k >= 0 && b[i - k] >= b[i])
		{
			cout << "Incorrect sequence";
			return 0;
		}
		if (i + k < n && b[i + k] <= b[i])
		{
			cout << "Incorrect sequence";
			return 0;
		}
	}
	for (int i = 0; i < n; i++)
		cout << b[i] << " ";
}

