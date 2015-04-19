#include <cstdio>
#include <cstdlib>
#include <cmath>
#include <cstring>
#include <string>
#include <vector>
#include <map>
#include <set>
#include <queue>
#include <stack>
#include <utility>
#include <algorithm>
#include <iostream>
#include <sstream>
#include <iterator>

using namespace std;
typedef long long LL;

#define oo 1000000000
#define sqr(x) ((x)*(x))
#define lowbit(x) ((x)&(-(x)))

const double pi = acos(-1.0);

#define maxn 100 + 10

int n;
char str[maxn];
LL f[maxn][2][2][2][2],ans = 0;

int main()
{
	int i,j,k,l,u,v;

	scanf("%s",str+1);
	n = strlen(str+1);

	f[2][0][0][0][0] = 1, f[2][1][1][0][1] = 1, f[2][1][0][0][0] = 1, f[2][1][0][1][0] = 1;
	for( i = 2 ; i < n ; ++i )
		for( j = 0 ; j <= 1 ; ++j )
			for( v = 0 ; v <= 1 ; ++v )
				for( k = 0 ; k <= 1 ; ++k )
					for( l = 0 ; l <= 1 ; ++l )
						for( u = 0 ; u <= 1 ; ++u )
							{
								if( k == 0 && u == 1 && l == 0 )
									{
										if( str[i] == 'B' )
											f[i+1][j][v][0][1] += f[i][j][v][k][l];
									}
/*
#include <bits/stdc++.h>
void p1W() { printf ("RICHARD\n"); }
void p2W() { printf ("GABRIEL\n"); }

int T, X, R, C;

int main() {
    freopen ("q4.in", "r", stdin);
    freopen ("q4.out", "w", stdout);
    scanf ("%d", &T);
    FO (_z,0,T) {
        printf ("Case #%d: ", _z+1);
        scanf ("%d %d %d", &X, &R, &C);
        if (R > C) swap (R, C);
        if (R == 5 && C == 3) assert (false);
        if ((R*C)%X != 0) {
            p1W();
            continue;
        }
        if (X == 1) {
            p2W();
            continue;
        }
        if (X == 2) {
            p2W();
            continue;
        }
        if (X == 3) {
            if (R == 1 || C == 1) {
                p1W();
            } else {
                p2W();
            }
            continue;
        }
        if (X == 4) {
            if (R <= 2 || C <= 2) {
                p1W();
            } else {
                p2W();
            }
        }
        if (X == 5) {
            if (R <= 2 || C <= 2) {
                p1W();
            } else if (R == 3 && C == 5) {
                p1W();
            }
            else {
                p2W();
            }
        }
        if (X == 6) {
            if (R <= 3 || C <= 3) {
                p1W();
            } else {
                p2W();
            }
        }
        if (X >= 7) {
            p1W();
            continue;
        }
    }
    return 0;
}
*/
								else if( k == str[i]-'A' )
									f[i+1][j][v][u][0] += f[i][j][v][k][l];
							}
	for( i = 0 ; i <= 1 ; ++i )
		for( v = 0 ; v <= 1 ; ++v )
			for( j = 0 ; j <= 1 ; ++j )
				for( k = 0 ; k <= 1 ; ++k )
					{
						if( j == 0 && i == 1 && k == 0 && v == 0 )
							{
								if( str[1] == 'A' && str[n] == 'B' )
									ans += f[n][i][v][j][k];
							}
						else if( i == str[1]-'A' && j == str[n]-'A' )
							ans += f[n][i][v][j][k];
					}	
	cout<<ans<<endl;

	return 0;
}