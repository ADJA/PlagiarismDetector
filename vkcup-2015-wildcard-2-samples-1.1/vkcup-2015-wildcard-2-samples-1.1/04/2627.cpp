/*
 * 2012-07-15  contest  <contest@vk19>

 * 
 */
#include <cstdio>
#include <cstring>
#include <cctype>
#include <cmath>
#include <ctime>
#include <cstdlib>
#include <cstdarg>
#include <iostream>
#include <fstream>
#include <iomanip>
#include <sstream>
#include <exception>
#include <stdexcept>
#include <memory>
#include <locale>
#include <bitset>
#include <deque>
#include <list>
#include <map>
#include <set>
#include <queue>
#include <stack>
#include <vector>
#include <algorithm>
#include <iterator>
#include <functional>
#include <string>
#include <complex>
#include <valarray>
#include <climits>

using namespace std;

template <class T> inline T checkmin(T &a, T b)
{
	return (a < b) ? a : a = b;
}

template <class T> inline T checkmax(T &a, T b)
{
	return (a > b) ? a : a = b;
}

template <class T> inline T sqr(T x)
{
	return x * x;
}

#define tr(i, x) for (typeof(x.begin()) i = x.begin(); i != x.end(); ++ i)
#define rep(i, n) for (int i = 0; i < n; ++ i)
#define cmplxd complex <double>
#define pii pair <int, int>
#define ll long long
#define mp make_pair
#define pb push_back
#define x first
#define y second

namespace Poor
{
	const int MaxiN = 5005;
	
	int N;
	int Pa[MaxiN], Sz[MaxiN];
	bool Able[MaxiN], Bag[MaxiN];
	vector <int> Adj[MaxiN];
	
	void DFS(int Cur)
	{
		Sz[Cur] = 1;
		tr (it, Adj[Cur])
			if (Pa[Cur] != *it)
			{
				Pa[*it] = Cur;
				DFS(*it);
				Sz[Cur] += Sz[*it];
			}
	}
	
	void Do(int Cur)
	{
		vector <int> List;
		if (Sz[0] - Sz[Cur] > 0)
			List.pb(Sz[0] - Sz[Cur]);
		tr (it, Adj[Cur])
			if (Pa[*it] == Cur)
				List.pb(Sz[*it]);
		fill(Bag, Bag + N, 0);
		Bag[0] = 1;
		tr (it, List)
			for (int i = N - 2; i >= *it; -- i)
				Bag[i] |= Bag[i - *it];
		for (int i = 1; i < N - 1; ++ i)
			Able[i] |= Bag[i];
	}
	
	void Run()
	{
		scanf("%d", &N);
		rep (i, N - 1)
		{
			int U, V;
			scanf("%d%d", &U, &V);
			-- U, -- V;
			Adj[U].pb(V);
			Adj[V].pb(U);
		}
		fill(Pa, Pa + N, - 1);
		DFS(0);
		fill(Able, Able + N, 0);
		rep (i, N)
			Do(i);
		int Ans = 0;
		for (int i = 1; i < N - 1; ++ i)
			Ans += Able[i];
		printf("%d\n", Ans);
		for (int i = 1; i < N - 1; ++ i)
			if (Able[i])
				printf("%d %d\n", i, N - i - 1);
	}
}

int main()
{
	#ifndef ONLINE_JUDGE
	freopen("E.in", "r", stdin);
	freopen("E.out", "w", stdout);
	#endif
	Poor::Run();
	return 0;
}
