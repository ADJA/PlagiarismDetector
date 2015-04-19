#include <cstdio>
#include <cstring>
#include <map>
#include <set>
#include <queue>
#include <vector>
#include <stack>
#include <algorithm>
#include <numeric>
#include <iostream>
#include <cassert>
#include <climits>
using namespace std;

#define rep(i, n) for (int i = 0; i < (int)n; ++i)
#define all(a) (a).begin(), (a).end()
#define iter(c) __typeof(c.begin())
#define tr(c, i) for (iter(c) i = c.begin(); i != c.end(); ++i)
#define pb push_back
#define mp make_pair

typedef long long ll;

ll fib[210];

int main() {
  fib[0] = fib[1] = 1;
  for (int i = 2; i <= 200; ++i) fib[i] = fib[i - 1] + fib[i - 2];
  
  string S;
  while (cin >> S) {
    vector<string> ss;
    
    string tmp = "";
    rep (i, S.length()) {
      if (tmp == "" || tmp[tmp.length() - 1] != S[i]) {
	tmp += S[i];
      } else {
	ss.pb(tmp);
	tmp = string() + S[i];
      }
    }
    assert(tmp != "");
    if (!ss.empty() && ss[0][0] != tmp[tmp.length() - 1]) ss[0] = tmp + ss[0];
    else ss.pb(tmp);

    size_t len_sum = 0;
    rep (i, ss.size()) len_sum += ss[i].length();
    assert(len_sum == S.length());
    
    // rep (i, ss.size()) cout << i << ": " << ss[i] << endl; puts("");
    
    ll ans = 1;
    if (ss.size() == 1 && S.length() % 2 == 0) {
      int chain = ss[0].length() / 2;
      ans = fib[chain] + fib[chain - 2];
    } else {
      rep (i, ss.size()) {
	string s = ss[i];
	// cerr << s << endl;
	if (s.length() == 1) continue;
	
	if (s[0] == 'A') {
	  if (s.length() < 3) { ans = 0; continue; }
	  s = s.substr(3);
	  if (s.empty()) continue;
	}

	if (s.length() == 1) continue;
	
	if (s[s.length() - 1] == 'B') {
	  if (s.length() < 3) { ans = 0; continue; }
	  s = s.substr(0, s.length() - 3);
	  if (s.empty()) continue;
	}

	assert(s.length() % 2 == 0);
	int chain = s.length() / 2;
	
	// cerr << s << ": " << fib[chain + 1] << endl;
	
	ans *= fib[chain + 1];
      }
    }

    cout << ans << endl;
  }
  return 0;
}
