#pragma comment(linker, "/STACK:256000000")
#define _CRT_SECURE_NO_WARNINGS

#include <iostream>
#include <vector>
#include <string>
#include <map>
#include <set>
#include <queue>
#include <algorithm>
#include <cmath>
#include <cassert>
#include <sstream>

using namespace std;

#define forn(i, n) for (int i = 0; i < int(n); i++)
#define for1(i, n) for (int i = 1; i <= int(n); i++)
#define forv(i, v) forn(i, v.size())

#define all(x) x.begin(), x.end()
#define pb push_back
#define mp make_pair

#define CIN_FILE "input.txt"
#define COUT_FILE "output.txt"

typedef long double ld;
typedef long long ll;
typedef pair<int, int> pii;

const int NMAX = 200005;
const ll INF = 2000000009;

int n, k;
ll a[NMAX];
bool q[NMAX];
ll b[NMAX];
    
int main()
{

    cin >> n >> k;
    forn(i, n)
    {
        string s; cin >> s;
        if (s == "?") q[i] = true;
        else 
        {   
            istringstream sin(s);
            sin >> a[i];
        }

    } 

    forn(i, k)
    {
        ll lf = -INF;
        int l = -k + i;
        while (l < n)
        {
            int r = l + k;
            while (r < n && q[r]) r += k;
            ll rg;
            if (r >= n) rg = INF; else rg = a[r];

            if (rg - lf < (r - l) / k)
            {
                cout << "Incorrect sequence\n";
                return 0;
            }

            if (lf >= 0)
            {
                for (int i = l + k; i < r; i += k)
                    a[i] = a[i - k] + 1;
            }
            else if (rg <= 0)
            {
                for (int i = r - k; i > l; i -= k)
                    a[i] = a[i + k] - 1;
            }
            else
            {
                int cnt = (r - l - k) / k;
                int L = -cnt/2;
                int R = (cnt-1)/2;
                if (L <= lf)
                {
                    L = lf + 1;
                    R = L + cnt - 1;
                }
                if (R >= rg)
                {
                    R = rg - 1;
                    L = R - (cnt - 1);
                }

                for (int i = l + k; i < r; i += k)
                {
                    a[i] = L;
                    L++;
                }
            }
            l = r;
            if (l < n) lf = a[l];

        }   
    }

    forn(i, n)
    {
        if (i) cout << " ";
        cout << a[i];
    }
    cout << endl;
    return 0;
}