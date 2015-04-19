#include<bits/stdc++.h>

using namespace std;

typedef pair<int, int> pii;
typedef long long int LL;
typedef vector<int> VI;

#define sd(x) scanf("%d", &x)
#define MP make_pair
#define PB push_back
#define F first
#define S second
#define INF 1023456789
#define MOD 1000000007
#define D double
#define LD long double

#define N 212345

int getNext(){
    int ret = 0, sign = 1;
    char ch = ' ';
    while((ch < '0' || ch > '9') && ch != '?' && ch != '-'){
        ch = getchar();
    }
    if(ch == '?'){
        return -INF;
    }
    if(ch == '-'){
        sign = -1;
        ch = getchar();
    }
    while(ch >= '0' && ch <= '9'){
        ret *= 10;
        ret += ch - '0';
        ch = getchar();
    }
    return ret * sign;
}

int getFirstVal(int l, int r, int k){
    if(-(k / 2) > l && (k - 1) / 2 < r){
        return -k / 2;
    }
    if(abs(l) > abs(r)){
        return r - k;
    }
    else{
        return l + 1;
    }
}

int a[N];
vector<int> vec;

int main(){
    int n, k, l, j, i, p, s;
    cin>>n>>k;
    for(i = 0; i < n; i++){
        a[i] = getNext();
    }
    for(i = 0; i < k; i++){
        vec.clear();
        vec.PB(-INF);
        for(j = i; j < n; j += k){
            vec.PB(a[j]);
        }
        l = 1;
        s = vec.size();
        vec.PB(INF);
        while(l < s){
            if(vec[l] != -INF){
                l++;
                continue;
            }
            for(j = l + 1; j < s; j++){
                if(vec[j] != -INF){
                    break;
                }
            }
            if(vec[j] - vec[l - 1] - 1 < j - l){
                cout<<"Incorrect sequence"<<endl;
                return 0;
            }
            if(vec[l - 1] >= 0){
                for(p = l; p < j; p++){
                    vec[p] = vec[p - 1] + 1;
                }
            }
            else if(vec[j] <= 0){
                for(p = j - 1; p >= l; p--){
                    vec[p] = vec[p + 1] - 1;
                }
            }
            else{
                vec[l] = getFirstVal(vec[l - 1], vec[j], j - l);
                for(p = l + 1; p < j; p++){
                    vec[p] = vec[p - 1] + 1;
                }
            }
            l = j + 1;
        }
        l = 1;
        for(j = i; j < n; j += k){
            a[j] = vec[l];
            l++;
        }
    }
    for(j = k; j < n; j++){
        if(a[j] <= a[j - k]){
            cout<<"Incorrect sequence"<<endl;
            return 0;
        }
    }
    for(i = 0; i < n; i++){
        printf("%d", a[i]);
        printf(i < n - 1 ? " " : "\n");
    }
    return 0;
}
