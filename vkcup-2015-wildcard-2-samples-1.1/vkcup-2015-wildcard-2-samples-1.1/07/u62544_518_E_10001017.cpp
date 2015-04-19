/*
    Nimesh Ghelani (nims11)
*/
#include <bits/stdc++.h>
#define in_T int t;for(scanf("%d",&t);t--;)
#define in_I(a) scanf("%d",&a)
#define in_F(a) scanf("%lf",&a)
#define in_L(a) scanf("%lld",&a)
#define in_S(a) scanf("%s",a)
#define newline printf("\n")
#define BE(a) a.begin(), a.end()

using namespace std;
long long arr[100010];
const long long inf = 1e15;
int main()
{
    int n, k;
    char s[20];
    in_I(n);
    in_I(k);
    vector<long long> seriesN, seriesL, seriesR, seriesStart;
    for(int i = 0;i<n;i++){
        in_S(s);
        if(s[0] == '?')
            arr[i] = inf;
        else
            arr[i] = atoi(s);
    }
    for(int i = 0;i<k;i++){
        long long prev = -inf, next;
        long long curN = 0, curL = -inf, curR = 2*inf, start;
        for(int j = i;j<n;j+=k){
            if(arr[j] != inf && prev != inf && arr[j]<=prev){
                printf("Incorrect sequence\n");
                return 0;
            }
            if(arr[j] == inf){
                if(curN == 0)
                    curL = prev, start = j;
                curN++;
            }else if(curN){
                seriesN.push_back(curN);
                seriesL.push_back(curL);
                seriesR.push_back(arr[j]);
                seriesStart.push_back(start);
                curN = 0;
            }
            prev = arr[j];
        }
        if(curN){
            seriesN.push_back(curN);
            seriesL.push_back(curL);
            seriesR.push_back(2*inf);
            seriesStart.push_back(start);
        }
    }
    long long N = n;
    for(int i = 0;i<seriesN.size();i++){
        long long n = seriesN[i], l = seriesL[i], r = seriesR[i], idx = seriesStart[i];
        // cout<<n<<" "<<l<<" "<<r<<" "<<idx<<endl;
        if(r-l-1 < n){
            printf("Incorrect sequence\n");
            return 0;
        }
        if(r <= 0){
            for(int i = idx, j = n;j>0;i+=k,j--)
                arr[i] = r-j;
        }else if(l >= 0){
            for(int  i = idx,j=0;j<n;i+=k,j++)
                arr[i] = l+j+1;
        }else{
            long long cur = max(-n/2, l+1);
            if(cur + n - 1 >= r)
                cur = r-n;
            for(int i = idx,j=0;j<n;i+=k,j++)
                arr[i] = cur+j;
        }
    }
    for(int i = 0;i<n;i++)
        printf("%lld ", arr[i]);
    printf("\n");
}