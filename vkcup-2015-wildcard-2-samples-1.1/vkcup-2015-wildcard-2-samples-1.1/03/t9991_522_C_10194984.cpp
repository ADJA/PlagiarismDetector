#include<iostream>
#include<cstdio>
#include<stack>
#include<queue>
#include<set>
#include<iomanip>
#include<complex>
#include<vector>
#include<map>
#include<algorithm>
#include<cmath>
#include<string>
#include<bitset>
#include<memory.h>
#include<cassert>
#include<ctime>

using namespace std;
bool used[200000];
int number[200000];

int main()
{
    ios_base::sync_with_stdio(0);
    int test;
    int n,m;
    cin>>test;
    for(int t=0;t<test;t++)
    {
        cin>>n>>m;
        for(int i=1;i<=m;i++)
            cin>>number[i];
        for(int i=1;i<=m;i++)
            used[i]=false;
        bool sad = false;
        int cnt1=0;
        int cnt2=0;
        for(int i=0;i<n-1;i++)
        {
            int tmp1,tmp2;
            cin>>tmp1>>tmp2;
            if(tmp2==1)
                sad=true;
            if(sad)
            {
                if(tmp1==0)cnt2++;
                else
                {
                    used[tmp1]=true;
                    number[tmp1]--;
                }
            }
            else
            {
                if(tmp1==0)cnt1++;
                else
                {
                    number[tmp1]--;
                }
            }
        }
            int MIN = 1000000000;
            for(int i=1;i<=m;i++)
                if(!used[i])MIN=min(MIN,number[i]);
            for(int i=1;i<=m;i++)
            {
                if(!used[i])
                {
                    if(number[i]<=cnt1)
                    {
                        cout<<"Y";
                        continue;
                    }
                }
                if(number[i]+MIN<=cnt1+cnt2)
                {
                    cout<<"Y";
                    continue;
                }
                cout<<"N";
            }
        cout<<endl;
    }
}