//ITNOG
#include <bits/stdc++.h>

using namespace std;

#define int long long
#define rep(i, s, e) for(int i = s; i < e; i ++)

typedef long double ld;

const int maxN = 100*1000 + 5;
const int mod = 1000*1000*1000 + 7;
int a[maxN], mark[maxN];

int toI(string s)
{
    int p = 0;
    
    int fl = 0;
    if(s[0] == '-')
    {
	  fl = 1;
	  s = s.substr(1);
    }
    
    rep(i, 0, s.size()) p *= 10, p += s[i] - '0';

    if(fl) p *= -1;
    return p;
}

int n, k;
int mar[maxN];

vector<pair<int, int> > b[maxN];


void bad() { cout << "Incorrect sequence" << endl; }

main()
{
    ios::sync_with_stdio(0); cin.tie();
    cin >> n >> k;


    rep(i, 0, n)
    {
	  string s; cin >> s;

	  if(s[0] == '?') mark[i] = 1;
	  else a[i] = toI(s);

	  b[i % k].push_back(make_pair(a[i], i));
	  
    }
    
    rep(i, 0, k) b[i].push_back(make_pair(2 * mod, n));
   
    
    rep(i, 0, k)
    {
	  int mx = -2 * mod; int ind = -1;

	  rep(j, 0, b[i].size())
	  {
		int ps = b[i][j].second, val = b[i][j].first;

//		cout << j << ' ' << mx << endl;
		
		if(mark[ps] == 0 && val <= mx + j - ind - 1) { bad(); return 0; }

		if(mark[ps]) continue;

		if(mx >= 0)
		    rep(k, ind + 1, j) a[b[i][k].second] = mx + k - ind;

		if(val <= 0) 
		    rep(k, ind + 1, j) a[b[i][k].second] = val - (j - k); 
		

		if(mx < 0 && val > 0)
		{
		    int te = j - ind - 1;

		    if(val <= te / 2)
		    {
			  int tmp = j - 1; int z = val - 1;
			  while(tmp > ind)
			  {
				a[b[i][tmp].second] = z; 
				tmp --; z --;
			  }
		    }
		    else if(mx >= -te / 2)
		    {
			  int tmp = ind + 1; mx ++;

			  while(tmp < j)
			  {
				a[b[i][tmp].second] = mx;
				tmp ++; mx ++;
			  }
		    }
		    else
		    {
			  int tmp = ind + 1; int z = -te / 2;

			  while(tmp < j)
			  {
				a[b[i][tmp].second] = z;
				tmp ++; z ++;
			  }
		    }
		}

		mx = val;
		ind = j;
	  }
    }
    

    rep(i, 0, n) cout << a[i] << ' '; cout << endl;

    return 0;
}
