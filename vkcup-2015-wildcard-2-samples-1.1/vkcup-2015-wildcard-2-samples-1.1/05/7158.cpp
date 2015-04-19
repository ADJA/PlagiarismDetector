#include<iostream>
#include<algorithm>
#include<cstdio>
#include<complex>
#include<vector>
#include<set>
#include<map>
#include<cmath>
#include<queue>
#include<string>
#include<cstdlib>
#include<memory.h>
#include<ctime>

using namespace std;

typedef long long ll;
typedef pair<int,int>	pii;
typedef pair<double,double>	pdd;
typedef vector<int> vi;
typedef vector<double> vd;
typedef pair<ll,ll> pl;

#define FOR(i,a,b)		for(int i=(a);i<(b);i++)
#define forn(i,n)		FOR(i,0,n)
#define SORT(v)			sort((v).begin(),(v).end())
#define pb				push_back

string s;
int n;

ll d[2][2][2][2][222];

int main(){
	cin>>s;
	n=s.size();
	d[0][0][0][0][1] = 1;
	d[0][1][1][1][1] = 1;
	d[1][0][0][0][1] = 1;
	d[1][1][0][0][1] = 1;

	ll temp;
	FOR(i,1,n-1)
    forn(s1,2)
    forn(s2,2)
    forn(c1,2)
    forn(c2,2)
    if(temp=d[s1][s2][c1][c2][i]){
		//cout<<s1<<' '<<s2<<' '<<c1<<' '<<c2<<' '<<i<<" -> "<<temp<<endl;
		forn(ns,2){
			int nc = 0, pc=c2;
    	//else cout<<"not "<<temp<<endl;
			if(s2==0 && ns==1)pc=1,nc=1;
			if((s2^pc)==s[i]-'A')
				d[s1][ns][c1][nc][i+1] += temp;
		}
	}

	ll res = 0;

    	//else cout<<"not "<<temp<<endl;
	forn(s1,2)
    	//else cout<<"not "<<temp<<endl;
    forn(s2,2)
    	//else cout<<"not "<<temp<<endl;
    forn(c1,2)
    forn(c2,2)
    if(temp=d[s1][s2][c1][c2][n-1]){
		if(s2 == 0 && s1 == 1) c1 = c2 = 1;
    	//else cout<<"not "<<temp<<endl;
		int t1 = s1 ^ c1;
    	//else cout<<"not "<<temp<<endl;
		int t2 = s2 ^ c2;
    	//else cout<<"not "<<temp<<endl;
		if(s[0]-'A'==t1 && s[n-1]-'A'==t2)
    	//else cout<<"not "<<temp<<endl;
        res+= temp;
		//else cout<<"not "<<temp<<endl;
	}
	cout<<res<<endl;


	
#ifdef LocalHost
	printf("TIME: %.3lf\n",double(clock())/CLOCKS_PER_SEC);
#endif
	return 0;
}