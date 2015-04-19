#include <iostream>
#include <cstdio>
#include <string>
#include <cmath>
#include <cstring>
#include <cstdlib>
#include <algorithm>
#define oo 1000100005
using namespace std;

int k, n, a[200005];

int getint ()
{
	char c = getchar ();
	while ((c < '0' || c > '9') && (c != '-') && (c != '?')) c = getchar ();
	if (c == '?') return oo+1;
	int k = 1;
	if (c == '-') { k = -1; c = getchar(); }
	int tmp = 0;
	for (; c >= '0' && c <= '9'; c = getchar())
		tmp = tmp * 10 + (c - '0');
	return tmp * k;
}

int main()
{
	n = getint();
	k = getint();
	for (int i = 1; i <= n; i++) a[i] = getint();
	a[0] = -oo;
	for (int i = n + 1; i <= 2*n; i++) a[i] = oo-1;
	for (int i = 1; i <= k; i++)
	{
		int last = 0;
		for (int j = i; j <= n + k; j += k) //!!
			if (a[j] < oo)
			{
				//printf("%d %d\n",j,last);
				if (a[j] <= a[last]) 
				{
					cout << "Incorrect sequence" << endl;
					return 0;
				}
				int x;
				if (last == 0) x = (j - i) / k;
				else x = (j - last) / k - 1;
				if (a[last] < 0 && a[j] > 0)
				{
					int y = min (abs(a[last]+1), a[j]-1);
					//printf(" !! %d %d\n",x,y);
					if (y + y + 1 >= x)
					{
						y = (x - 1) / 2;
						if (last == 0) last = i - k;
						for (int p = last + k, q = -y; p < j; p += k, q++)
							a[p] = q;
					}
					else
					{
						if (abs (a[last]) < a[j])
						{
							for (int p = last + k; p < j; p += k)
								a[p] = a[p-k] + 1;
							if (a[j-k] >= a[j]) 
							{
								cout << "Incorrect sequence" << endl;
								return 0;
							}
						}
						else
						{
							int p;
							for (p = j - k; p > last; p -= k)
								a[p] = a[p+k] - 1;
							p += k;
							if (a[p] <= a[last])
							{
								cout << "Incorrect sequence" << endl;
								return 0;
							}
						}
					}
				}
				else
				{
					if (abs (a[last]) < abs (a[j]))
					{
						for (int p = last + k; p < j; p += k)
							a[p] = a[p-k] + 1;
						if (a[j-k] >= a[j]) 
						{
							cout << "Incorrect sequence" << endl;
							return 0;
						}
					}
					else
					{
						if (last == 0) last = i-k;
						int p;
						for (p = j - k; p > last; p -= k)
							a[p] = a[p+k] - 1;
						p += k;
						if (a[p] <= a[max (0,last)])
						{
							cout << "Incorrect sequence" << endl;
							return 0;
						}
					}
				}
				last = j;
			}
	}
	for (int i = 1; i <= n; i++)
		printf ("%d ", a[i]);
	printf("\n");
	//system("pause");
	
	return 0;
}
