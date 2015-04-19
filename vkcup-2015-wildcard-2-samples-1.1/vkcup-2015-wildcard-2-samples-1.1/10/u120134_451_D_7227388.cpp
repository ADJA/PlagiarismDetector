/*
ID: ashish1610
PROG: D
LANG: C++
*/
#include<bits/stdc++.h>
using namespace std;
#define ll  long long int
int main()
{
    string str;
    cin>>str;
    ll dp[2][2];
    memset(dp,0,sizeof(dp));
    ll even=0,odd=0;
    int len=str.length();
    for(int i=0;i<len;++i)
    {
        dp[str[i]-'a'][(i+1)&1]++;
        even+=dp[str[i]-'a'][!((i+1)&1)];
        odd+=dp[str[i]-'a'][(i+1)&1];
    }
    cout<<even<<" "<<odd<<endl;
    return 0;
}