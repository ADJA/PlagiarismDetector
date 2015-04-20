#include<bits/stdc++.h>

using namespace std;

const int M = 1000000007;

char s[1000005];
int p[1000005];
bool compat[1000005] = {0};
bool mark[1000005] = {0};

int main(){
	int l,m; scanf("%d%d",&l,&m);
	scanf("%s",s+1);
	int n = strlen(s+1);

	p[1] = 0; int j = 0;
	for(int q = 2; q<=n; q++){
		while(j>0&&s[j+1]!=s[q]) j = p[j];
		if(s[j+1]==s[q]) j++;
		p[q] = j;
	}

	j = n;
	while(j!=0){
		compat[j = p[j]] = 1;
	}

	while(m--){
		int x; scanf("%d",&x);
		mark[x] = 1;
	}

	int det = 0;
	long long ans = 1;
	for(int i = 1; i<=l; i++){
		if(mark[i]){
			if(det){
				if(compat[n-(i+n-1-det)]) det = i+n-1;
				else {puts("0"); return 0;}
			}else{
				det = i+n-1;
			}
		}
		if(det<i){
			det = 0;
		}
		if(!det){
			ans = (ans*26)%M;
		}
	}
	cout<<ans<<endl;

	return 0;
}
