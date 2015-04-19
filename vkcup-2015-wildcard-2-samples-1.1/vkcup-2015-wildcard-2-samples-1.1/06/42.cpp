#include <iostream>

using namespace std;

typedef long long int num;

int divup(int a, int b) {
	int res = a/b;
	if (a%b) res++;
	return res;
}

int main() {
	int n, q;
	cin >> n >> q;
	num sizes[n];
	num sizesum = 0;
	for (num& x : sizes) cin >> x, sizesum += x;
	//cout << sizesum << endl;
	int next[n];
	int time[n], rounds[n];
	for (int query=0; query<q; query++) {
		int b;
		cin >> b;
		if (b >= sizesum) {
			cout << 1 << endl;
			continue;
		}
		num cont = 0;
		for (int i=0, nexti=0; i<n; i++) {
			while (cont+sizes[nexti] <= b) {
				cont += sizes[nexti];
				nexti++; nexti = nexti % n;
			}
			next[i] = nexti;
			cont -= sizes[i];
		}
	//	for (int i=0; i<n; i++) cout << i << " "; cout << endl;
	//	for (int x : next) cout << x << " "; cout << endl;
		for (int& x : time) x = 0;
		for (int& x : rounds) x = 0;
		for (int i=0, t=1, r=0; ; t++, i = next[i]) {
			if (time[i]) {
	//			for (int x : time) cout << x << " "; cout << endl;
	//			for (int j=0; j<n; j++) cout << (j==i?"*":" ") << " "; cout << endl;
				cout << divup(t-time[i], r-rounds[i]) << endl;
				break;
			}
			time[i] = t;
			rounds[i] = r;
			if (next[i] < i) r++;
		}
	}
}
