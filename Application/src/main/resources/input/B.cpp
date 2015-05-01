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

int n, k, p, sum, med;
int g, cursum;

int main() {
	//assert(freopen("input.txt","r",stdin));
	//assert(freopen("output.txt","w",stdout));

	scanf("%d %d %d %d %d", &n, &k, &p, &sum, &med);

	for (int i = 1; i <= k; i++) {
		int x;
		scanf("%d", &x);
		cursum += x;
		if (x >= med)
			g++;
	}

	vector <int> ansv;

	for (int i = k + 1; i <= n; i++) {
		if (g < (n + 1) / 2) {
			ansv.push_back(med);
			cursum += med;
			g++;
		}
		else {
			ansv.push_back(1);
			cursum++;
			if (1 >= med)
				g++;
		}
	}

	if (cursum > sum || g < (n + 1) / 2) {
		puts("-1");
	}
	else {
		for (int i = 0; i < (int) ansv.size(); i++) {
			printf("%d ", ansv[i]);
		}
		cout << endl;
	}

	return 0;
}