#include <iostream>
#include <fstream>
#include <cmath>
#include <algorithm>
#include <vector>
#include <queue>
#include <cstdlib>
#include <cstdio>
#include <string>
#include <cstring>
#include <cassert>
#include <utility>
#include <iomanip>

using namespace std;

const int N = 1050;
const int di[] = {-1, 1, 0, 0};
const int dj[] = {0, 0, 1, -1};

int n, m;
int a[N][N];
bool u[N][N];
int r1, c1, r2, c2;
queue < pair <int, int> > q;

int main() {
	//assert(freopen("input.txt","r",stdin));
	//assert(freopen("output.txt","w",stdout));

	scanf("%d %d\n", &n, &m);

	for (int i = 1; i <= n; i++) {
		for (int j = 1; j <= m; j++) {
			char c;
			scanf("%c", &c);
			if (c == 'X')
				a[i][j] = 1;
			else
				a[i][j] = 0;
		}
		scanf("\n");
	}

	cin >> r1 >> c1;
	cin >> r2 >> c2;
	
	bool was = false;
	if (a[r2][c2] == 1)
		was = true;
	
	a[r1][c1] = a[r2][c2] = 0;

	u[r1][c1] = true;
	q.push(make_pair(r1, c1));

	while (!q.empty()) {
		int i = q.front().first, j = q.front().second;
		q.pop();

		for (int k = 0; k < 4; k++) {
			int ci = i + di[k], cj = j + dj[k];
			if (ci < 1 || ci > n || cj < 1 || cj > m)
				continue;
			if (u[ci][cj] || a[ci][cj] == 1)
				continue;
			u[ci][cj] = true;
			q.push(make_pair(ci, cj));
		}
	}

	if (!u[r2][c2]) {
		cout << "NO" << endl;
		return 0;
	}

	if (was && !(r1 == r2 && c1 == c2)) {
		cout << "YES" << endl;
		return 0;
	}

	int num = 0;
	for (int k = 0; k < 4; k++) {
		int ci = r2 + di[k], cj = c2 + dj[k];
		if (ci < 1 || ci > n || cj < 1 || cj > m)
			continue;
		if (a[ci][cj] == 0)
			num++;		
	}

	//cout << "NUM " << num << endl;

	if (num > 1 || (num == 1 && r1 == r2 && c1 == c2))
		cout << "YES" << endl;
	else
		cout << "NO" << endl;

	return 0;
}