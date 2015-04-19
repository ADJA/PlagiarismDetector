#pragma comment(linker, "/STACK:256000000")

#include <iostream>
#include <vector>
#include <cstdio>
#include <cmath>
#include <set>
#include <map>
#include <queue>
#include <deque>
#include <algorithm>
#include <cstring>
#include <sstream>
using namespace std;

#define forn(i, n) for (int i = 0; i < int(n); i++)
#define forv(i, v) forn(i, v.size())
#define for1(i, n) for (int i = 1; i <= int(n); i++)

#define pb push_back
#define mp make_pair
#define all(v) v.begin(), v.end() 

#define CIN_FILE "input.txt"
#define COUT_FILE "output.txt"

#define pi 3.14159265358979

typedef long long ll;
typedef long double ld;
typedef pair<int, int> pii;

#define NMAX 105
#define next nxt
#define prev prv

string s;
int n;
int next[NMAX], prev[NMAX];
int num[NMAX];
bool must[NMAX];

ll d[NMAX][2][2];


int main()
{
     

    cin >> s;
    n = (int)s.size();
    s += s[0];

    memset(num, -1, sizeof(num));
    int k = 0;
    forn(i, n)
    {
        if (s[i] == 'B' && s[i + 1] == 'A')
        {
            num[i] = k;
            k++;
        }   
    }

    memset(next, -1, sizeof(next));

    forn(i, n)
    {
        if (s[i] == 'A' && s[i + 1] == 'B')
        {
            if (num[(i - 1 + n) % n] == -1 && num[(i + 1) % n] == -1)
            {
                cout << 0 << endl;
                return 0;
            }
            if (num[(i - 1 + n) % n] == -1) must[num[(i + 1) % n]] = true;
            else
            if (num[(i + 1) % n] == -1) must[num[(i - 1 + n) % n]] = true; 
            else
            {
                next[num[(i - 1 + n) % n]] = num[(i + 1) % n];
                prev[num[(i + 1) % n]] = num[(i - 1 + n) % n];
            }
        }
    }

    if (k == 0)
    {
        cout << 1 << endl;
        return 0;
    }

    d[0][1][1] = 1;
    if (!must[0]) d[0][0][0] = 1;

    for1(i, k - 1)
    {
        forn(f, 2)
        {
            forn(b, 2)
            {
                d[i][f][1] += d[i - 1][f][b];
                if (!must[i] && (b == 1 || prev[i] == -1))
                {
                    d[i][f][0] += d[i - 1][f][b];
                }
            }
        }
    }

    ll ans = 0;
    forn(f, 2)
    {
        forn(b, 2)
        {
            ans += d[k - 1][f][b];
        }
    }
    if (next[k - 1] != -1) ans -= d[k - 1][0][0];

    cout << ans << endl;
    return 0;
}