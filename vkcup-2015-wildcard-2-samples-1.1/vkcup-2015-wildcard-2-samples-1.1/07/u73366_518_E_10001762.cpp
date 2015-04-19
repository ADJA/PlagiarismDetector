#include<cstdio>
#include<fstream>
#include<iostream>
#include<iomanip>
#include<algorithm>
#include<vector>
#include<bitset>
#include<deque>
#include<queue>
#include<set>
#include<map>
#include<cmath>
#include<cstring>
#include<ctime>
#include<cstdlib>
#include<unordered_map>

#define ll long long
#define pb push_back
#define mp make_pair
#define fi first
#define se second
#define pii pair<int,int>
#define pll pair<ll,ll>

using namespace std;

const int nmax = 100005;
const int inf = 1 << 30;

int n, k, i, m, j, nr, cnt, mlc, poz1, poz2, poz, A, B, a[nmax];
string s;

vector<int> v[nmax];
bitset<nmax> viz;

int main()
{
    cin.sync_with_stdio(false);

    cin >> n >> k;

    for(i = 1; i <= n; i++)
    {
        cin >> s;

        if(s[0] == '?') a[i] = inf;
        else if(s[0] == '-')
        {
            m = s.size();
            nr = 0;
            for(j = 1; j < m; j++) nr = nr * 10 + s[j] - '0';
            nr *= -1;
            a[i] = nr;
        }
        else
        {
            m = s.size();
            nr = 0;
            for(j = 0; j < m; j++) nr = nr * 10 + s[j] - '0';
            a[i] = nr;
        }
    }

    for(i = 1; i <= n; i++)
        if(a[i] == inf)
            if(!viz[i])
            {
                viz[i] = 1;
                cnt++;

                mlc = i - k;
                if(mlc >= 1) v[cnt].pb(mlc);

                v[cnt].pb(i);

                for(j = i + k; j <= n; j += k)
                {
                    v[cnt].pb(j);
                    viz[j] = 1;
                    if(a[j] != inf) break;
                }
            }

    for(i = 1; i <= cnt; i++)
    {
        m = v[i].size();
        A = a[v[i][0]];
        B = a[v[i][m - 1]];

        if(A == inf && B == inf)
        {
            a[v[i][m / 2]] = 0;

            mlc = 0;
            for(j = m / 2 - 1; j >= 0; j--)
                a[v[i][j]] = --mlc;

            mlc = 0;
            for(j = m / 2 + 1; j < m; j++)
                a[v[i][j]] = ++mlc;
        }
        else if(A == inf && B != inf)
        {
            if(B <= 1)
            {
                mlc = B;
                for(j = m - 2; j >= 0; j--)
                    a[v[i][j]] = --mlc;
            }
            else
            {
                poz1 = (m - 1) / 2;
                poz2 = m - B - 1;

                if(poz2 <= poz1) poz = poz1;
                else poz = poz2;

                a[v[i][poz]] = 0;
                mlc = 0;
                for(j = poz - 1; j >= 0; j--)
                    a[v[i][j]] = --mlc;

                mlc = 0;
                for(j = poz + 1; j < m - 1; j++)
                    a[v[i][j]] = ++mlc;
            }
        }
        else if(A != inf && B == inf)
        {
            if(A >= -1)
            {
                mlc = A;
                for(j = 1; j < m; j++)
                    a[v[i][j]] = ++mlc;
            }
            else
            {
                poz1 = m / 2;
                poz2 = -A;

                if(poz2 >= poz1) poz = poz1;
                else poz = poz2;

                a[v[i][poz]] = 0;
                mlc = 0;
                for(j = poz - 1; j > 0; j--)
                    a[v[i][j]] = --mlc;

                mlc = 0;
                for(j = poz + 1; j < m; j++)
                    a[v[i][j]] = ++mlc;
            }
        }
        else
        {
            mlc = B - A - 1;

            if(m - 2 > mlc)
            {
                cout << "Incorrect sequence";
                return 0;
            }

            if(A >= -1)
            {
                mlc = A;
                for(j = 1; j < m - 1; j++)
                    a[v[i][j]] = ++mlc;
            }
            else if(B <= 1)
            {
                mlc = B;
                for(j = m - 2; j > 0; j--)
                    a[v[i][j]] = --mlc;
            }
            else
            {
                poz1 = m / 2;
                poz2 = -A;

                if(poz2 >= poz1)
                {
                    poz1 = (m - 1) / 2;
                    poz2 = m - B - 1;

                    if(poz2 <= poz1) poz = poz1;
                    else poz = poz2;
                }
                else poz = poz2;

                a[v[i][poz]] = 0;
                mlc = 0;
                for(j = poz - 1; j > 0; j--)
                    a[v[i][j]] = --mlc;

                mlc = 0;
                for(j = poz + 1; j < m - 1; j++)
                    a[v[i][j]] = ++mlc;
            }
        }
    }

    viz = 0;
    for(i = 1; i <= n; i++)
        if(!viz[i])
        {
            viz[i] = 1;
            A = a[i];
            for(j = i + k; j <= n; j += k)
            {
                viz[j] = 1;
                if(a[j] <= A)
                {
                    cout << "Incorrect sequence";
                    return 0;
                }
                else A = a[j];
            }
        }

    for(i = 1; i <= n; i++)
        cout << a[i] << " ";

    return 0;
}
