#include <iostream>
#include <stdio.h>
#include <vector>
#include <set>
#include <map>
#include <queue>
#include <stack>
#include <string>
#include <string.h>
#include <cmath>
#include <memory.h>
#include <algorithm>
using namespace std;
typedef long long ll;
int R, C, row[5], col[20];
vector<int> seg[6];
unsigned short vis[20][4084101];
char sol[5][21];
bool calc(char i, int msk){
    int s = 0, h = 0;
    for (int j = 0; j < R; ++j){
        if (row[j] < 0)
            return false;
        s += row[j];
        h = h * 21 + row[j];
    }
    if (i == C)
        return s == 0;
    if ((vis[i][h] >> msk) & 1)
        return false;
    vis[i][h] |= 1 << msk;
    for (int j = 0; j < seg[col[i]].size(); ++j){
        for (int k = 0; k < R; ++k){
            if ((seg[col[i]][j] >> k) & 1){
                if (i == 0 || !((seg[col[i - 1]][msk] >> k) & 1))
                    row[k] -= 1;
            }
        }
        if (calc(i + 1, j)){
            for (int k = 0; k < R; ++k)
                sol[k][i] = (seg[col[i]][j] >> k) & 1 ? '*' : '.';
            return true;
        }
        for (int k = 0; k < R; ++k){
            if ((seg[col[i]][j] >> k) & 1){
                if (i == 0 || !((seg[col[i - 1]][msk] >> k) & 1))
                    row[k] += 1;
            }
        }
    }
    return false;
}
int main()
{
    cin >> R >> C;
    for (int i = 0; i < R; ++i)
        cin >> row[i];
    for (int i = 0; i < C; ++i)
        cin >> col[i];
    for (int i = 0; i < (1 << R); ++i){
        int c = i & 1;
        for (int j = 1; j < R;++j)
        if (((i >> j) & 1) && !((i >> (j - 1)) & 1))
            ++c;
        seg[c].push_back(i);
    }
    calc(0, 0);
    for (int i = 0; i < R; ++i)
        puts(sol[i]);
    return 0;
}