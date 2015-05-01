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

const int MAXN = 1050;

int n;
string a, b;
int ans;

int f(int a, int b) {
	if (a > b)
		swap(a, b);
	return min(b - a, 10 - b + a);
}

int main() {
	//assert(freopen("input.txt","r",stdin));
	//assert(freopen("output.txt","w",stdout));

	scanf("%d\n", &n);
	getline(cin, a);
	getline(cin, b);

	for (int i = 0; i < (int) a.length(); i++) {
		ans += f(a[i] - '0', b[i] - '0');
	}

	cout << ans << endl;

	return 0;
}