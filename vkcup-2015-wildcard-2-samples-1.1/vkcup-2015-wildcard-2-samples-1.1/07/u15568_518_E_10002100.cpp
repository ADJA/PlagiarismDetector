#include <iostream>
#include <fstream>
#include <stdio.h>
#include <stdlib.h>
#include <cstring>
#include <string>
#include <vector>
#include <map>
#include <set>
#include <deque>
#include <queue>
#include <stack>
#include <algorithm>

#define _USE_MATH_DEFINES
#include <math.h>
#include <ctype.h>
#include <assert.h>

#define forn(i,n) for (int i=0;i<n;i++)
#define rforn(i,n) for (int i=n-1;i>=0;i--)
#define mp make_pair
#define LL long long

using namespace std;

void smain();

int main() {
    ios_base::sync_with_stdio(false);
#ifndef ONLINE_JUDGE
    freopen("input.txt", "r", stdin);
    //freopen("output.txt", "w", stdout);
#endif
    smain();

    return 0;
}

#define int long long

bool b[200000];
int a[200000];

void smain(){
	int n, k;

	char str[200]={0};
	cin>>n>>k;

	forn(i,n) {
		cin>>str;
		if (str[0]=='?')
			b[i] = false;
		else
		{
			b[i] = true;
			a[i] = atoi(str);
		}
	}

	int pos, q, mx, pos2, pos3, mxl, mxr;
	int s1, s2;
	forn(st, k) {
		pos = st;
		q = 0;
		while (pos < n && b[pos] == false) {
			q++;
			pos += k;
		}

		if (pos < n) {
			mx = a[pos]-1;
			if (mx>q/2)
				mx = q/2;
		} else {
			mx = q/2;
		}

		pos2 = pos - k;
		while (pos2 >=st) {
			a[pos2] = mx;
			b[pos2] = true;
			mx--;
			pos2 -= k;
		}

		pos2 = pos+k;
		while (pos2<n) {
			if (b[pos2]==true) {
				if (a[pos] >= a[pos2]) {
					cout<<"Incorrect sequence";
					return;
				}

				pos = pos2;
				pos2 = pos+k;
				continue;
			}

			pos3 = pos2;
			q = 0;
			while (pos3 < n && b[pos3]==false) {
				pos3 += k;
				q++;
			}

			if (pos3 >= n) {
				mx = -q/2;
				if (mx <= a[pos]) {
					mx = a[pos]+1;
				}

				pos3 = pos2;
				while (pos3<n) {
					a[pos3] = mx;
					b[pos3] = true;
					mx++;
					pos3 += k;
				}

				pos = pos3;
				pos2 = pos + k;
			} else {
				if (a[pos3] - a[pos] <= q) {
					cout<<"Incorrect sequence";
					return;
				}

				mxl = -q/2;
				mxr = mxl + q-1;

				if (mxl<=a[pos]) {
					mxl = a[pos]+1;
					mxr = mxl + q-1;
				}

				if (mxr>=a[pos3]) {
					mxr = a[pos3]-1;
					mxl = mxr - q+1;
				}

				pos2 = pos+k;
				forn(i,q) {
					a[pos2] = mxl;
					b[pos2] = true;
					mxl++;
					pos2 += k;
				}

				pos = pos3;
				pos2 = pos+k;
			}
		}
	}

	forn(i,n) {
		cout<<a[i]<<' ';
	}
}
