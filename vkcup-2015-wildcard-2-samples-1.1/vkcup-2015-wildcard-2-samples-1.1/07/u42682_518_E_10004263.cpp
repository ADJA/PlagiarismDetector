#include <bits/stdc++.h>
using namespace std;
#define ll long long
#define gc getchar

int a[500005];
bool v[500005];

int read(int i) {
  char c = gc();
  while((c<'0' || c>'9') && c!='?' && c!='-') c = gc();
  bool sig = 1;
  if(c=='?') { v[i] = 1; return 0; }
  if(c=='-') { c = gc(); sig = 0; }
  int ret = 0;
  while(c>='0' && c<='9') {
    ret = 10 * ret + c - 48;
    c = gc();
  }
  if(sig) return ret;
  return -ret;
}

int main(){ 
  ios_base::sync_with_stdio(0);
  int n,k;
  n = read(0); k = read(0);
  //cout<<n<<" "<<k<<endl;
  for(int i=0; i<n; i++) {
    a[i] = read(i);
    //cout<<a[i]<<" "<<v[i]<<endl;
  }
  bool ov = true;
  for(int i=0; i<k; i++) {
    int l = i-k;
    while(l+k<n) {
      int r = l+k; int p = 0;
      while(r<n && v[r]) { r+=k; p++; }
      //cout<<"1: "<<l<<" "<<r<<endl;
      int r2 = r;
      if(l<0 && r>=n) {
        int cur = -(p/2);
        r = l+k; while(r<n) { a[r] = cur; cur++; r+=k; }
      }
      else if(l<0) {
        int cur = a[r]-1; if(cur>p/2) cur = p/2;
        r-=k; while(r>=0) { a[r] = cur; cur--; r-=k; }
      }
      else if(r>=n) {
        int cur = a[l]+1; if(cur<-(p/2)) cur = -(p/2);
        r = l+k; while(r<n) { a[r] = cur; cur++; r+=k; }
      }
      else if(a[r]-p-1<a[l]) {
        ov = false;
      }
      else if(a[l]>0) {
        int cur = a[l]+1;
        r = l+k; while(r<n && v[r]) { a[r] = cur; cur++; r+=k; }
      }
      else if(a[r]<0) {
        int cur = a[r]-1;
        r-=k; while(r>=0 && v[r]) { a[r] = cur; cur--; r-=k; }
      }
      else {
        int cur = -(p/2);
        if(cur<a[l]+1) cur = a[l]+1;
        else {
          while(cur+p>a[r]) cur--;
        }
        r = l+k; while(r<n && v[r]) { a[r] = cur; cur++; r+=k; }
      }
      l = r2;
    }
  }
  if(!ov) {
    cout<<"Incorrect sequence"<<endl;
  }
  else {
    for(int i=0; i<n; i++) cout<<a[i]<<" ";
    cout<<endl;
  }
  return 0;
}