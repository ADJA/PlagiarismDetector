#include <bits/stdc++.h>
using namespace std;
#define DBG(x) cout << #x << " = " << x << endl;
/*
Compile:
    -Wall -Wextra -pedantic -std=c++11 -O2 -Wshadow -Wformat=2 -Wfloat-equal -Wconversion -Wlogical-op -Wcast-qual -Wcast-align -fwhole-program -D_GLIBCXX_DEBUG -D_GLIBCXX_DEBUG_PEDANTIC -lmcheck -fsanitize=address 

Check for memory usage:
    valgrind --tool=massif
 */


vector<int> masks[5];
int row[6], col[22];
int n, m;

int cur[22];

long long zob[22][33];

void init()
{
    random_device rnd;
    mt19937_64 g;
    g.seed(rnd());

    for(int i = 0; i < 22; i++)
        for(int j = 0; j < 33; j++)
            zob[i][j] = g();
}

unordered_set<long long> was;

void go(int placed=0, int pmask=0)
{
//    cout << placed << ", p= " << pmask << endl;
    if(placed == m) {
        for(int i = 0; i < n; i++)
            if(row[i])
                return;
        for(int i = 0; i < n; i++) {
            for(int j = 0; j < m; j++) {
                if(cur[j] & (1 << i))
                    cout << "*";
                else
                    cout << ".";
            }
            cout << "\n";
        }
        exit(0);
    } else {
        long long hs = 0;
        for(int i = 0; i < n; i++)
            hs ^= zob[i][row[i]];
        hs ^= zob[10][placed];
        if(was.count(hs))
            return;
        for(const auto &mm: masks[col[placed]]) {
            bool good = true;
            for(int i = 0; i < n; i++) {
                if((mm & (1 << i)) and not(pmask & (1 << i)))
                    row[i]--;
                if(m - placed - 1 < row[i] * 2 - ((mm & (1 << i)) == 0)) {
                    good = false;
                }
            }
//            cout << placed << " " << mm  << " " << good<< endl;
            cur[placed] = mm;
            if(good)
                go(placed + 1, mm);
            for(int i = 0; i < n; i++) {
                if((mm & (1 << i)) and not(pmask & (1 << i)))
                    row[i]++;
            }
        }
        was.insert(hs);
    }
}

int main()
{
    init();
    cin >> n >> m;
    for(int i = 0; i < (1 << n); i++) {
        int val = 0;
        int last = 0;
        for(int j = 0; j < n; j++) {
            int tt = ((1 << j) & i) > 0;
            if(tt == 1 and last == 0)
                val++;
            last = tt;
        }
        masks[val].push_back(i);
    }
    for(int i = 0; i < n; i++)
        cin >> row[i];
    for(int i = 0; i < m; i++)
        cin >> col[i];

    go();
    return 0;
}
