#include <iostream>
#include <algorithm>
#include <string>
#include <stdio.h>
#define N 4000005
using namespace std;

int b[N],fix[N],i,j,ki,r,a[N],n,z[N],q,sum[N],e,bolo,S[N],ans;

void go(int t)
{
    if (fix[t]==1) {return;}
    if (t==2*n+1) return;
    r++;
    z[r]=b[t]-t+1;
    fix[t]=1;
    go (b[t]+1);
}

main()
{
     scanf("%d %d",&n,&q);
      for (i=1;i<=n;i++)
       {
         scanf("%d",&a[i]);
         a[i+n]=a[i];
       }
      for (i=2*n;i>=1;i--)
       sum[i]=sum[i+1]+a[i];
       
         while (q--)
          {
              ans=N;
             cin>>e;
             
              for (i=1;i<=2*n;i++)  fix[i]=0;
              
              bolo=2*n;
              for (i=2*n;i>=1;i--)
                {
                     while (sum[i]-sum[bolo+1]>e) bolo--;
                     b[i]=bolo;
                } 
            
            
            
             for (i=1;i<=n;i++)
              if (fix[i]!=1)
              {
                r=0;
                 go(i);
                 
                 S[r+1]=0; S[0]=0;
                 for (j=1;j<=r;j++)     
                  S[j]=S[j-1]+z[j];
                    
                bolo=r;
                 for (j=r;j>=1;j--)
                  if (S[j]<n) break; else
                  {
                    while (S[j]-S[bolo-1]<n && bolo>0) bolo--;
                    
                    ans=min(ans,j-bolo+1);
                  } 
                     
              } 
                 cout<<ans<<endl;
             
          }
        
       
       
}