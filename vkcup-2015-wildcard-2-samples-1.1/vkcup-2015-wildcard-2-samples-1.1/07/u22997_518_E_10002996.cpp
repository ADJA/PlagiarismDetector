
#include<stdio.h>
#include<string.h>
#include<math.h>
#include<stdlib.h>
#include<iostream>
#include<algorithm>
#include<string>
#include<vector>
#include<set>
#include<queue>
#include<map>
#include<bitset>
using namespace std;
#define PII pair<int,int>
#define X first
#define Y second
#define PB push_back
#define CLR(a) memset(a, 0, sizeof(a))
#define FOR(i,a,b) for (int i=(a);i<(b);i++)
#define FOE(i,a,b) for (int i=(a);i<=(b);i++)
#define FIT(i,a) for (__typeof__((a).begin()) i = (a).begin(); i != (a).end(); i++)
#define TRA(i,a,b) for (int i = (a); i != -1; i = (b)[i])
#define INF (1 << 30)
#define EPS (1e-9)
#define REP(i,n) FOR(i,0,n)
#define LL long long
#define N 200000
#define M 1000000000LL
int n, m, k;
int a[N], d[N], v[N];
char s[30];
int find(int x){
        LL lo = -2 * M, hi = 2 * M;
        int p1, p2;
        while(x < n){
                if (a[x] != M + 1){
                        if (a[x] < lo) return 0;
                        lo = a[x] + 1;
                }
                else{
                        hi = 2 * M;
                        p1 = p2 = x;
                        while(p2 < n && a[p2] == M + 1) p2 += k;
                        if (p2 < n) hi = a[p2] - 1;
                        int sz = (p2 - p1) / k;
                        if (hi + 1 - lo < sz) return 0;
                        if (hi >= 0 && lo <= 0){
                                if (hi < sz / 2){
                                        for (int i = p2 - k; i >= p1; i -= k){
                                                a[i] = hi;
                                                hi--;
                                        }
                                }
                                else if (lo > -sz/2){
                                        for (int i = p1; i < p2; i += k){
                                                a[i] = lo;
                                                lo++;
                                        }
                                }
                                else{
                                        hi = sz / 2;
                                        for (int i = p2 - k; i >= p1; i -= k){
                                                a[i] = hi;
                                                hi--;
                                        }
                                }
                        }
                        else if (hi <= 0){
                                for (int i = p2 - k; i >= p1; i -= k){
                                        a[i] = hi;
                                        hi--;
                                }
                        }
                        else {
                                for (int i = p1; i < p2; i += k){
                                        a[i] = lo;
                                        lo++;
                                }
                        }
                        x = p2 - k;
                        if (x < n) lo = a[x] + 1;
                }
                x += k;
        }
        return 1;
}
int main(){
        scanf("%d%d", &n, &k);
        FOR(i,0,n){
                scanf("%s", s);
                if (s[0] == '?') a[i] = M + 1;
                else a[i] = atol(s);
        }
        int ok = 1;
        FOR(i,0,k) if (!find(i)) {puts("Incorrect sequence"); return 0;}
        FOR(i,0,n) printf("%d ", a[i]);
        puts("");
        return 0;
}
