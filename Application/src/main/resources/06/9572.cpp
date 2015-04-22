#include<bits/stdc++.h>


using namespace std;

int n, q, a[2000000], f[2000000], fst[2000000], nx[2000000];

int main() {
   srand(time(0));
   scanf("%d %d",&n,&q);
   for (int i = 1 ; i <= n ; i ++ )
	   scanf("%d",&a[i]);

   for ( ; q -- ; )
   {
	   long long b;
	   cin >> b;
	   int answer = 2e9, j = 1;
	   long long sum = 0;
	   for (int i = 1 ; i <= n ; i ++ )
	   {
		   sum += a[i];
		   while ( sum > b )
		   {
			   sum -= a[j];
			   j ++ ;
		   }
		   nx[i] = j - 1;
	   }
	   f[0] = 0;
	   for (int i = 1 ; i <= n ; i ++ )
		   f[i] = f[nx[i]] + 1;

	   for (int i = 1 ; i <= n ; i ++ )
		   if ( f[i] == 1 )
			   fst[i] = i;
		   else
			   fst[i] = fst[nx[i]];
	   sum = a[1];
	   if ( sum > b ) {
		   printf("%d\n",answer);
		   continue;
	   }
	   int it = 1;
	   long long rightpart = a[1];
	   for (int i = 2 ; i < n ; i ++ ) {
		if ( sum + a[i] > b ) break;
		sum += a[i];
		rightpart += a[i];
		it = i;
	   }
	   
	   for (int i = n ; i >= 2 ; i -- )
	   {
		   sum += a[i];
		   while ( it > 0 && sum > b ) {
			sum -= a[it];
			rightpart -= a[it];
			it -- ;
		   }
		   if ( sum > b ) break;
		   if ( fst[i - 1] <= it)
			   answer = min(answer, f[i - 1]);
		   else
			   answer = min(answer, f[i-1] + 1);
	   }

	  
	   printf("%d\n",answer);
   };
   return 0;
}
