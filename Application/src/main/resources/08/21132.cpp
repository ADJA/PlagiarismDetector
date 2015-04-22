#include <string>
#include <vector>
#include <algorithm>
#include <numeric>
#include <set>
#include <map>
#include <queue>
#include <iostream>
#include <sstream>
#include <cstdio>
#include <cmath>
#include <ctime>
#include <cstring>
#include <cctype>
#include <cassert>
#include <limits>
#include <functional>
#define rep(i,n) for(int (i)=0;(i)<(int)(n);++(i))
#define rer(i,l,u) for(int (i)=(int)(l);(i)<=(int)(u);++(i))
#define reu(i,l,u) for(int (i)=(int)(l);(i)<(int)(u);++(i))
#if defined(_MSC_VER) || __cplusplus > 199711L
#define aut(r,v) auto r = (v)
#else
#define aut(r,v) __typeof(v) r = (v)
#endif
#define each(it,o) for(aut(it, (o).begin()); it != (o).end(); ++ it)
#define all(o) (o).begin(), (o).end()
#define pb(x) push_back(x)
#define mp(x,y) make_pair((x),(y))
#define mset(m,v) memset(m,v,sizeof(m))
#define INF 0x3f3f3f3f
#define INFL 0x3f3f3f3f3f3f3f3fLL
using namespace std;
typedef vector<int> vi; typedef pair<int,int> pii; typedef vector<pair<int,int> > vpii; typedef long long ll;
template<typename T, typename U> inline void amin(T &x, U y) { if(y < x) x = y; }
template<typename T, typename U> inline void amax(T &x, U y) { if(x < y) x = y; }


template<unsigned P>
struct UnorderedHash {
	unsigned long long x;
	static vector<unsigned long long> p;
	static void init(int n) {
		p.assign(n, 0);
		p[0] = 1;
		reu(i, 1, n) p[i] = p[i-1] * P;
	}
	UnorderedHash(): x(0) { }
	UnorderedHash(int t): x(p[t]) { }
	UnorderedHash &operator+=(const UnorderedHash &that) {
		x += that.x; return *this;
	}
	UnorderedHash &operator-=(const UnorderedHash &that) {
		x -= that.x; return *this;
	}
	UnorderedHash operator+(const UnorderedHash &that) const { return UnorderedHash(*this) += that; }
	UnorderedHash operator-(const UnorderedHash &that) const { return UnorderedHash(*this) -= that; }
	bool operator==(const UnorderedHash<P> &that) const {
		return x == that.x;
	}
	bool operator<(const UnorderedHash<P> &that) const {
		return x < that.x;
	}
};
template<unsigned P> vector<unsigned long long> UnorderedHash<P>::p;


struct UnorderedHashes {
	UnorderedHash<1000000007> h1;
	UnorderedHash<1000000009> h2;

	static void init(int n) {
		UnorderedHash<1000000007>::init(n);
		UnorderedHash<1000000009>::init(n);
	}
	UnorderedHashes(): h1(), h2() { }
	UnorderedHashes(int t): h1(t), h2(t) { }
	UnorderedHashes &operator+=(const UnorderedHashes &that) {
		h1 += that.h1; h2 += that.h2; return *this;
	}
	UnorderedHashes &operator-=(const UnorderedHashes &that) {
		h1 -= that.h1; h2 -= that.h2; return *this;
	}
	UnorderedHashes operator+(const UnorderedHashes &that) const { return UnorderedHashes(*this) += that; }
	UnorderedHashes operator-(const UnorderedHashes &that) const { return UnorderedHashes(*this) -= that; }
	bool operator==(const UnorderedHashes &that) const {
		return
			h1 == that.h1 &&
			h2 == that.h2;
	}
	bool operator<(const UnorderedHashes &that) const {
		return
			 h1 <  that.h1 ||
			(h1 == that.h1 && h2 < that.h2);
	}
};

int geti(int i, int n) {
	i %= (n-1) * 2;
	if(i <= n-1)
		return i;
	else
		return (n-1) * 2 - i;
}

int main() {
	int n;
	scanf("%d", &n);
	vector<int> a(n);
	rep(i, n) scanf("%d", &a[i]);
	int m;
	scanf("%d", &m);
	UnorderedHashes::init(n);
	UnorderedHashes qh;
	rep(i, m) {
		int b;
		scanf("%d", &b), -- b;
		qh += b;
	}
	UnorderedHashes curh;
	long long curd = 0;
	rep(i, m) {
		if(i != 0) curd += abs(a[geti(i-1, n)] - a[geti(i, n)]);
		curh += geti(i, n);
	}
	vector<long long> v;
	rep(i, (n-1) * 2) {
		if(curh == qh)
			v.push_back(curd);
		curd += abs(a[geti(i+m-1, n)] - a[geti(i+m, n)]);
		curh += geti(i+m, n);
		curd -= abs(a[geti(i, n)] - a[geti(i+1, n)]);
		curh -= geti(i, n);
	}
	if(v.empty()) {
		cerr << "err" << endl;
		abort();
	}
	if(count(all(v), v[0]) != v.size()) {
		puts("-1");
	}else {
		cout << v[0] << endl;
	}
	return 0;
}
