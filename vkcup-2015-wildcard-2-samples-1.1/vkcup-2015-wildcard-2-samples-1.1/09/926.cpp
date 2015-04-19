#include <iostream>
#include <cstdio>
#include <algorithm>
#include <cstring>
#include <string>
#include <cctype>
#include <stack>
#include <queue>
#include <list>
#include <vector>
#include <map>
#include <sstream>
#include <cmath>
#include <limits>
#include <bitset>
#include <utility>
#include <iomanip>
#include <set>
#include <fstream>
#include <numeric>
#include <stdexcept>
#include <cassert>

#define INF_MAX 2147483647
#define INF_MIN -2147483647
#define INF_LL 9223372036854775807LL
#define INF 1000000000
#define PI acos(-1.0)
#define EPS 1e-8
#define LL long long
#define mod 1000000007
#define pb push_back
#define mp make_pair
#define f first
#define s second
#define setzero(a) memset(a,0,sizeof(a))
#define setdp(a) memset(a,-1,sizeof(a))

using namespace std;

int n, m;
int cntrow[21];
int cntcol[6];
vector<int> sol;
vector<int> allmasks[6];

bool DP[20][11][11][11][11][11][(1 << 5) + 1];

bool solve(int row, int c1, int c2, int c3, int c4, int c5, int mask)
{
  if(row == m)
  {
    int tmp = c1 + c2 + c3 + c4 + c5;
    if(tmp == 0) return true;
    return false;
  }
  bool &temp = DP[row][c1][c2][c3][c4][c5][mask];
  if(temp) return false;
  temp = true;
  for(int i=0;i<allmasks[cntrow[row]].size();i++)
  {
    int tmp = allmasks[cntrow[row]][i];
    int nc1 = c1;
    int nc2 = c2;
    int nc3 = c3;
    int nc4 = c4;
    int nc5 = c5;
    if((mask & (1 << 0)) == 0 && (tmp & (1 << 0)) != 0)
      nc1--;
    if((mask & (1 << 1)) == 0 && (tmp & (1 << 1)) != 0)
      nc2--;
    if((mask & (1 << 2)) == 0 && (tmp & (1 << 2)) != 0)
      nc3--;
    if((mask & (1 << 3)) == 0 && (tmp & (1 << 3)) != 0)
      nc4--;
    if((mask & (1 << 4)) == 0 && (tmp & (1 << 4)) != 0)
      nc5--;
    if(nc1 < 0 || nc2 < 0 || nc3 < 0 || nc4 < 0 || nc5 < 0) continue;
    if(solve(row + 1, nc1, nc2, nc3, nc4, nc5, tmp))
    {
      sol.pb(tmp);
      return true;
    }
  }
  return false;
}

int main()
{
  ios_base::sync_with_stdio(0);
  //freopen("death.in", "r", stdin);
  //freopen("death.out", "w", stdout);
  cin >> n >> m;
  for(int i=0;i<n;i++)
    cin >> cntcol[i];
  for(int i=0;i<m;i++)
    cin >> cntrow[i];
  for(int i=0;i<(1 << n);i++)
  {
    int cnt = 0;
    for(int j=0;j<n;j++)
    {
      if(j == 0 || ((i & (1 << (j - 1))) == 0))
        if((i & (1 << j)) != 0)
          cnt++;
    }
    allmasks[cnt].pb(i);
  }
  solve(0, cntcol[0], cntcol[1], cntcol[2], cntcol[3], cntcol[4], 0);
  reverse(sol.begin(), sol.end());
  for(int j=0;j<n;j++)
  {
    for(int i=0;i<sol.size();i++)
    {
      if(sol[i] & (1 << j))
        cout << '*';
      else cout << '.';
    }
    cout << "\n";
  }
  return 0;
}
