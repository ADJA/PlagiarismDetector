#include <cstdio>
#include <iostream>
#include <vector>
#include <map>
#include <list>
#include <queue>
#include <sstream>
#include <cmath>
#include <string>
#include <cstring>
#include <complex>
#include <algorithm>

#define REP(i,N) for (int i = 0; i < (N); ++i)
#define FOR(i,a,b) for (int i = (a); i < (b); ++i)
#define FORD(i,b,a) for (int i = (int)(b) - 1; i >= a; --i)
#define FOREACH(it,c) for (__typeof((c).begin()) it = (c).begin(); it != (c).end(); ++it)

using namespace std;

typedef long long LL;
typedef unsigned long long ULL;
typedef pair<int,int> PII;
typedef complex<int> Point;
#define X real()
#define Y imag(

list<int> adj[5001];
int N;
bool can[5001];
bool visited[5001];

//local
bool isok[5001];

int dfs(int v) {
 
  int moc = 1;
  visited[v] = true;
  vector<int> moce;
  FOREACH(it, adj[v]) {
    if (visited[*it]) continue;
    int t = dfs(*it);
    moce.push_back(t);
    moc += t;
  }
  
  moce.push_back(N - moc);

  REP(i,N) isok[i] = false;
  isok[0] = true;
  FOREACH(jt, moce) {
    int w = *jt;
    FORD(i,N,w) {
      if (isok[i - w]) isok[i] = true;
    }  
  }
  
  REP(i,N) if (isok[i]) {
    can[i] = true;
  }

  return moc;
}

int main() {
  scanf("%d",&N);
  REP(i,N-1) {
    int a, b;
    scanf("%d%d",&a,&b);
    --a,--b;
    adj[a].push_back(b);
    adj[b].push_back(a);
  }
  dfs(0);
  int c = 0;
  FOR(i,1,N-1) if (can[i]) ++c;
  printf("%d\n", c);
  FOR(i,1,N-1) if (can[i]) printf("%d %d\n", i, N-1-i); 
}