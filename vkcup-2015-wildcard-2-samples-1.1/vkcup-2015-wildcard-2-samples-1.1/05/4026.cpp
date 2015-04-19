#include <cstdio>
#include <cstring>
#include <iostream>
#define MAXL 105

using namespace std;

int n;
char S[MAXL];
long long w[MAXL][2];

long long calc() {
   long long sol=0;
   for(int f=0;f<2;f++) {
      for(int i=0;i<=n;i++)
         w[i][0]=w[i][1]=0;
      w[0][f]=1;
      for(int i=1;i<n;i++) {
         if(S[i]!=0) {
            w[i][0]+=w[i-1][1];
            if(S[i-1]==0) w[i][0]+=w[i-1][0];
            w[i][1]+=w[i-1][1];
         } else {
            w[i][0]+=w[i-1][1];
            if(S[i-1]==0) w[i][0]+=w[i-1][0];
            if(S[i-1]==1) w[i][1]+=w[i-1][0];
         }
      }
      if(f!=0) {
         if(S[0]==0&&S[n-1]==1) sol+=w[n-1][0];
         if(S[0]==1) sol+=w[n-1][1];
      } else {
         sol+=w[n-1][1];
         if(S[n-1]==0) sol+=w[n-1][0];
      }
   }
   return sol;
}

int main(void)
{
   scanf("%s",S);
   n=strlen(S);
   for(int i=0;i<n;i++)
      S[i]-='A';
   cout << calc() << endl;
   return 0;
}
