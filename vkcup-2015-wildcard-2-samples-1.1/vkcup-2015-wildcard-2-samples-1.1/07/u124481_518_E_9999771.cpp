#include "bits/stdc++.h"

using namespace std;

const int QUESTION_MARK = -(int) 1e9 - 3e8;
const int INF = (int) 1e9 + 1e8;
const long long LINF = (long long) 1e18;

char buf[1005];

long long getSum(long long start, int len) {
	long long ans = 0; 
	for (int i = 0; i < len; i++) {
		ans += abs(start + i);
	}
	return ans;
}


void noSolution() {
	printf("Incorrect sequence\n");
	exit(0);
}

long long doIt(int total, long long lo, long long hi) {
	long long best = LINF;
	long long where = lo;
	for (int it = 0; it < 100; it++) {
		long long mid1 = lo + (hi - lo) / 3;
		long long mid2 = hi - (hi - lo) / 3;
		long long mid1Val = getSum(mid1, total);
		long long mid2Val = getSum(mid2, total);
		if (mid1Val < mid2Val) {
			hi = mid2;
		} else {
			lo = mid1;
		}
		if (mid1Val < best) {
			best = mid1Val;
			where = mid1;
		} 
		if (mid2Val < best) {
			best = mid2Val;
			where = mid2;
		}
	}
	//cerr << "cc " << best << " " << where << endl;
	return where;
}

void print(std::vector<int> a) {
	cout << "printing a" << endl;
	for (int i = 0; i < a.size(); i++) {
		cout << a[i] << " ";
	}
	cout << endl;
}

std::vector<int> solve(std::vector<int> a) {
	//cout << "here " << endl;
	//print(a);
	long long lower = -INF;
	long long upper = INF;
	for (int i = 0; i < a.size(); ) {
		if (a[i] != QUESTION_MARK) {
			lower = a[i] + 1;
			i++;
			continue;
		}
		upper = INF;
		int curLen = 0;
		int nextPosition = -1;
		for (int j = i; j < a.size(); j++) {
			if (a[j] != QUESTION_MARK) {
				nextPosition = j;
				upper = a[j] - 1;
				break;
			}
			curLen++;
		}
		//cout << "hey " << lower << " " << upper << " " << curLen << endl;
		if (upper - lower < curLen - 1) {
			noSolution();
		} 
		long long startVal = doIt(curLen, lower, upper - curLen + 1L);
		//cout << "hey bro " << startVal << endl;
		for (int j = i; j < a.size(); j++) {
			if (a[j] != QUESTION_MARK) {
				break;
			}
			a[j] = startVal + j - i;
		}
		if (nextPosition == -1) {
			break;
		} else {
			i = nextPosition;
		}
	}
	return a;
}

const int MAXN = (int) 1e5 + 10;
int a[MAXN];

bool sorted(std::vector<int> a) {
	for (int i = 1; i < a.size(); i++) {
		if (a[i] <= a[i - 1]) {
			return false;
		}
	}
	return true;
}

int main() {
	int n, k;
	scanf("%d %d", &n, &k);
	for (int i = 0; i < n; i++) {
		scanf("%s", buf);
		int t;
		if (strcmp(buf, "?") == 0) {
			t = QUESTION_MARK;
		} else {
			t = atoi(buf);
		}
		a[i] = t;
	}
	for (int i = 0; i < k; i++) {
		std::vector<int> b;
		for (int j = i; j < n; j += k) {
			b.push_back(a[j]);
		}
		//cout << "bol bhai " << b.size() << endl;
		//print(b);
		vector<int> res = solve(b);
		//print(res);
		if (!sorted(res)) {
			noSolution();
		}
		int cnt = 0;
		for (int j = i; j < n; j += k) {
			a[j] = res[cnt++];
		}
	}
	for (int i = 0; i < n; i++) {
		printf("%d ", a[i]);
	}
	printf("\n");
	return 0;
}