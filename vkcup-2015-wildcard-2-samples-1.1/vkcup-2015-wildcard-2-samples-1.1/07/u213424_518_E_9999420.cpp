#include <bits/stdc++.h>
using namespace std;

const int N = 131420;

int n, k, x;
vector<int> rem[N];

bool Gao(vector<int> &arr, int lid, int rid, int lv, int rv) {
	int s = rid - lid + 1, h = s >> 1;
	long long vd = rv - 1LL - lv;

	//cout << lid << ' ' << rid << ' ' << lv << ' ' << rv << endl;
	if (s == 0) {
		return lv < rv;
	}
	if (vd < s) {
		return 0;
	}
	if (lv < -h && h < rv) {
		for (int i = lid, j = -h; i <= rid; ++i, ++j) {
			arr[i] = j;
		}
	} else {
		if (lv >= -h) {
			for (int i = lid, j = lv + 1; i <= rid; ++i, ++j) {
				arr[i] = j;
			}
		} else {
			for (int i = rid, j = rv - 1; i >= lid; --i, --j) {
				arr[i] = j;
			}
		}
	}

	return 1;
}

bool Gao(vector<int> &arr) {
	int last = 0, value = INT_MIN;

	for (int i = 0; i < int(arr.size()); ++i) {
		if (arr[i] != INT_MAX) {
			if (Gao(arr, last, i - 1, value, arr[i])) {
			} else {
				return 0;
			}
			last = i + 1;
			value = arr[i];
		}
	}
	if (last < int(arr.size())) {
		if (Gao(arr, last, int(arr.size()) - 1, value, INT_MAX)) {
		} else {
			return 0;
		}
	}

	return 1;
}

int Run() {
	while (cin >> n >> k) {
		string buff;

		assert(n >= k);
		for (int i = 0; i < n; ++i) {
			cin >> buff;
			//cout << buff << endl;
			if (buff[0] == '?') {
				rem[i % k].push_back(INT_MAX);
			} else {
				sscanf(buff.c_str(), "%d", &x);
				rem[i % k].push_back(x);
			}
		}
		bool ok = 1;

		for (int i = 0; ok && i < k; ++i) {
			ok &= Gao(rem[i]);
			//cout << i << ' ' << ok << endl;
		}
		if (ok) {
			for (int i = 0; i < n; ++i) {
				cout << rem[i % k][i / k] << ' ';
			}
			cout << endl;
		} else {
			cout << "Incorrect sequence" << endl;
		}
	}

	return 0;
}

int main() {
	ios::sync_with_stdio(0);
	return Run();
}
