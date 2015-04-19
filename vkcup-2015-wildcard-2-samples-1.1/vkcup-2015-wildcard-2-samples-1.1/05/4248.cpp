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

char S[101];
bool AB[101];
bool BA[101];

long long DP[101][2][3];
bool need[101];

bool next[101];
int value[101];
const int MAYBE = 0;
const int YES = 1;
const int NO = 2;

long long path(int N) {
  long long DP[N][2];
  DP[0][0] = DP[0][1] = 1;
  FOR(i,1,N) {
    DP[i][1] = DP[i-1][0] + DP[i-1][1];
    DP[i][0] = DP[i-1][1];
  }
  return DP[N-1][0] + DP[N-1][1];
}

bool check(int& a, int& b, bool& n) {
  if (!n) return true;
  if (a == NO && b == NO) return false;
  if (a == YES || b == YES) {
    n = false;
    return true;
  }
  if (a == NO) {
    b = YES;
    n = false;
    return true;
  }
  if (b == NO) {
    a = YES;
    n = false;
    return true;
  }  
  return true;
}

long long cycle(int N) {
  long long DP[N][2];
  DP[0][0] = 1; DP[0][1] = 0;
  FOR(i,1,N) {
    DP[i][1] = DP[i-1][0] + DP[i-1][1];
    DP[i][0] = DP[i-1][1];
  }
  return path(N) - DP[N-1][0];  
}

int main() {
  scanf("%s",S);
  int N = strlen(S);
  S[N] = S[0];
  REP(i,N) {
    AB[i] = (S[i] == 'A' && S[i+1] == 'B');
    BA[i] = (S[i] == 'B' && S[i+1] == 'A');
  }
  
  int c = 0;
  REP(i,N) if (AB[i]) ++c;
  
  if (2 * c == N) {
    cout << cycle(c) << endl;
  } else {
    REP(i,N) {
      if (AB[(i+1)%N]) next[i] = true;
      value[i] = BA[i] ? MAYBE : NO;
    }
    REP(w,2*N) {
      REP(i,N) {
          if (!check(value[i], value[(i+2)%N], next[i])) goto fail;
      }
    }
    long long result = 1;
    REP(i,N) {
      if (value[i] == MAYBE && !next[(i+N-2)%N] && !next[i]) result <<= 1;
      else if (next[i] && !next[(i+N-2)%N]) {
        int p = 0;
        int t = i;
        while (next[t]) {
          ++p;
          t = (t+2) % N;
        }
        result *= path(p+1);
      }
    }
    cout << result << endl;    
  }
      
  return 0;
  fail:
    printf("0\n");
  return 0;
}