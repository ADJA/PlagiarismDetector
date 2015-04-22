#include <iostream>
#include <cstdlib>
#include <cstdio>
#include <stdio.h>
using namespace std;
int a[200000],s[200000];
int l(int e,int r,int t){
  if((e==1)&&(r==2))
   return t+t;
  if((e==1)&&(r==1))
   return t;
  return 0;
}
int main(){
  //freopen("input.txt","r",stdin);
  //freopen("output.txt","w",stdout);
  int q,w,e,r,t=0,c,v=0;
  long long ans=0;
  cin>>q;
  for(w=0;w<q;w++){
   scanf("%d",&a[w]);
   s[w]=0;}
  cin>>w;
  for(;w;w--){
   scanf("%d",&e);
   s[e-1]++;}
  v=min(s[0],s[q-1]);
  for(w=1;w<q-1;w++)
   v=min(v,s[w]>>1);
  ans=((long long)(2*(a[q-1]-a[0])))*v;
  s[0]-=v;
  s[q-1]-=v;
  for(w=1;w<q-1;w++)
   s[w]-=v+v;
  v=0;
  for(w=0;w<q;w++)
   v+=s[w];
  if(v==0){
   for(w=1;w<q;w++)
    if(a[1]-a[0]!=a[w]-a[w-1]){
     cout<<-1;
     return 0;}
   ans-=a[1]-a[0];
   cout<<ans;
   return 0;}
  if(v==1){
   cout<<ans;
   return 0;}
  if(q==2){
   cout<<ans+a[1]-a[0];
   return 0;}
  ans+=l(s[0],s[1],a[1]-a[0])+l(s[q-1],s[q-2],a[q-1]-a[q-2]);
  for(w=2;w<q-1;w++)
   ans+=min(s[w-1],s[w])*(a[w]-a[w-1]);
  cout<<ans;
  return 0;}
