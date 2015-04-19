#include <stdio.h>
#include <iostream>
#include <stack>
#include <queue>
#include <deque>
#include <map>
#include <set>
#include <vector>
#include <string>
#include <cstring>
#include <math.h>
#include <algorithm>
#include <complex>
#include <ctime>
#include <iomanip>
#include <cassert>
#include <sstream>
#include <iterator>

using namespace std;

#define file "file"
#define mp make_pair
#define pb push_back
#define xx real()
#define yy imag()
typedef long long ll;
typedef unsigned long long ull;
typedef pair<int,int> pii;
typedef vector<int> vi;
typedef complex<double> point;

const int MAXN = 20 + 5;
const int MASK = 33;
const ll BASE = 21;

int p[MAXN];
int a[MAXN];
int n,m;
int r[MAXN],c[MAXN];
vi good[MAXN];
int was;
int ans[MAXN];

map<pair<ll,ll>,int> dp;

ll hash_code(int col){
    ll ans = 0;
    for(int i = 0;i < n;i++){
        ans *= BASE;
        ans += a[i];
    }
    ans *= BASE;
    ans += col;
    return ans;
}

void precalc(){
    for(int mask = 0;mask < (1 << n);mask++){
        int block = 0;
        int last = 0;
        for(int i = 0;i < n;i++){
            if(mask & (1 << i)){
                if(!last) block++;
                last = 1;
            }
            else{
                last = 0;
            }
        }
        good[block].pb(mask);
    }
}

void rec_sol(int col,int prev){
    if(was) return;
    if(col == m){
        for(int i = 0;i < n;i++){
            if(r[i] != a[i]){
                return;
            }
        }
        was = 1;
        for(int i = 0;i < m;i++){
            ans[i] = p[i];
        }
        return;
    }
    ll code = hash_code(col);
    if(dp.find(mp(code,prev)) != dp.end()) return;
    dp[mp(code,prev)] = 1;
    for(int i = 0;i < n;i++){
        if(a[i] > r[i]){
            return;
        }
    }
    int a2[5];
    for(int i = 0;i < n;i++){
        a2[i] = a[i];
    }
    for(int i = 0;i < (int) good[c[col]].size();i++){
        int nxt = good[c[col]][i];
        for(int j = 0;j < n;j++){
            if(nxt & (1 << j)){
                if(!(prev & (1 << j))){
                    a[j]++;
                }
            }
        }
        int t = p[col];
        p[col] = nxt;
        rec_sol(col + 1,nxt);
        p[col] = t;
        if(was) return;
        for(int j = 0;j < n;j++) a[j] = a2[j];
    }
}

void solve(){
    scanf("%d%d",&n,&m);
    for(int i = 0;i < n;i++){
        scanf("%d",&r[i]);
    }
    for(int i = 0;i < m;i++){
        scanf("%d",&c[i]);
    }
    precalc();
    rec_sol(0,0);
    for(int i = 0;i < n;i++){
        for(int j = 0;j < m;j++){
            if(ans[j] & (1 << i)) printf("*");
            else printf(".");
        }
        printf("\n");
    }
}

int main()
{
	#ifndef ONLINE_JUDGE
    assert(freopen("input.txt","r",stdin));
    assert(freopen("output.txt","w",stdout));
    #else
    //assert(freopen(file".in","r",stdin)); assert(freopen(file".out","w",stdout));
    #endif
	int t = 1;
	while(t--){
		solve();
	}
	return 0;
}
