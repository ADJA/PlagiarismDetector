#include <bits/stdc++.h>
using namespace std;

int n, m;
int cntCol[21];
int cntRow[5];
bool ans[5][20];

vector<int> masksFor[6];
unordered_set<int> seen;

int curCnt[5];
bool go ( int col, int pmask )
{
/*	cout << "go ( " << col << ", ";
	for ( int i = 0, x = pmask; i < n; ++i, x /= 2 ) cout << x%2; 
	cout << " )" << endl;  */

	int code = 0;
	for ( int i = 0; i < n; ++i )
		code = 11*code + curCnt[i];
	code = (1<<5)*code + pmask;
	code = (m+1)*code + col;

	if ( seen.count(code) ) return false;
	seen.insert ( code );

	int i;
	if ( col == m ) {
		for ( i = 0; i < n; ++i )
			if ( curCnt[i] != cntRow[i] )
				return false;
		return true;
	}

	for ( i = 0; i < n; ++i )
		if ( curCnt[i] > cntRow[i] || curCnt[i] + (m-col+1)/2 < cntRow[i] )
			return false;

	for ( int mask : masksFor[cntCol[col]] ) {
		for ( i = 0; i < n; ++i )
			if ( !((pmask>>i)&1) && ((mask>>i)&1) )
				curCnt[i]++;

		if ( go ( col+1, mask ) ) {
			for ( i = 0; i < n; ++i )
				ans[i][col] = ( (mask>>i)&1 ? true : false);
			return true;
		}

		for ( i = 0; i < n; ++i )
			if ( !((pmask>>i)&1) && ((mask>>i)&1) )
				curCnt[i]--;
	}

	return false;
}

int main()
{
	cin >> n >> m;
	for ( int i = 0; i < n; ++i )
		cin >> cntRow[i];
	for ( int i = 0; i < m; ++i )
		cin >> cntCol[i];

	for ( int mask = 0; mask < (1<<n); ++mask ) {
		int cnt = mask&1;
		for ( int i = 1; i < n; ++i )
			if ( (mask>>i)&1 )
				if ( !( (mask>>(i-1))&1 ) )
					cnt++;
		masksFor[cnt].push_back ( mask );
	}

	assert ( go(0,0) );
	for ( int i = 0; i < n; ++i ) {
		for ( int j = 0; j < m; ++j )
			if ( ans[i][j] ) printf ( "*" );
			else printf ( "." );
		printf ( "\n" );
	}

	return 0;
}
