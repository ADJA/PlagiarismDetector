#include <iostream>
#include <cstdio>
#include <ctime>
#include <cassert>
#include <cmath>
#include <stack>
#include <set>
#include <map>
#include <vector>
#include <queue>
#include <algorithm>
#include <utility>
#include <cstdlib>
#include <cstring>
#include <string>
using namespace std;

#ifdef WIN32
	#define lld "%I64d"
#else
	#define lld "%lld"
#endif

#define mp make_pair
#define pb push_back
#define put(x) { cerr << #x << " = "; cerr << (x) << endl; }
                                                                                                                                                               
typedef long long ll;
typedef long double ld;
typedef unsigned long long ull;
typedef double db;

const int M = 15 * 1e5 + 15 * 15 * 15;
const int Q = 1e9 + 7;


ll suf[M], pref[M], po[M];
map<ll, int> ma;

int a[M], b[M];
                                        	

ll dist(ll i, int n, int m){
	i %= (2 * n - 2);
	
	if (i + m - 1 >= 2 * n - 2){
		ll res = suf[i] + pref[(i + m - 1) % (2 * n - 2)];
		ll m1 = m;
		m -= (2 * n - 2 - i);
		m -= ((i + m1 - 1) % (2 * n - 2) + 1);
		res += suf[0] * (m / (2 * n - 2));
		return res;
	}
	else{
		return suf[i] - suf[i + m - 1];
	}
}
ll ans = -1;
void upd(ll x){
	if (ans == -1){
		ans = x;
		return;
	}
	if (ans != x){
		printf("-1");
		exit(0);
	}
}


ll next(ll pos, int c, int n){
	if (pos == -1)
		return c - 1;
   	if (c == 1 || c == n)
   		return pos + 2 * n - 2;
   	int ost = pos % (2 * n - 2);
   	if (pos % (2 * n - 2) < n)
   		return pos - ost + (2 * n - 2 - ost);
   	else
   		return pos + (2 * n - 2 - ost) * 2;
}
int main(){
	srand(time(NULL));
#ifndef ONLINE_JUDGE
	freopen("input.txt", "r", stdin);
	freopen("output.txt", "w", stdout);
#endif
	int n, m;
	scanf("%d", &n);
	for (int i = 0; i < n; i++)
		scanf("%d", &a[i]);
	pref[0] = 0;
	for (int i = 1; i < n; i++)
		pref[i] = pref[i - 1] + a[i] - a[i - 1];
	for (int i = n; i < 2 * n - 2; i++)
		pref[i] = pref[i - 1] + a[2 * n - i - 1] - a[2 * n - i - 2];
	for (int i = 2 * n - 3; i >= 0; i--)
		suf[i] = pref[2 * n - 2 - i];
	suf[0] = suf[1] + a[1] - a[0];

	scanf("%d", &m);
	for (int i = 0; i < m; i++)
		scanf("%d", &b[i]);

	for (int i = 1; i <= n; i++)
		po[i] = -1;
	ll l = 1e17, r = -1;
	for (int i = 0;i < m; i++){
		ll cur = next(po[b[i]], b[i], n);
		ma[cur] = b[i];
		po[b[i]] = cur;
		l = min(l, cur);
		r = max(r, cur);
	}	
	for (int i = 0; i < 2 * n - 2; i++){
		if (ma[l] == 0){
			l++;
			continue;
		}
		if (r - l + 1 == m)               {

			upd(dist(l, n, m));
		}	
		ll cur = next(po[ma[l]], ma[l], n);
		ma[cur] = ma[l];
		po[ma[l]] = cur;
		r = max(r, cur);
		l++;
	}
	cout << ans;	
	return 0;
}	