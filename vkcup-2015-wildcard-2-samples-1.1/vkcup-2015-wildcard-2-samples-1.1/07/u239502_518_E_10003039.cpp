#include<stdio.h>
#include<iostream>
#include<string>
#include <iomanip>
#include<stack>
#include<set>
#include<vector>
#include<algorithm>
#include <string.h>
#include<map>
using namespace std;
map<long long,int>maxmove;
#define imp 1234567890
double dp[2100][2100];
double p;
double getPerson(int peopleLeft,int timeLeft){
    if(dp[peopleLeft][timeLeft]!=0)
        return dp[peopleLeft][timeLeft];
    if(timeLeft==0||peopleLeft==0)
        return 0;
    if(timeLeft==1)
        return p;

    double p1=getPerson(peopleLeft-1,timeLeft-1);
    double p2=getPerson(peopleLeft,timeLeft-1);
    dp[peopleLeft][timeLeft]=p+(p*p1)+(1-p)*p2;
    return dp[peopleLeft][timeLeft];
}

struct TheGridDivOne{
    int dp(long long val,int moveNum){
        if(moveNum==0)
            return 0;
        int v=maxmove[val];
        if(v!=0)
            return v;
        long long xv=1;
        xv=xv<<32;
        int vUp,vDown,vLeft,vRight,vH,vV;
        vUp=dp(val+1,moveNum-1);
        vDown=dp(val-1,moveNum-1);
        vLeft=dp(val-xv,moveNum-1)-1;
        vRight=1+dp(val+xv,moveNum-1);
        vV=max(vUp,vDown);
        vH=max(vLeft,vRight);
        v=max(vH,vV);
        if(v==0)
            v--;
        maxmove[val]=v;
        return v;
    }
    int find(vector <int> x, vector <int> y, int k){
        long long startingX=1<<30;
        long long startingY=startingX;
        vector<long long>X;
        vector<long long>Y;
        for(int i=0;i<x.size();i++){
            X.push_back(x[i]+startingX);
            Y.push_back(y[i]+startingY);
            long long val=(X[i]<<32)+Y[i];
            maxmove[val]=-1;
        }
        int v=dp((startingX<<32)+startingY,k);
        if(v<0)
            v=0;
        return v;
    }
};
long long nums[100100];
long long getVal(string s){
    long long val=0;
    int start=0;
    if(s[0]=='-')
        start=1;
    for(int i=start;i<s.size();i++){
        val=(val*10)+(s[i]-'0');
    }
    if(start==1)
        val*=-1;
    return val;
}

void replaceVal(long n,long k){
    for(long i=0;i<n;i++){
        if(nums[i]==imp){
            if(i<k){
                long next_imps=1,pos=i+k;
                    while(pos<n&&nums[pos]==imp){
                        next_imps++;
                        pos+=k;
                    }
                long long candidate=0-(next_imps/2);
                if(pos<n)
                    {
                        if(nums[pos]-next_imps<candidate)
                            candidate=nums[pos]-next_imps;
                    }
                    nums[i]=candidate;
                    pos=i+k;
                    while(pos<n&&nums[pos]==imp){
                        nums[pos]=nums[pos-k]+1;
                        pos+=k;
                    }
            }
            else{
                if(nums[i-k]>-2)
                    nums[i]=nums[i-k]+1;
                else{
                    long next_imps=1,pos=i+k;
                    while(pos<n&&nums[pos]==imp){
                        next_imps++;
                        pos+=k;
                    }

                    long long candidate=0-(next_imps/2);
                    if(pos<n)
                    {
                        if(nums[pos]-next_imps<candidate)
                            candidate=nums[pos]-next_imps;
                    }
                    if(candidate>nums[i-k])
                        nums[i]=candidate;
                    else
                        nums[i]=nums[i-k]+1;
                    pos=i+k;
                    while(pos<n&&nums[pos]==imp){
                        nums[pos]=nums[pos-k]+1;
                        pos+=k;
                    }
                }
            }
        }
    }
}
bool isValidSeq(long n,long k){
    for(long i=k;i<n;i++)
    {
        if(nums[i-k]>=nums[i])
            return false;
    }
    return true;
}
int main(void)
{
    long n,m,k,t;

    cin>>n>>k;
    string s;
    for(long i=0;i<n;i++){
        cin>>s;
        if(s[0]!='?')
            nums[i]=getVal(s);
        else{
            nums[i]=imp;
        }
    }
    replaceVal(n,k);
    if(isValidSeq(n,k)){
        for(long i=0;i<n;i++){
            cout<<nums[i]<<" ";
        }
    }
    else
    cout<<"Incorrect sequence"<<endl;

    return 0;
}
