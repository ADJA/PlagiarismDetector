#include <stdio.h>
#include <set>
#include <string>
#include <string.h>
#include <iostream>
#include <cmath>
#include <vector>
#include <algorithm>
#include <cmath>
using namespace std;

typedef long long LL;

#define MAXN 400100
#define INF 20000000
#define tl(x) (x << 1)
#define tr(x) (x << 1 | 1)

int n, m;
int bx[MAXN];

int num[MAXN], cp[MAXN];

long long sum;

vector <int> ck1;

bool check1() {
    for(int i = 2; i < n; i++) {
        if(num[i] > 1) return false;
    }

    for(int i = 2; i < n; i++) {
        if(num[i]) ck1.push_back(i);
    }
    for(int i = 1; i < ck1.size(); i++) {
        if(ck1[i] != ck1[i - 1] + 1) return false;
    }
    return true;
}

bool check2() {
    bool one = 0, zero = 0, two = 0;
    for(int i = 2; i < n; i++) if(num[i] > 2) return false;
    for(int i = 2; i < n; i++) cp[i] = num[i];
    bool gt = 0;
    for(int i = 2; i < n; i++) {
        if(cp[i] == 2) gt = 1, cp[i]--;
        else if(cp[i] == 0) break;
        else if(cp[i] == 1) {
            if(gt) break;
            cp[i]--;
        }
    }

    for(int i = n - 1; i > 1; i--) {
        if(cp[i]) cp[i]--;
        else break;
    }

    for(int i = 2; i < n; i++) if(cp[i] != 0) return false;
    return true;
}

int main()
{
    
    scanf("%d", &n);
    for(int i = 1; i <= n; i++) scanf("%d", &bx[i]);

    scanf("%d", &m);

    for(int i = 1, a; i <= m; i++) {
        scanf("%d", &a);
        num[a]++;
    }

    for(int i = 2; i <= n; i++) sum += bx[i] - bx[i - 1];

    if(num[1] == 0 && num[n] == 0) {
        if(!check1()) {
            printf("-1\n");
            return 0;
        }
        long long ans = 0; int pre = 0;
        for(int i = 2; i < n; i++) {
            if(num[i]) {
                pre = bx[i];
                break;
            }
        }
        for(int i = 2; i < n; i++) {
            if(num[i]) ans += bx[i] - pre, pre = bx[i];
        }
        printf("%I64d\n", ans);
    } else if(num[1] == num[n]) {
        long long ans = 0;
        for(int i = 2; i < n; i++) {
            num[i] -= (num[1] * 2 - 1);
            if(num[i] < 0) {
                printf("-1\n");
                return 0;
            }
        }

        if(!check2()) {
            printf("-1\n");
            return 0;
        }

        ans += (num[1] * 2 - 1) * sum;
       
        int find = 0;
        for(int i = 2; i < n; i++) {
            if(num[i] == 2) {
                find = 1;
                break;
            } else if(num[i] == 0) {
                find = 2;
                break;
            }
        }

        if(!find) {
            int ax = -1;
            for(int i = 2; i <= n; i++) {
                if(ax == -1) ax = bx[i] - bx[i - 1];
                else if(ax != bx[i] - bx[i - 1]) {
                    printf("-1\n");
                    return 0;
                }
            }
            for(int i = 2; i < n; i++) ans += bx[i] - bx[i - 1];
            printf("%I64d\n", ans);    
        } else {
            if(find == 1) {
                bool gt = 0;
                for(int i = 2; i < n; i++) {
                    if(num[i] == 2) gt = 1, ans += bx[i] - bx[i - 1], num[i]--;
                    else if(num[i] == 1) {
                        if(gt) break;
                        ans += bx[i] - bx[i - 1];
                        num[i]--;
                    }
                }

                for(int i = n - 1; i > 1; i--) {
                    if(num[i]) ans += bx[i + 1] - bx[i];
                    else break;
                }
                printf("%I64d\n", ans);
            } else {
                for(int i = 2; i < n; i++) {
                    if(num[i]) ans += bx[i] - bx[i - 1];
                    else break;
                }
                for(int i = n - 1; i > 1; i--) {
                    if(num[i]) ans += bx[i + 1] - bx[i];
                    else break;
                }
                printf("%I64d\n", ans);
            }   
        }
    } else if(num[1] == num[n] + 1) {
        long long ans = 0;
        for(int i = 2; i < n; i++) {
            num[i] -= num[n] * 2;
            if(num[i] < 0) {
                printf("-1\n");
                return 0;
            }
        }
        ans += num[n] * sum * 2;

        for(int i = 2; i < n; i++) {
            if(num[i]) ans += bx[i] - bx[i - 1], num[i]--;
        }
        
        for(int i = 2; i < n; i++) {
            if(num[i]) ans += bx[i] - bx[i - 1], num[i]--;
        }

        for(int i = 2; i < n; i++) {
            if(num[i] != 0) {
                printf("-1\n");
                return 0;
            }
        }

        printf("%I64d\n", ans);
    } else if(num[1] + 1 == num[n]) {
        long long ans = 0;
        for(int i = 2; i < n; i++) {
            num[i] -= num[1] * 2;
            if(num[i] < 0) {
                printf("-1\n");
                return 0;
            }
        }
        ans += num[1] * sum * 2;

        for(int i = n - 1; i > 1; i--) {
            if(num[i]) ans += bx[i + 1] - bx[i], num[i]--;
        }

        for(int i = n - 1; i > 1; i--) {
            if(num[i]) ans += bx[i + 1] - bx[i], num[i]--;
        }

        for(int i = 2; i < n; i++) {
            if(num[i] != 0) {
                printf("-1\n");
                return 0;
            }
        }

        printf("%I64d\n", ans);
    } else {
        printf("-1\n");
        return 0;
    }
    
    return 0;
}