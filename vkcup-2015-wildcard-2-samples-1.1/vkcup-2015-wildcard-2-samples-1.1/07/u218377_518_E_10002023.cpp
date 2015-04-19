#include<stdio.h>
#include<string.h>
#define M 15
#define MAX 100200 
#define INF 1010000000
#define fi first
#include<vector>
#define se second
#include<algorithm>
using namespace std;
typedef pair<int,int> ii;
vector<ii> res;
vector<int> curr;
char s[M];
int a[MAX];
bool is_quest[MAX];
int n,k;
bool wrong = false;
int abs(int n){
    if( n >= 0 ) return n;
    return -n;
}
bool cmp(int a,int b){
    return (abs(a) < abs(b));
}
int cal(){
    int n = strlen(s);
    int x = 0;
    int start = 0;
    if(s[0] == '-') start = 1;
    for(int i = start ; i < n ; i++)
        x = (x*10 + s[i] - 48);
    if(start == 0) return x;
    return -x;
}
void solve(int pos){
    res.clear();
    res.push_back(ii(pos - k,-INF));
    for(int i = pos ; i <= n ; i += k)
        if(!is_quest[i]) res.push_back(ii(i,a[i]));
    for(int i = pos ; i <= n ; i+=k)
        if(i + k > n) res.push_back(ii(i + k,INF));
    for(int i = 0 ; i < res.size() - 1 ; i++){
        if(res[i].se > res[i+1].se ){
            wrong = true;
            return ;
        }
        if(res[i+1].se - res[i].se  < (res[i+1].fi - res[i].fi)/k){
            wrong = true;
            return ;
        }
        if(res[i].fi + k == res[i+1].fi) continue;
        if(res[i + 1].se <= 0){
            int tmp = res[i+1].se;
            for(int j = res[i+1].fi - k ; j > res[i].fi ; j-=k){
                tmp--;
                a[j] = tmp;
            }
        }   
        if(res[i].se >= 0){
            int tmp = res[i].se;
            for(int j = res[i].fi + k ; j < res[i+1].fi ; j+=k){
                tmp++;
                a[j] = tmp;
            }
        }   
        if(res[i].se < 0 && res[i+1].se > 0){
            curr.clear();
            curr.push_back(0);
            int x = (res[i+1].fi - res[i].fi)/k;
            for(int j = 1 ; j < min(res[i+1].se,x + 1) ; j++) curr.push_back(j);
            for(int j = -1 ; j > max(-(x + 1),res[i].se) ; j--) curr.push_back(j);
            sort(curr.begin(),curr.end(),cmp);
            while( curr.size() > x ) curr.pop_back();
            sort(curr.begin(),curr.end());
            int tmp = 0;
            for(int j = res[i].fi + k ; j < res[i+1].fi ; j+=k){
                a[j] = curr[tmp];
                tmp++;
            }
        }
    }
}
int main(){
//  freopen("test.inp","r",stdin);
    scanf("%d %d",&n,&k);
    for(int i = 1 ; i <= n ; i++){
        scanf("%s",&s);
        if(s[0] == '?') is_quest[i] = true;
        else a[i] = cal();
    }
    for(int i = 1 ; i <= k ; i++){
        solve(i);
        if(wrong){
            printf("Incorrect sequence");
            return 0;
        }
    }
    for(int i = 1 ; i <= n ; i++)   printf("%d ",a[i]);
}