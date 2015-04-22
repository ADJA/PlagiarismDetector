#include <cstdio>
#include <algorithm>

using namespace std;

int dat[1000000];
int jumplen[1000000];
pair<int,int> grplen[2000000];

pair<int,int> getroot(int p)
{
	int sum = 0;
	int np = p;
	while(p != grplen[p].first) {
		sum += grplen[p].second;
		p = grplen[p].first;
	}
	int tsum = sum;
	while(np != grplen[np].first) {
		int tp = grplen[np].first;
		int tl = grplen[np].second;
		grplen[np].first = p;
		grplen[np].second = sum;
		sum -= tl;
		np = tp;
	}
	return make_pair(p, tsum);
}

int main()
{
	int n,Q;
	scanf("%d%d",&n,&Q);
	for (int i = 0; i < n; i++) {
		scanf("%d",&dat[i]);
	}
	while(Q--){
		int B;
		scanf("%d",&B);
		int j = 0;
		long long tot = 0;
		for (int i = 0; i < n; i++) {
			int tmp;
			while (j < i+n && tot + (tmp =dat[j >= n ? (j-n) : j]) <= B) {
				tot += tmp;
				j++;
			}
			jumplen[i] = j-i;
			tot -= dat[i];
		}
		int ans = n;
		for (int i = 0; i < 2*n; i++) {
			grplen[i] = make_pair(i, 0);
		}
		for (int i = 0; i < n; i++) {
			int p, l;
			int curcnt = 0;
			auto r = getroot(i);
			p = r.first; l = r.second;
			curcnt = l;
			while(p < i + n) {
				int np = min(2*n-1, p + jumplen[p % n]);
				auto nr = getroot(np);
				grplen[p].first = nr.first;
				grplen[p].second = nr.second + 1;
				p = nr.first;
				curcnt += nr.second + 1;
			}
			ans = min(ans, curcnt);
		}
		printf("%d\n", ans);
	}
	return 0;
}