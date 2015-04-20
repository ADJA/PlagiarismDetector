#include <iostream>
#include <fstream>
#include <cmath>
#include <algorithm>
#include <vector>
#include <set>
#include <map>
#include <stack>
#include <queue>
#include <cstdlib>
#include <cstdio>
#include <string>
#include <cstring>
#include <cassert>
#include <utility>
#include <iomanip>

using namespace std;

const int MAXN = 105000;

int n, mx, t;
int diff;
int total;
int in[MAXN], out[MAXN];
queue <int> q;
int num[MAXN];
int a[MAXN];
int ans[MAXN];
int ap;
bool hasMax = false;     

int main() {
	//assert(freopen("input.txt","r",stdin));
	//assert(freopen("output.txt","w",stdout));

	scanf("%d %d %d\n", &n, &mx, &t);

	for (int i = 1; i <= n; i++) {
		int h, m, s;
		scanf("%d:%d:%d\n", &h, &m, &s);
		a[i] = h * 3600 + m * 60 + s;
		in[a[i]]++;
		out[a[i] + t - 1]++;
	}

	for (int i = 0; i <= 86400; i++) {
		for (int j = 0; j < in[i]; j++) {
			if (diff < mx) {
				diff++;
				if (diff == mx) {
					hasMax = true;
				}
				total++;
				num[total]++;
				q.push(total);
			}
			else {
				num[total]++;
				q.push(total);
			}
			ap++;
			ans[ap] = total;
		}
		for (int j = 0; j < out[i]; j++) {
			int cur = q.front();
			q.pop();
			num[cur]--;
			if (num[cur] == 0)
				diff--;
		}
	}             

	if (!hasMax) {
		puts("No solution");
		return 0;
	}

	printf("%d\n", total);
	for (int i = 1; i <= n; i++) {
		printf("%d\n", ans[i]);
	} 

	return 0;
}