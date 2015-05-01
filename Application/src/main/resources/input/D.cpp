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

const int MAXN = 105;

int r, s, p;
double dp[MAXN][MAXN][MAXN];
bool used[MAXN][MAXN][MAXN];
queue <int> rq, sq, pq;
double rans, sans, pans;

double calc(int a, int b, int c) {
	int total = a + b + c;
	int ways = a * b + b * c + a * c;
	int need = a * b;
	return 1.0 * need / ways;
}

int main() {
	//assert(freopen("input.txt","r",stdin));
	//assert(freopen("output.txt","w",stdout));

	scanf("%d %d %d", &r, &s, &p);

	dp[r][s][p] = 1.0;
	rq.push(r);
	sq.push(s);
	pq.push(p);

	used[r][s][p] = true;  

	while (!rq.empty()) {

		int rr = rq.front();
		rq.pop();
		int ss = sq.front();
		sq.pop();
		int pp = pq.front();
		pq.pop();

		//cout << rr << " " << ss << " " << pp << " " << dp[rr][ss][pp] << endl;

		if (rr > 0 && ss == 0 && pp == 0) {
			rans += dp[rr][ss][pp];
			continue;
		}
		if (ss > 0 && rr == 0 && pp == 0) {
			sans += dp[rr][ss][pp];
			continue;
		}
		if (pp > 0 && rr == 0 && ss == 0) {
			pans += dp[rr][ss][pp];
			continue;
		}

		if (rr && ss) {
			dp[rr][ss - 1][pp] += dp[rr][ss][pp] * calc(rr, ss, pp);
			if (!used[rr][ss - 1][pp]) {
				used[rr][ss - 1][pp] = true;
				rq.push(rr);
				sq.push(ss - 1);
				pq.push(pp);
			}
		}	


		if (rr && pp) {
			dp[rr - 1][ss][pp] += dp[rr][ss][pp] * calc(rr, pp, ss);
			if (!used[rr - 1][ss][pp]) {
				used[rr - 1][ss][pp] = true;
				rq.push(rr - 1);
				sq.push(ss);
				pq.push(pp);
			}
		}	


		if (pp && ss) {
			dp[rr][ss][pp - 1] += dp[rr][ss][pp] * calc(pp, ss, rr);
			if (!used[rr][ss][pp - 1]) {
				used[rr][ss][pp - 1] = true;
				rq.push(rr);
				sq.push(ss);
				pq.push(pp - 1);
			}
		}	
	}

	printf("%.12lf %.12lf %.12lf\n", rans, sans, pans);

	return 0;
}