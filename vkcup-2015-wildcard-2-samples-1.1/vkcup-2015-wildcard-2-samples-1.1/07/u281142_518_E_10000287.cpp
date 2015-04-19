#include <bits/stdc++.h>

#define	st first
#define	nd second
#define	mp make_pair
#define	pb push_back
#define	lli long long int
#define	all( gg )	gg.begin(),gg.end()
#define	foreach( gg,itit )	for( typeof(gg.begin()) itit=gg.begin();itit!=gg.end();itit++ )
#define	FP( ii,aa,bb ) for( lli ii=aa;ii<=bb;ii++ )
#define	FM( ii,aa,bb ) for( lli ii=aa;ii>=bb;ii-- )
#define	debug(ccc)	cout << #ccc << " = " << ccc << endl;

#define	mod	1000000007LL
#define	inf	2000000000LL

#define	NOSOL	return	cout << "Incorrect sequence" << endl,0;

using namespace std;

vector< pair<lli,lli> >	v;

lli	n,k,h[200000];

pair<lli,lli>	arr[300000];

lli	res[300000];

int main(){

	cin >> n >> k;

	char	s[50];
	FP( i,1,n ){
		scanf("%s",s+1);
		if( strcmp(s+1,"?")==0 ){
			arr[i] = mp(1,1);
			continue;
		}
		arr[i] = mp( 0,atoi( s+1 ) );
		res[i] = arr[i].nd;
	}

	vector<lli>	temp;

	FP( U,1,k ){
		int	K = U;
		v.clear();
		v.pb( mp( 0,-inf ) );
		while( K<=n ){
			v.pb( arr[K] );
			K += k;
		}
		v.pb( mp( 0,+inf ) );
		lli	last = -inf-1;
		FP( i,0,v.size()-1 ){
			if( v[i].st==0 ){
				if( v[i].nd<=last ){
					NOSOL;
				}
				last = v[i].nd;
				continue;
			}
			int j = i;
			while( v[j+1].st==1 )	j++;
			int	tempjj=j;
			lli	alt = last+1,ust = v[j+1].nd-1;
			if( ust-alt<j-i )	NOSOL;
			if( ust<=0 ){
				last = ust;
				while( j>=i ){
					res[(j*k-k)+U] = ust;
					ust--;
					j--;
				}
			}
			else	if( alt>=0 ){
				ust = alt+j-i;
				last = ust;
				while( j>=i ){
					res[(j*k-k)+U] = ust;
					ust--;
					j--;
				}
			}
			else{
				temp.clear();
				temp.pb( 0 );
				int	bas=-1,son=1;
				FP( ttt,1,j-i ){
					if( alt<=bas and (abs(bas)<=abs(son) or ust<son) )	temp.pb( bas-- );
					else	temp.pb( son++ );
				}
				sort( all(temp) );
				last = temp.back();
				while( j>=i ){
					res[j*k-k+U] = temp.back();
					temp.pop_back();
					j--;
				}
			}
			i = tempjj;
		}
	}

	FP( i,1,n )	printf("%lld ",res[i]);
	cout << endl;

}
