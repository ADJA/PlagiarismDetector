#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <cmath>
#include <ctime>
#include <string>
#include <algorithm>
#include <vector>
#include <map>
#include <set>
#include <queue>
#include <iomanip>
#include <sstream>
#include <fstream>

using namespace std;

const int MaxN = 5100, MaxE = MaxN*2;

int n, v[MaxE], Next[MaxE], Head[MaxN], s[MaxN], ENum;
bool View[MaxN], f[MaxN][MaxN], Ans[MaxN];

inline void AddEdge(const int x, const int y)
{
	Next[++ENum] = Head[x];
	v[Head[x] = ENum] = y;
}

void DFS(const int t)
{
	View[t] = 1;
	s[t] = 1;
	f[t][0] = 1;
	for (int i = Head[t], j; i; i = Next[i])
		if (! View[v[i]])
		{
			DFS(v[i]);
			s[t] += s[v[i]];
			for (j = n; j >= s[v[i]]; --j)
				f[t][j] |= f[t][j-s[v[i]]];
		}
	for (int i = 1; i <= n; ++i)
		if (f[t][i])
			Ans[i] = Ans[i+n-s[t]] = 1;
	Ans[n-s[t]] = 1;
}

int main()
{
	#ifndef ONLINE_JUDGE
	freopen("E.in", "r", stdin);
	freopen("E.out", "w", stdout);
	#endif
	cin.sync_with_stdio(0);
	cin >> n;
	for (int i = 1, x, y; i < n; ++i)
	{
		cin >> x >> y;
		AddEdge(x, y);
		AddEdge(y, x);
	}
	DFS(1);
	int Count = 0;
	for (int i = 1; i < n-1; ++i)
		if (Ans[i])
			++Count;
	cout << Count << endl;
	for (int i = 1; i < n-1; ++i)
		if (Ans[i] || Ans[n-1-i])
			cout << i << " " << n-1-i << endl;
	return 0;
}
