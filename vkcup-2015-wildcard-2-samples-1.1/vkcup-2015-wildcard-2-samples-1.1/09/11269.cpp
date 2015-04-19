#define _CRT_SECURE_NO_WARNINGS
#pragma comment(linker, "/stack:16777216")
#include <string>
#include <vector>
#include <map>
#include <list>
#include <iterator>
#include <set>
#include <queue>
#include <iostream>
#include <sstream>
#include <stack>
#include <deque>
#include <cmath>
#include <memory.h>
#include <cstdlib>
#include <cstdio>
#include <cctype>
#include <algorithm>
#include <utility>
#include <time.h>
using namespace std;

#define FOR(i, a, b) for(int i = (a); i < (b); ++i)
#define RFOR(i, b, a) for(int i = (b) - 1; i >= (a); --i)
#define REP(i, N) FOR(i, 0, N)
#define RREP(i, N) RFOR(i, N, 0)
#define FILL(A,value) memset(A,value,sizeof(A))

#define ALL(V) V.begin(), V.end()
#define SZ(V) (int)V.size()
#define PB push_back
#define MP make_pair
#define Pi 3.14159265358979

typedef long long Int;
typedef unsigned long long UInt;
typedef vector <int> VI;
typedef pair <int, int> PII;

const int INF = 1000000000;
const int MAX = 64;
const int MAX2 = 170000;
const int BASE = 1000000000;
const int CNT = MAX2/32+1;

double eps = 1E-7;

int n, m;
int R[MAX];
int C[MAX];
unsigned int A[21][1 << 5][MAX2/32];
int D[1 << 5][1 << 5];
int W[1 << 5];
int P[MAX];
int B[MAX][MAX];

int get(int a, int b, int c)
{
    return (A[a][b][c/32] & (1 << (c%32))) != 0;
}

int main()
{
    //freopen("in.txt", "r", stdin);

    P[0] = 1;
    FOR (i,1,MAX)
        P[i] = P[i-1] * 11;

    cin >> n >> m;
    FOR (i,0,n)
        cin >> R[i];
    FOR (i,0,m)
        cin >> C[i];



    FOR (i,0,(1 << n))
    {
        W[i] = 0;
        FOR (j,0,n)
        {
            if ((i & (1 << j)) != 0)
                if (j == 0 || ((i & (1 << (j-1))) == 0))
                    ++ W[i];
        }
    }
    FOR (i,0,(1 << n))
    {
        FOR (j,0,(1 << n))
        {
            D[i][j] = 0;
            FOR (k,0,n)
            {
                if ((i & (1 << k)) == 0)
                    if ((j & (1 << k)) != 0)
                        D[i][j] += P[k];
            }
        }
    }
    A[0][0][0] = 1;
    FOR (i,0,m)
        FOR (j,0,(1 << n))
        {
            FOR (k,0,(1 << n))
            {
                if (W[k] != C[i])
                    continue;
                int add = D[j][k];
                int pos = add;
                int id = pos/32;
                for (int l = 0; l < CNT; ++l)
                {
                    if (id+1 >= CNT)
                        break;
                    if (A[i][j][l] != 0)
                    {
                        if (pos % 32 == 0)
                        {
                            A[i+1][k][id] |= A[i][j][l];
                        }
                        else
                        {
                            int a = (pos%32);
                            int b = (32-a);
                            A[i+1][k][id] |= (A[i][j][l] << a);
                            A[i+1][k][id+1] |= (A[i][j][l] >> b);
                        }
                    }
                    ++ id;
                    pos += 32;
                }
            }
        }
    int w = 0;
    FOR (i,0,n)
        w += P[i] * R[i];
    int mask = -1;
    FOR (i,0,(1 << n))
        if (get(m, i, w) == 1)
        {
            mask = i;
        }
    int x = m;
    while (x > 0)
    {
        FOR (i,0,n)
            if ((mask & (1 << i)) != 0)
                B[i][x-1] = 1;
        FOR (mask2,0,(1 << n))
        {
            int w2 = (w - D[mask2][mask]);
            if (w2 >= 0)
            {
                if (get(x-1, mask2, w2))
                {
                    mask = mask2;
                    w = w2;
                    -- x;
                    break;
                }
            }
        }
    }
    FOR (i,0,n)
    {
        FOR (j,0,m)
            if (B[i][j])
                cout << '*';
            else
                cout << '.';
        cout << endl;
    }






    return 0;
}
