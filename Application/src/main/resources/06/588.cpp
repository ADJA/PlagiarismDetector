/*
User:JeffCsoul
Time:
No.:
Everything will be better.
*/
#include <cstdio>
#include <iostream>
#include <cstring>
#include <string>
#include <map>
#include <vector>
#include <algorithm>
#include <cstdlib>

using namespace std;

#define rep(a,b,c) for(int a=b;a<=c;++a)
#define per(a,b,c) for(int a=b;a>=c;--a)
#define PII pair<int,int>
#define max(a,b) (((a)>(b))?(a):(b))
#define min(a,b) (((a)<(b))?(a):(b))
#define pb push_back
#define mp make_pair

typedef long long ll;

int n,q,ans;
ll a[2222222],k;
ll sum[2222222];
PII s[2222222];

int main(){
	scanf("%d%d",&n,&q);
	rep(i,1,n)	scanf("%d",&a[i]);
	rep(i,1,n)	a[i+n]=a[i];
	rep(vv,1,q){
		scanf("%d",&k);
		ll cur=0;
		int fb=0,r=0,lt=1,ed,md;
		rep(i,1,n){
			if	(cur+a[i]>k){
				s[++r]=mp(lt,i-1);
				sum[r]=cur;
				cur=a[i];lt=i;
			}
			else	cur+=a[i];
		}
		if	(cur){
			s[++r]=mp(lt,n);
			sum[r]=cur;
		}
		ans=r;
		ed=s[1].second;
		rep(j,1,ed){
			sum[1]-=a[j];
			s[1].first++;
			int i=1;
			do{
				if	(s[i].second==n+j-1)	break;
				md=0;
				while	(sum[i]+a[s[i].second+1]<=k){
					s[i].second++;
					sum[i]+=a[s[i].second];
					s[i+1].first++;
					sum[i+1]-=a[s[i].second];
					if	(s[i].second==n+j-1)	break;
					md=1;
				}
				if	(!md)	break;
				i++;
			}while	(1);	
			while	(sum[r]==0)	r--;
			if	(sum[r]+a[j]<=k){
				sum[r]+=a[j];
				s[r].second++;
			}
			else{
				r++;
				s[r].first=s[r].second=n+j;
				sum[r]=a[j];
			}
			ans=min(ans,r);
		}
		cout <<ans <<endl;
	}
}

