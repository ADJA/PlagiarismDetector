#include <iostream>
#include <cmath>
#include <vector>
#include <algorithm>

using namespace std;

typedef int TOF;

// sorry for this .. :-| but the bug was with long long .. :(
#define int long long

const int QUES = 1e9 + 7;

int st2int(string s) {
	if (s[0] == '?')
		return QUES;
	int ret = 0;
	for (int i = (s[0] == '-'); i < s.size(); i++) {
		ret = ret * 10 + s[i] - '0';
	}
	if (s[0] == '-')
		ret *= -1;
//	cerr << " tabdil " << s << " " << ret << endl;
	return ret;
}

const int MAXN = 1e5 + 10;

int a[MAXN];

TOF main() {
	int n, k;
	cin >> n >> k;
	for (int i = 0; i < n; i++) {
		string s;
		cin >> s;
		a[i] = st2int(s);
//		cerr << i << " " << a[i] << endl;
	}
	for (int st = 0; st < k; st++) {
		vector<int> cur;
		cur.push_back(-2 * QUES);
		for (int j = st; j < n; j += k) {
			cur.push_back(a[j]);
//			cerr << " fucking " << j << " " << a[j] << endl;
		}
		cur.push_back(2 * QUES);
		int ind = 0;
		while (ind + 1 < cur.size()) {
			vector<int> tof;
			int sz = 0;
			int lo = cur[ind];
			ind++;
			while (cur[ind] == QUES)
				ind++, sz++;
			int hi = cur[ind];
//			cerr << " lo " << lo << " hi " << hi << " sz " << sz << endl;
			if (hi - lo - 1 < sz) {
				cout << "Incorrect sequence" << endl;
				return 0;
			}
			if (hi <= 0) {
				for (int i = 0; i < sz; i++) {
					int tmp = hi - i - 1;
//					cerr << "  here " << tmp << endl;
					tof.push_back(tmp);
				}
			}
			else if (lo >= 0) {
				for (int i = 0; i < sz; i++) {
					int tmp = lo + i + 1;
					tof.push_back(tmp);
				}
			}
			else {
				int l = -1, r = 0, tmpSz = sz;
				while(sz) {
					int tmp = QUES;
					if (r == hi)
						tmp = l, l--;
					else if (l == lo)
						tmp = r, r++;
					else {
						if (-l < r)
							tmp = l, l--;
						else
							tmp = r, r++;
					}
					tof.push_back(tmp);
					sz--;
				}
				sz = tmpSz;
			}
			sort(tof.begin(), tof.end());
			reverse(tof.begin(), tof.end());
			for (int i = 0; i < sz; i++) {
				a[(ind - i - 2) * k + st] = tof[i];
			}
		}
	}
	for (int i = 0; i < n; i++)
		cout << a[i] << " ";
	cout << endl;
	return 0;
}
