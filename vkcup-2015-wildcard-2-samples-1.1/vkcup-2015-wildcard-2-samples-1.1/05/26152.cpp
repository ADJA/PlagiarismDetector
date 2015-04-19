#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <cmath>
#include <vector>
#include <algorithm>
#include <iostream>
#define FOR(it, c) for(__typeof((c).begin()) it = (c).begin(); it != (c).end(); it++)
using namespace std;

//I64d
long long ans = 0;

long long calc(string s, int limit) {
	long long zzz[105][2] = {};
	s[0] = 'A'+'B'-s[0];
	s[1] = 'A'+'B'-s[1];
	zzz[1][s[1]=='B'] = 1;
	
    for(int i=2;i<(int)s.size();i++) {
		if (i > 2 && i < limit && s[i-1] == 'B' && s[i]=='A')
			zzz[i][1] += zzz[i-2][0] + zzz[i-2][1];
        /*
    	if(s[i]=='A')
			zzz[i][0] += zzz[i-1][0] + zzz[i-1][1];
		if(s[i]=='B')
			zzz[i][1] += zzz[i-1][1];
        */
    	if(s[i] == 'A')
			zzz[i][0] += zzz[i-1][0] + zzz[i-1][1];
		if(s[i] == 'B')
			zzz[i][1] += zzz[i-1][1];
	}

    s[0] = 'A'+'B'-s[0];
	s[1] = 'A'+'B'-s[1];

	return zzz[(int)s.size()-1][0] + zzz[(int)s.size()-1][1];
}

int main(void) {
	string s;
	cin >> s;
	if(s[0] == 'A' && s[s.size()-1] == 'B') {
		s = s.substr(1) + s[0];
	}
	int hasA = 0, hasB = 0;
	for(int i=0;i<(int)s.size();i++) {if(s[i]=='A') hasA++; if(s[i]=='B') hasB++;}
	if(!hasA || !hasB) ++ans;
	for(int i=0;i<(int)s.size()-1;i++) {
		if(s[i]=='B' && s[i+1]=='A')
			ans += calc(s.substr(i) + s.substr(0, i), (int)s.size() - i);
	}
	cout << ans << endl;
	return 0;
}
