//g++ -std=c++0x your_file.cpp -o your_program
#include<iostream>
#include<fstream>
#include<string>
#include<algorithm>
#include<math.h>
#include<vector>
#include<cstring>
#include<cstdio>
#include<cstdlib>
#include<queue>
#include<map>
#include<set>
#define fname ""
#define mp make_pair
#define F first
#define pb push_back
#define S second
#define ub upper_bound
#define lb lower_bound
#define inf 2000000000
#define INF 2000000000000000000ll
using namespace std;

const int maxn = 101010;

vector <pair <int, int> > a[maxn];

int b[maxn];

int last[maxn];

char s[20 * maxn];

int n, k;

void fill_stupid(int l, int r, int i)
{
	if (r - l <= 1)
		return ;
	int idl, idr;
	idl = l * k + i, idr = r * k + i;
	if (idr <= n && b[idr] <= 0)
	{
		int val = b[idr];
		for (int j = r - 1; j > l; j--)
			b[j * k + i] = --val;
		return ;
	}
	int val = b[idl];
	for (int j = l + 1; j < r; j++)
		b[j * k + i] = ++val;
	return ;
}

void fill_not_so_stupid(int l, int r, int i)
{
	if (r - l <= 1)
		return ;
	int idl, idr;
	idl = l * k + i, idr = r * k + i;
	if (l == -1 || idr > n)
	{
		fill_stupid(l, r, i);
		int mid = l + (r - l) / 2;
		if (l < mid && mid < r)
		{
			int id = mid * k + i;
			if ((l == -1 && b[id] > 0) || (idr > n && b[id] < 0))
			{
				b[id] = 0;
				for (int j = 1; mid + j < r; j++)
					b[(mid + j) * k + i] = j;
				for (int j = -1; mid + j > l; j--)
					b[(mid + j) * k + i] = j;
			}
		}
		return ;
	}
	int MinVal, MaxVal;
	int mid = l + (r - l) / 2;
	int val = b[idl];
	for (int j = l + 1; j < r; j++)
		b[j * k + i] = ++val;
	MinVal = b[mid * k + i];
	val = b[idr];
	for (int j = r - 1; j > l; j--)
		b[j * k + i] = --val;
	MaxVal = b[mid * k + i];
	if (MinVal <= 0 && MaxVal >= 0)
	{
		int id = mid * k + i;
		b[id] = 0;
		for (int j = 1; mid + j < r; j++)
			b[(mid + j) * k + i] = j;
		for (int j = -1; mid + j > l; j--)
			b[(mid + j) * k + i] = j;
	}
	else if (MaxVal < 0)
	{
		val = b[idr];
		for (int j = r - 1; j > l; j--)
			b[j * k + i] = --val;
	}
	else
	{
		val = b[idl];
		for (int j = l + 1; j < r; j++)
			b[j * k + i] = ++val;
	}
}
	
int main()
{
	#ifndef ONLINE_JUDGE
	freopen (fname".in", "r", stdin);
	freopen (fname".out", "w", stdout);
	#endif
	cin >> n >> k;
	scanf("\n");
	gets(s);
	int m = (int)strlen(s);
	int it = 1;
	for (int i = 0; i < m; i++)
	{
		if (s[i] == '?')
		{
			b[it++] = inf;
			continue;
		}
		else if (isdigit(s[i]))
		{
			while (i < m && isdigit(s[i]))
			{
				b[it] = b[it] * 10 + (int)s[i] - '0';
				i++;
			}
			it++;
		}
		else if (s[i] == '-')
		{
			i++;
			while (i < m && isdigit(s[i]))
			{
				b[it] = b[it] * 10 + (int)s[i] - '0';
				i++;
			}
			b[it] = -b[it];
			it++;
		}
	}
	pair <int, int> cur;
	for (int i = 1; i <= k; i++)
	{
		for (int j = 0; j * k + i <= n; j++)
		{
			int id = j * k + i;
			if (b[id] != inf)
			{
				if ((int)a[i].size() != 0)
				{
					cur = a[i][(int)a[i].size() - 1];
					if (j - cur.S > b[id] - cur.F)
					{
						cout << "Incorrect sequence";
						return 0;
					}
				}
				a[i].pb(mp(b[id], j));
			}
			last[i] = j;
		}
	}
	for (int i = 1; i <= k; i++)
	{
		if (!(int)a[i].size())
		{
			for (int j = 0; j <= last[i]; j++)
				b[j * k + i] = j - (last[i] + 1) / 2;
			continue;
		}
		if (a[i][0].F <= 0)
			fill_stupid(-1, a[i][0].S, i);
		else
			fill_not_so_stupid(-1, a[i][0].S, i);
		cur = a[i][(int)a[i].size() - 1];
		if (cur.F >= 0)
			fill_stupid(cur.S, last[i] + 1, i);
		else
			fill_not_so_stupid(cur.S, last[i] + 1, i);
		for (int j = 0; j < (int)a[i].size() - 1; j++)
		{
			if (a[i][j].F >= 0)
				fill_stupid(a[i][j].S, a[i][j + 1].S, i);
			else if (a[i][j + 1].F <= 0)
				fill_stupid(a[i][j].S, a[i][j + 1].S, i);
			else
				fill_not_so_stupid(a[i][j].S, a[i][j + 1].S, i);
		}
	}
	for (int i = 1; i <= n; i++)
		printf("%d ", b[i]);
	return 0;
}
