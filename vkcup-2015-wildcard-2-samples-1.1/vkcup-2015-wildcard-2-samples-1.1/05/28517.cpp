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

typedef long long ll;
ll fib[110];

ll cycle(int N){
    return fib[N/2-1] + fib[N/2+1];
}

ll chain(char start, int N){
    if(start == 'A'){
        if(N%2 == 0) return fib[N/2-1];
        return fib[N/2+1];
    }
    if(N%2 == 0) return fib[N/2+2];
    return fib[N/2+1];
}

int main(void){
    int i;
    
    fib[0] = 0;
    fib[1] = 1;
    for(i=2;i<110;i++) fib[i] = fib[i-1] + fib[i-2];
    
    string s;
    cin >> s;
    int N = s.length();
    
    vector <int> v;
    REP(i,N) if(s[i] == s[(i-1+N)%N]) v.push_back(i);
    
    if(v.empty()){
        cout << cycle(N) << endl;
        return 0;
    }
    
    int tmp = v[0];
    v.push_back(tmp+N);
    s = s + s;
    
    int K = v.size() - 1;
    ll ans = 1;
    REP(i,K) ans *= chain(s[v[i]], v[i+1] - v[i]);

    cout << ans << endl;    
    
    return 0;
}
