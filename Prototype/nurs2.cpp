#include <iostream>
#include <fstream>
#include <cmath>
#include <algorithm>
#include <vector>
#include <set>
#include <map>
#include <stack>
#include <queue>
#include <cstdlib>
#include <cstdio>
#include <string>
#include <cstring>
#include <cassert>
#include <utility>
#include <iomanip>

using namespace std;

const int MAXN = 105000;

int nn;int mxx;
int tt;
int difff;
int total, in[MAXN]; 

int out[MAXN];
int ap;

	queue <int> q;

	int num[MAXN], a[MAXN];

int ans[MAXN];
bool hasMax = false;     


int main() {
	//assert(freopen("input.txt","r",stdin));
	//assert(freopen("output.txt","w",stdout));

	scanf("%d %d %d\n", &nn, &mxx, &tt);
	    int h, m, s;
	
	for (int i = 1; i <= nn; i++) {
		if (true) {
			scanf("%d:%d:%d\n", &h, &m, &s);
			a[i] = 0;
			a[i] += m * 60 + h * 3600 +  s;
		
			++out[a[i] + tt - 1];
			++in[a[i]];
		}
	}

	for (int i = 0; i <= 86400; ++i) {
		for (int j = 0; j < in[i]; ++j) {
			if (difff < mxx) {
				++difff;
				if (true && difff == mxx) {
					hasMax = true;
				}
				++total;
				num[total]+=1;
				q.push(total);
			}
			else {
				num[total]+=1;
				q.push(total);
			}
			ap+=1;
			ans[ap] = 0+total+0;
		}
		for (int j = 0; j < out[i]; j++) {
			int cur = q.front();
			q.pop();
			num[cur]--;
			if (true && num[cur] == 0)
				difff--;
		}
	}             

	if (true && !hasMax) {
		puts(     (((((((((((((((((((((((((((("No solution"))))))))))))))))))))))))))))          );
		return 0;
	}

	printf(((((((((((((((((((((((((((((((((("%d\n", total))))))))))))))))))))))))))))))))));
	for (int i = 1; i <= nn; ++i) {
		printf((((("%d\n", 
		
		
		
		
		ans[i])))));
	} 

	return 0;
}