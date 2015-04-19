#include <vector>
#include <list>
#include <map>
#include <math.h>
#include <cmath>
#include <set>
#include <queue>
#include <deque>
#include <string>
#include <stack>
#include <bitset>
#include <algorithm>
#include <functional>
#include <numeric>
#include <utility>
#include <string.h>
#include <sstream>
#include <iostream>
#include <iomanip>
#include <cstdio>
#include <cstdlib>
#include <ctime>

using namespace std;

int n,m,arr[6][21],tens[5]={1,11,11*11,11*11*11,11*11*11*11};
int col[21],row[6];
//char vis[5][20][32][161060];
char dp[20][32][161060];
char vis[20][32][161060];
bool flag;
bool bt(short i,short j,short mask,int tot,int cl)
{
    if(j==m){
            if(tot==0&&!flag)
            {
                flag=1;
                for(int f=0;f<n;f++)
                {
                    for(int f1=0;f1<m;f1++)
                    {
                        if(arr[f][f1])
                            cout<<"*";
                        else
                            cout<<".";
                    }
                    cout<<endl;
                }
                return 1;
            }
            return 0;
    }
    if(i==n)
    {
        if(cl)
            return 0;
        return bt(0,j+1,mask,tot,col[j+1]);
    }
    if((vis[j][mask][tot]&(1<<i))!=0)
        return (dp[j][mask][tot]&(1<<i));
    vis[j][mask][tot]+=(1<<i);
    int temp=cl;
    if(i==0||(mask&(1<<(i-1)))==0)
        temp--;
    if((mask&(1<<i))!=0)
    {
        arr[i][j]=1;
        if(bt(i+1,j,mask,tot,temp))
            return 1,(dp[j][mask][tot]&=(1<<i));
        arr[i][j]=0;
        if(bt(i+1,j,mask&(~(1<<i)),tot,cl))
            return 1,(dp[j][mask][tot]&=(1<<i));
    }
    else
    {
        arr[i][j]=1;
        if(bt(i+1,j,mask|(1<<i),tot-tens[i],temp))
            return 1,(dp[j][mask][tot]&=(1<<i));
        arr[i][j]=0;
        if(bt(i+1,j,mask,tot,cl))
            return 1,(dp[j][mask][tot]&=(1<<i));
    }
    return 0;
}

int main()
{
    cin>>n>>m;
    for(int f=0;f<n;f++)
        cin>>row[f];
    for(int f=0;f<m;f++)
        cin>>col[f];
    int tot=0;
    for(int f=0;f<n;f++)
        tot+=row[f]*tens[f];
    //memset(dp,-1,sizeof dp);
    bt(0,0,0,tot,col[0]);

}
