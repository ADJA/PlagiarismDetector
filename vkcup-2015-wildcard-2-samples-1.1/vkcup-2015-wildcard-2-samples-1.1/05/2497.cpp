#include <stdio.h> 
#include <stdlib.h>
#include <iostream>
#include <set>
#include <map>
#include <string.h>
#include <vector>
#include <queue>
#include <algorithm>
using namespace std;
#define li long long int
#define rep(i, n) for(li (i) = 0; (i) < (n); (i)++)
#define sz(a) ((li)(a).size())
#define bit(n) (1ll << (n))
#define all(a) (a).begin(), (a).end()
#define S second
#define F first



///////////// underscore //////////////////
#define MP make_pair
#define pb push_back
#define popback pop_back
#define builtinpopcountll __builtin_popcountll
#define builtinctz __builtin_ctz
#define LINE __LINE__
#define upperbound upper_bound
#define lowerbound lower_bound
///////////////////////////////////////////////
///////////// vertical bar ////////////////////
#define OR ||
////////////////////////////////////////////////

#define MAX 105
li dp[MAX][2][2][2][2];
string base;

// need to test.
li recur(li pos, li last, li lastflip, li bef, li flip)
{
	if(last && lastflip) cout << "ERROR" << endl;
	if(!bef && flip) cout << "ERROR" << endl;
//	cout << pos << " " << last << lastflip << " " << bef << flip << endl;
	if(pos == sz(base)){
		if( lastflip &&  flip) return 1;
		if(!lastflip && !flip && (last OR !bef)) return 1;
		return 0;
	}
	
	li &res = dp[pos][last][lastflip][bef][flip];
	if(res != -1) return res;
	res = 0; 
	
	if(base[pos] == 'A'){
		if(flip){
			res += recur(pos + 1, last, lastflip, 0, 0);
		}else{
			res += recur(pos + 1, last, lastflip, 1, 0);
		}
	}
	if(base[pos] == 'B'){
		if(flip){
		}else{
			if(bef){
				res += recur(pos + 1, last, lastflip, 1, 1);
			}else{
				res += recur(pos + 1, last, lastflip, 1, 1);
				res += recur(pos + 1, last, lastflip, 0, 0);
			}
		}
	}	
	
/*
	if(bef){
		if(flip){
			if(base[pos] == 'B'){
				res += recur(pos + 1, last, lastflip, 0, 0);
			}
		}else{
			if(base[pos] == 'A'){
				res += recur(pos + 1, last, lastflip, 1, 0);
			}else{
				res += recur(pos + 1, last, lastflip, 1, 1);
			}
		}
	}else{	
		if(base[pos] == 'A'){
			res += recur(pos + 1, last, lastflip, 1, 0);
		}else{
			res += recur(pos + 1, last, lastflip, 1, 1);
			res += recur(pos + 1, last, lastflip, 0, 0);
		}
	}
*/
	return res;
}


li check(li last, li lastflip, li bef, li flip)
{
	if(last && lastflip) return 0;
	if(!bef && flip) return 0;
	if(base[0] == 'A'){
		bool ok = false;
		if(last && bef) ok = true;
		if(!last && lastflip) ok = true;
		if(!ok) return 0;
	}
	if(base[0] == 'B'){
		bool ok = false;
		if(last && !bef) ok = true;
		if(!last && !lastflip) ok = true;
		if(!ok) return 0;
	}
	if(base[1] == 'A'){
		bool ok = false;
		if(bef && !flip) ok = true;
		if(!bef && last) ok = true;
		if(!ok) return 0;
	}
	if(base[1] == 'B'){
		bool ok = false;
		if(bef && flip) ok = true;
		if(!bef && !last) ok = true;
		if(!ok) return 0;
	}
	
//	cout << last << " " << lastflip << " " << bef << " " << flip << endl;
	return recur(2, last, lastflip, bef, flip);
}

// li recur(li pos, li last, li lastflip, li bef, li flip)
int main()
{
	cin >> base;
	li res = 0;
	memset(dp, -1, sizeof(dp));
	
	rep(last, 2)rep(lastflip, 2)rep(bef, 2)rep(flip, 2){
		res += check(last, lastflip, bef, flip);
//		cout << res << " * " << last << " " << lastflip << " " << bef << " " << flip << endl;
	}
	
	cout << res << endl;
}
