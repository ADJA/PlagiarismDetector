#include <cstdio>
#include <iostream>
#include <algorithm>
#include <cstring>
#include <vector>
#include <cstring>
#include <queue>
#include <set>
using namespace std;
#define pii pair<int,  int>
#define x first
#define y second
#define mp make_pair
#define pb push_back
#define VI vector<int>
#define all(s) (s).begin(),(s).end()
#define bp push_back
#define L(s) (int)(s).size()
#define ll long long
#define inf 1000000000
int n, k;
int a[111111];
char str[111];
int main() {
	scanf("%d%d", &n, &k);
	for(int i = 0; i < n; ++i) {
		scanf("%s", str);
		if (str[0] == '?') {
			a[i] = inf + inf;
		} else {
			sscanf(str, "%d", &a[i]);
		}
	}

	for(int st = 0; st < k; ++st) {
		VI vals(0);
		vals.pb(-inf - inf);
		for(int el = st; el < n; el += k) {
			vals.pb(a[el]);
		}
		vals.pb(inf + inf + 100);

		for(int i = 0; i < L(vals) - 1; ) {
			int low = vals[i];
			int j = i + 1;
			while(j < L(vals) && vals[j] == inf + inf) ++j;

			int high = vals[j];

			if (low + j - i - 1 >= high) {
			//	cerr << i << " " << j << endl;
				printf("Incorrect sequence\n");
				exit(0);
			}

			if (high <= 0) {
				for(int pos = j - 1; pos > i; --pos) {
					vals[pos] = vals[pos + 1] - 1;
				}
			} else
				if (low >= 0) {
					for(int pos = i + 1; pos < j; ++pos) {
						vals[pos] = vals[pos - 1] + 1;
					}
				} else if (j - i - 1 > 0) {
					VI ins(0);
					ins.pb(0);
				//	cerr << low << " " << high << endl;
					for(int el = 1; ;++el) {
						if (L(ins) == j - i - 1) break;
						if (el < high) ins.pb(el);
						if (L(ins) == j - i - 1) break;
						if (-el > low) ins.pb(-el);
					}
					sort(all(ins));
					for(int pos = i + 1; pos < j; ++pos) {
						vals[pos] = ins[pos - i - 1];
					}
				//	cerr << ins[0] << " " << ins[1] << endl;
				//	cerr << L(ins) << endl;
				//	cerr << vals[1] << " " << vals[2] << endl;
				//	exit(0);
				}

			i = j;
		}

		for(int el = st, pos = 1; el < n; el += k, ++pos) {
			a[el]  = vals[pos];
		}
	}

	for(int i = 0; i < n; ++i) {
		if (i) printf(" ");
		printf("%d", a[i]);
	}
	printf("\n");
}
