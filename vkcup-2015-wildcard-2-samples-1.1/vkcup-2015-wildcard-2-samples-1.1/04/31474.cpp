#include <iostream>
#include <sstream>
#include <string>
#include <vector>
#include <queue>
#include <deque>
#include <set>
#include <map>
#include <algorithm>
#include <utility>
#include <cstdio>
#include <cstdlib>
#include <cmath>

using namespace std;

#define REP(i,n) for((i)=0;(i)<(int)(n);(i)++)
#define foreach(c,itr) for(__typeof((c).begin()) itr=(c).begin();itr!=(c).end();itr++)

bool ans[5010];

int N;
vector <int> graph[5010];
vector <int> child[5010];
int sz[5010];
bool dp[5010];

int dfs(int p, int x){
    int ans=1,i;
    
    REP(i,graph[x].size()){
        int y = graph[x][i];
        if(y != p){
            ans += dfs(x,y);
            child[x].push_back(y);
        }
    }
    
    return sz[x] = ans;
}

void add(int x){
    int i;
    if(x == 0) return;
    for(i=N-x;i>=0;i--) if(dp[i]) dp[i+x] = true;
}

void func(int x){
    int i;
    
    REP(i,N+1) dp[i] = false;
    dp[0] = true;
    
    REP(i,child[x].size()) add(sz[child[x][i]]);
    add(N-sz[x]);
    
    REP(i,N+1) if(dp[i]) ans[i] = true;
}

int main(void){
    int i,a,b;
    
    cin >> N;
    REP(i,N-1){
        cin >> a >> b;
        a--; b--;
        graph[a].push_back(b);
        graph[b].push_back(a);
    }
    
    dfs(-1,0);
    REP(i,N) func(i);
    
    int S = N - 1;
    int cnt = 0;
    for(i=1;i<S;i++) if(ans[i]) cnt++;
    
    cout << cnt << endl;
    for(i=1;i<S;i++) if(ans[i]) cout << i << ' ' << S-i << endl;
    
    return 0;
}
