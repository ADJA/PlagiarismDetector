#include<iostream>
#include<fstream>
#include<cstdio>
#include<vector>
#include<string>
#include<cstring>
#include<queue>
#include<map>
#include<set>
#include<algorithm>
#include<iomanip>
#include<bitset>
using namespace std;

const int N = 100100;
const int inf = 2000000000;

int n, k, x[N];
char a[100];
int p = 0;

int ter() {
    int r = 0, ver = 1;
    if(a[p] == '-') {
        ++p;
        ver = -1;
    }

    while(a[p] >= '0' && a[p] <= '9')
        r = r * 10 + a[p++] - '0';
    return r * ver;
}

int gr[N], cs[N], cd[N], nrg, nrel[N], val1[N];

int main() {
    int i;
   // freopen("ttt", "r", stdin);

    cin >> n >> k;

    for(i = 1; i <= n; ++i) {
        cin >> a;
        p = 0;
        if(a[0] == '?')
            x[i] = inf;
        else
            x[i] = ter();
    }

    for(i = 0; i < N; ++i) {
        cs[i] = cd[i] = inf;
    }

    for(i = 1; i <= k; ++i) {
        if(x[i] == inf) {
            ++nrg;
            gr[i] = nrg;
            cs[nrg] = -inf;
            nrel[nrg] = 1;
        }
    }

    for(i = k + 1; i <= n; ++i) {
        if(x[i] != inf && x[i - k] != inf) {
            if(x[i] <= x[i - k]) {
                cout << "Incorrect sequence";
                return 0;
            }
            continue;
        }

        if(x[i] == inf && x[i - k] != inf) {
            ++nrg;
            gr[i] = nrg;
            cs[nrg] = x[i - k];
            nrel[nrg] = 1;
        }

        if(x[i] != inf && x[i - k] == inf) {
            cd[gr[i - k]] = x[i];
        }

        if(x[i] == inf && x[i - k] == inf) {
            gr[i] = gr[i - k];
            nrel[gr[i]]++;
        }
    }

    for(i = 1; i <= nrg; ++i) {
        if(1LL * cd[i] - cs[i] - 1 < 1LL * nrel[i]) {
            cout << "Incorrect sequence";
            return 0;
        }

        if(cs[i] >= 0) {
            val1[i] = cs[i] + 1;
            continue;
        }
        if(cd[i] <= 0) {
            val1[i] = cd[i] - nrel[i];
            continue;
        }

        int aa = nrel[i] / 2;

            if(cs[i] < -aa && cd[i] > aa) {
                val1[i] = -aa;
                continue;
            }

            if(cs[i] < -aa)
                val1[i] = cd[i] - nrel[i];

            if(cd[i] > aa)
                val1[i] = cs[i] + 1;

    }

    for(i = 1; i <= n; ++i) {
        if(x[i] == inf)
            x[i] = val1[gr[i]]++;

        cout << x[i] << " ";
    }

    return 0;
}
