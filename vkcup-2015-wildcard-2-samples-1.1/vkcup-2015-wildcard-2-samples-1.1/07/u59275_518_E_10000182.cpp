#define _CRT_SECURE_NO_WARNINGS
#pragma comment(linker, "/STACK:1000000000")
#include <iostream>
#include <algorithm>
#include <memory.h>
#include <cstring>
#include <sstream>
#include <cstdlib>
#include <complex>
#include <string>
#include <bitset>
#include <vector>
#include <cstdio>
#include <ctime>
#include <cmath>
#include <queue>
#include <stack>
#include <set>
#include <map>

using namespace std;

typedef long long ll;
typedef long double ld;
typedef unsigned long long ull;
typedef complex < double > cd;

const bool db = false;

#define mp make_pair
#define pb push_back
#define ppb pop_back
#define sd second
#define fs first

#define inf 1000000007
#define nmax 500010
#define mmax 100010
#define eps 1e-6

int n, k, a[nmax];
vector < int > g[nmax];

int main() {
	//freopen("input.txt", "r", stdin); freopen("output.txt", "w", stdout);
	//freopen("censor.in", "r", stdin); freopen("censor.out", "w", stdout);
	scanf("%d%d", &n, &k);
	for(int i = 1; i <= n; ++i) {
		char c;
		while(c = getchar(), c <= 32);
		if(c == '?') { a[i] = -inf; continue; }
		int min = 0;
		if(c == '-') min = 1; 
		else a[i] = c - '0';
		while(c = getchar(), c > 32)
			a[i] = 10 * a[i] + c - '0';
		if(min) a[i] = -a[i];
	}
	for(int i = 1; i <= n; ++i) {
		g[i % k].push_back(i);
	}
	for(int i = 0; i < k; ++i) {
		if(g[i].empty()) continue;
		vector < int > nonz;
		for(int j = 0; j < g[i].size(); ++j) {
			if(a[g[i][j]] != -inf) {
				nonz.pb(j);
			}
		}
		if(!nonz.size()) {
			int X = g[i].size();
			int pt = -X / 2;
			for(int j = 0; j < g[i].size(); ++j) {
				a[g[i][j]] = pt++;
			}
			continue;
		}
		for(int j = 0; j + 1 < nonz.size(); ++j) {
			if(a[g[i][nonz[j + 1]]] < a[g[i][nonz[j]]] + nonz[j + 1] - nonz[j]) {
				puts("Incorrect sequence");
				exit(0);
			}
			if(nonz[j] == nonz[j + 1] - 1) continue;
			long long s1 = 0, s2 = 0, s3 = 0;
			for(int x = nonz[j] + 1, val = a[g[i][nonz[j]]] + 1; x < nonz[j + 1]; ++x, ++val) {
				s1 += abs(val);
			}
			for(int x = nonz[j + 1] - 1, val = a[g[i][nonz[j + 1]]] - 1; x > nonz[j]; --x, --val) {
				s2 += abs(val);
			}
			//cout << s1 << " " << s2 << endl;
			int sz = nonz[j + 1] - nonz[j] - 1;
			if(-sz / 2 > a[g[i][nonz[j]]]) {
				for(int x = nonz[j] + 1, val = -sz / 2; x < nonz[j + 1]; ++x, ++val) {
					s3 += abs(val);
					if(x == nonz[j + 1] - 1 && val >= a[g[i][nonz[j + 1]]]) { s3 = 1LL << 60; break; }
				}
			} else s3 = 1LL << 60;
			if(s1 <= s2 && s1 <= s3) {
				for(int x = nonz[j] + 1, val = a[g[i][nonz[j]]] + 1; x < nonz[j + 1]; ++x, ++val) {
					a[g[i][x]] = val;
				}
			} else if(s2 <= s1 && s2 <= s3) {
				for(int x = nonz[j + 1] - 1, val = a[g[i][nonz[j + 1]]] - 1; x > nonz[j]; --x, --val) {
					a[g[i][x]] = val;
				}
			} else {
				for(int x = nonz[j] + 1, val = -sz / 2; x < nonz[j + 1]; ++x, ++val) {
					a[g[i][x]] = val;
				}
			}
		}
		if(a[g[i][0]] == -inf) {
			int sz = nonz[0];
			int Right = min(a[g[i][nonz[0]]] - 1, sz / 2);
			for(int j = nonz[0] - 1; j >= 0; --j) {
				a[g[i][j]] = Right--;
			}
		}
		if(a[g[i].back()] == -inf) {
			int sz = g[i].size() - 1 - nonz.back();
			int Left = max(a[g[i][nonz.back()]] + 1, -sz / 2);
			for(int j = nonz.back() + 1; j < g[i].size(); ++j) {
				a[g[i][j]] = Left++;
			}
		}
	}
	for(int i = 1; i <= n; ++i)
		cout << a[i] << (i == n ? '\n' : ' ');
	getchar(); getchar();
	return 0;
}