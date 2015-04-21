#include <bits/stdc++.h>

using namespace std;

typedef pair<int, int> pie;

#define MP make_pair
#define PB push_back
#define L first
#define R second

long long a[2], b[2];

int main(){
	ios_base::sync_with_stdio(false);
	string s;
	cin>>s;
	long long fard = s.size(), zoj = 0;
	if(s[0] == 'a')
		a[0] = 1;
	else
		b[0] = 1;
	for(int i=1;i<s.size();i++){
		if(s[i] == 'b')
			fard += b[1], zoj += b[0];
		else
			fard += a[1], zoj += a[0];
		swap(b[0], b[1]);
		swap(a[0], a[1]);
		if(s[i] == 'b')
			b[0]++;
		else
			a[0]++;
	}
	cout<<zoj<<" "<<fard<<endl;
}
