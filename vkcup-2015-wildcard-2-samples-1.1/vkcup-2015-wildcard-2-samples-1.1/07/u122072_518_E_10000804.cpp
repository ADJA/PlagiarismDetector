#include <iostream>
#include <vector>
#include <cstdio>

using namespace std;

const int inf = 1e9+1;

int main()
{
    ios_base::sync_with_stdio(false);
    int n,k;
    cin >> n >>k;
    vector<vector<int> > a(k);
    for(int i=0;i<n;i++)
    {
        char b[20];
        cin >> b;
        int x = inf;
        if(b[0]!='?') sscanf(b,"%d",&x);
        a[i%k].push_back(x);
    }

    for(int i=0;i<k;i++)
    {
        if(a[i].size()==0) continue;
        int l =0 ;
        while(l<a[i].size() && a[i][l]==inf) l++;
        if(l==a[i].size())
        {
            l/=2;
            l*=-1;
            for(int j =0; j<a[i].size();j++)
                a[i][j] = l++;
            continue;
        }
        if(l>0)
        {
            if(a[i][l]>(l-1)/2)
            {
                int v = l/2;
                v*=-1;
                for(int j =0; j<l;j++)
                    a[i][j] = v++;
            }else
            {
                for(int j = l-1;j>=0;j--)
                    a[i][j] = a[i][j+1]-1;
            }
        }
        int prev = a[i][l];
        while(l<a[i].size()-1)
        {
            int r = l+1;
            while(r< a[i].size() && a[i][r]==inf) r++;

            int count = r-l-1;

            if(r==a[i].size())
            {
                if(prev< -(count-1)/2)
                {
                    int v = count/2;
                    for(int j=a[i].size()-1;j>l;j--)
                        a[i][j]=v--;
                }else
                {
                    for(int j=l+1;j<a[i].size();j++)
                        a[i][j]=a[i][j-1]+1;
                }
                break;
            }
            count/=2;
            if(prev + r-l >a[i][r]) {cout <<"Incorrect sequence"; return 0;}

            if(prev>= - count)
            {
                for(int j = l+1;j<=r-1;j++)
                    a[i][j] = a[i][j-1]+1;
            }else
            if(a[i][r]<=count)
            {
                for(int j = r-1;j>l;j--)
                    a[i][j] = a[i][j+1]-1;
            }else
            {
                int v = -count;
                for(int j=l+1;j<=r-1;j++)
                    a[i][j] = v++;
            }
            l=r;
            prev = a[i][r];
        }

    }


    int x=0;
    int y=0;
    for(int i=0;i<n;i++)
    {
        printf("%d ",a[x][y]);
        x++;
        if(x==k) {x=0; y++;}
    }

    return 0;
}
