#include <iostream>
#include <string>

using namespace std;

const int MAXN = 100010;
const int INF = 2000000010;

string s[MAXN];
int a[MAXN];

int val(int x)
{
	return (x >= 0 ? x : -x);
}

int main()
{
	int n, k;
	cin >> n >> k;
	for (int i = 0; i < n; i++)
	{
		cin >> s[i];
		if (s[i][0] != '?')
		{
			int coef = 1;
			if (s[i][0] == '-')
			{
				coef = -1;
				s[i] = s[i].substr(1);
			}
			for (int j = 0; j < s[i].length(); j++)
				a[i] = a[i] * 10 + s[i][j] - '0';
			a[i] *= coef;
		}
	}
	for (int i = 0; i < k; i++)
	{
		int last = -INF;
		int lptr = i;
		for (int j = i; j < n; j += k)
			if (s[j][0] != '?')
			{
				int cnt = 0;
				for (int x = lptr; x < j; x += k)
					cnt++;
				if (last < -(cnt - 1) / 2 && a[j] >= cnt - ((cnt - 1) / 2))
					last = -(cnt - 1) / 2;
				if (val(last) > val(a[j] - 1))
					for (int x = 0; x < cnt; x++)
						a[lptr + k * x] = a[j] - cnt + x;
				else
					for (int x = 0; x < cnt; x++)
						a[lptr + k * x] = last + x;
				lptr = j + k;
				last = a[j] + 1;
			}
		int cnt = 0;
		for (int x = lptr; x < n; x += k)
			cnt++;
		if (last < -(cnt - 1) / 2)
			last = -(cnt - 1) / 2;
		for (int x = lptr; x < n; x += k)
		{
			a[x] = last;
			last++;
		}
			
	}
	for (int i = k; i < n; i++)
		if (a[i - k] >= a[i])
		{
			cout << "Incorrect sequence" << endl;
			return 0;
		}
	for (int i = 0; i < n; i++)
		cout << a[i] << " ";
	cout << endl;
		
}
