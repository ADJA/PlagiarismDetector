#include <bits/stdc++.h>
using namespace std;
int const inf = 0x3f3f3f3f;
int a[100100];
int b[100100];
bool q[100100];
int n, k;
int ans[100100];

int main() {
	char s[20];
	scanf("%d%d", &n, &k);
	for (int i = 0; i < n; ++i) {
		scanf(" %s", s);
		if (s[0] == '?') q[i] = 1;
	 	else {
			sscanf(s, "%d", &a[i]);
		}	
	}	
	for (int i = 0; i < k; ++i) {
		int m = 0;
		for (int j = i; j < n; j += k) {
			if (q[j]) b[m++] = inf;
			else b[m++] = a[j];
		}
		for (int j = 1; j < m; ++j) {
			if (b[j] != inf && b[j - 1] != inf && b[j] <= b[j - 1]) {
					puts("Incorrect sequence");
					return 0;
			}
		}
		for (int j = 0; j < m; ++j) {
			if (b[j] == inf) {
				int l = j, r = j;
				while (l >= 0 && b[l] == inf) --l;
				while (r < m && b[r] == inf) ++r;
				int tl = (l == -1 ? -inf : b[l]);
				int tr = (r == m ? inf : b[r]);
				int e = r - l - 1;
				if (tr - tl - 1 < e) {
					puts("Incorrect sequence");
					return 0;
				}
				int v;
				if (tr <= 0) v = -tr;
				else if (tl >= 0) v = tl;
				else v = 0;
				int top = 0;
				for (; e > 0; ++v) {
					if (v > tl && v < tr) {
						ans[top++] = v;
						--e;
					}
					if (e > 0 && v != 0 && -v > tl && -v < tr) {
						ans[top++] = -v;
						--e;
					}
				}
				sort(ans, ans + top);
				for (v = l + 1; v < r; ++v) {
					a[i + v * k] = ans[v - l - 1];
				}
				j = r;
			}
		}
	}
	for (int i = 0; i < n; ++i) {
		printf("%d ", a[i]);
	}
	puts("");
	return 0;
}
