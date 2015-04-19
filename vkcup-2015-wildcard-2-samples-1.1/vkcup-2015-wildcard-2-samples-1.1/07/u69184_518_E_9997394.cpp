#include <map>
#include <set>
#include <cmath>
#include <ctime>
#include <deque>
#include <queue>
#include <stack>
#include <bitset>
#include <cctype>
#include <cstdio>
#include <vector>
#include <cassert>
#include <complex>
#include <cstdlib>
#include <cstring>
#include <fstream>
#include <iomanip>
#include <sstream>
#include <iostream>
#include <algorithm>
using namespace std;
#define int long long

const int N = 1e5 + 23, inf = 0x3f3f3f3f;
int a[N];

inline int inp()
{
	int c = getchar(), x = 0;
	bool neg = 0;
	for (; ((c < 48 or c > 57) and c != '-' and c != '?'); c = getchar());
	if (c == '?') return inf;
	if (c == '-') neg = 1, c = getchar();
	for (; c > 47 and c < 58; c = getchar())
		x = (x << 1) + (x << 3) + c - 48;
	return neg ? -x : x;
}

bool fix(int st, int en, int n, int k)
{
	int lo = (st < 0 ? -inf : a[st]) + 1;
	int hi = (en >= n ? inf : a[en]) - 1;
	int num = (en - st) / k - 1;
	if (hi - lo + 1 < num) return false;
	if (lo >= 0)
	{
		for (int i = st + k; i < en; i += k)
			a[i] = lo++;
		return true;
	}
	if (hi <= 0)
	{
		for (int i = en - k; i > st; i -= k)
			a[i] = hi--;
		return true;
	}
	int fst = (num - 1) / 2;
	int snd = num / 2;
	if (fst > abs(lo))
	{
		snd += fst - abs(lo);
		fst = abs(lo);
	}
	else if (snd > hi)
	{
		fst += snd - hi;
		snd = hi;
	}
	int cur = -fst;
	for (int i = st + k; i < en; i += k)
		a[i] = cur++;
	return true;
}

bool go(int r, int n, int k)
{
	int prev = r - k;
	for (int i = r; i < n; i += k)
	{
		if (a[i] < inf)
		{
			if (prev >= 0 and a[prev] >= a[i]) return false;
			prev = i;
			continue;
		}
		while (i < n and a[i] == inf) i += k;
		bool can = fix(prev, i, n, k);
		if (!can) return false;
		prev = i;
	}
	return true;
}

#undef int
int main()
{
#define int long long
//	freopen("in", "r", stdin);
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);

	int n = inp(), k = inp();
	for (int i = 0; i < n; i++) a[i] = inp();
	for (int i = 0; i < k; i++)
		if (!go(i, n, k))
		{
			cout << "Incorrect sequence\n";
			return 0;
		}
	for (int i = 0; i < n; i++) cout << a[i] << " ";
	cout << "\n";
	return 0;
}