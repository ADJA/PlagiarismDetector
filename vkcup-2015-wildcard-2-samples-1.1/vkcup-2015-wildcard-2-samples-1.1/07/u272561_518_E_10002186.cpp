#include <iostream>
#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <cmath>
#include <algorithm>
#include <functional>
#include <map>
#include <numeric>
#include <queue>
#include <set>
#include <stack>
#include <unordered_map>
#include <unordered_set>
#include <utility>
#include <vector>

#define X first
#define Y second

using namespace std;
using i64 = long long;
using Pii = pair<int, int>;

constexpr int MAX = 200010;
constexpr int INF = 0x3F3F3F3F;

int a[MAX];
vector<int> ls[MAX];

bool calc(const vector<int>& ls, int l, int r, int low, int high) {
	int n = r - l + 1;
	if (high - low - 1 < n) return false;
	int u = -(n >> 1), v = n - 1 - (n >> 1);
	if (u <= low) {
		int d = low - u + 1;
		u += d; v += d;
	} else if (v >= high) {
		int d = v - high + 1;
		u -= d; v -= d;
	}
	int x = u;
	for (int i = l; i <= r; ++i) {
		a[ls[i]] = x++;
	}
	return true;
}

bool solve(int n, int k) {
	for (int r = 0; r < k; ++r) {
		ls[r].clear();
		for (int i = r; i < n; i += k) {
			ls[r].push_back(i);
		}
	}
	for (int r = 0; r < k; ++r) {
		int m = ls[r].size();
		int pre = -INF;	
		for (int i = 0; i < m; ++i) {
			if (a[ls[r][i]] == INF) continue;
			if (a[ls[r][i]] <= pre) return false;
			pre = a[ls[r][i]];
		}
		pre = -1;
		for (int i = 0; i < m; ++i) {
			if (a[ls[r][i]] < INF) {
				if (pre < i - 1) {
					int low = ~pre ? a[ls[r][pre]] : -INF;
					int high = a[ls[r][i]];
					bool ok = calc(ls[r], pre + 1, i - 1, low, high);
					if (!ok) return false;
				}
				pre = i;
			}
		}
		if (pre < m - 1) {
			int low = ~pre ? a[ls[r][pre]] : -INF;
			int high = INF;
			bool ok = calc(ls[r], pre + 1, m - 1, low, high);
			if (!ok) return false;
		}
	}
	return true;
}

int main() {
	int n, k;
	char str[16];
	while (~scanf("%d%d", &n, &k)) {
		for (int i = 0; i < n; ++i) {
			scanf("%s", str);
			if (str[0] == '?') a[i] = INF;
			else sscanf(str, "%d", &a[i]);
		}
		if (!solve(n, k)) printf("Incorrect sequence\n");
		else {
			for (int i = 0; i < n; ++i) {
				printf("%d%c", a[i], i < n - 1 ? ' ' : '\n');
			}
		}
	}
	return 0;
}
