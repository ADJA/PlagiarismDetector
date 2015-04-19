#include <iostream>
#include <fstream>
#include <cmath>
#include <algorithm>
#include <vector>
#include <set>
#include <map>
#include <stack>
#include <queue>
#include <cstdlib>
#include <cstdio>
#include <string>
#include <cstring>
#include <cassert>
#include <utility>
#include <iomanip>

using namespace std;

const int K = 5;
const int W = 1;
const int p = 257;

long long getHash(string &s, int pos, int len) {
	long long res = 0;
	long long pp = 1;

	for (int i = pos; i < pos + len; i++) {
		res += 1ll * pp * s[i];
		pp *= p;
	}

	return res;
}

map < long long, vector <int> > getFingerprints(string &s, int K, int W) {
	int len = (int) s.length();

	vector <long long> hv;

	map < long long, vector <int> > mp;

	for (int i = 0; i < len; i++) {
		if (i + K - 1 >= len)
			continue;
		long long curHash = getHash(s, i, K);
		mp[curHash].push_back(i);
	}              

	return mp;
}

string processFile(string fileName) {
	ifstream in(fileName.c_str(), ifstream::in);

	string res = "";
	string cur;

	while (getline(in, cur)) {
		while ((int) cur.length() > 0 && cur[0] <= ' ')
			cur = cur.substr(1);
		if (cur.substr(0, 8) == "#include")
			continue;
		if (cur.substr(0, 7) == "#define")
			continue;
		if (cur.substr(0, 2) == "//")
			continue;
		if (cur.substr(0, 2) == "/*")
			continue;
		if (cur.substr(0, 6) == "import")
			continue;
		if (cur.substr(0, 5) == "using")
			continue;
		if (cur.substr(0, 8) == "int main")
			continue;
		if (cur.substr(0, 8) == "template")
			continue;
		for (int i = 0; i < (int) cur.length(); i++) {
			cur[i] = tolower(cur[i]);
			if (cur[i] == ';' || cur[i] == '{' || cur[i] == '}')
				continue;
			if (cur[i] <= ' ')
				continue;
			res.append(1, cur[i]);
		}
	}

	in.close();
	return res;
}

double process(string &text1, string &text2, int K, int W) {
	map < long long, vector <int> > fp1 = getFingerprints(text1, K, W);
	map < long long, vector <int> > fp2 = getFingerprints(text2, K, W);

	int total = 0, match = 0;
	
	for (map < long long, vector <int> > :: iterator it = fp1.begin(); it != fp1.end(); it++) 
		total++; //= (int) it->second.size();

	/*for (map < long long, vector <int> > :: iterator it = fp2.begin(); it != fp2.end(); it++) 
		total += (int) it->second.size();    */

	for (map < long long, vector <int> > :: iterator it = fp1.begin(); it != fp1.end(); it++) {
		long long h = it->first;
		if (fp2.count(h)) 
			match++; //= (it->second).size() + fp2[h].size();
	}

	cerr << "MATCHED " << match << " OUT OF " << total << endl;
	cerr << "PERCENTILE IS " << 1.0 * match / total << endl;

	return 1.0 * match / total;
}

const int MAXN = 105;
const double LIM = 0.65;

int n;
string f[MAXN];
string s[MAXN];
int st[MAXN];
bool used[MAXN];
vector < vector < string > > ansv;

int getSet(int x) {
	if (st[x] == x)
		return st[x];
	return st[x] = getSet(st[x]);
}

void unite(int a, int b) {
	a = getSet(a); b = getSet(b);
	if (rand() & 1)
		swap(a, b);
	st[a] = b;
}

int main(int argc, char * argv[]) {
	assert(freopen("input.txt","r",stdin));
	assert(freopen("output.txt","w",stdout));

	/*
	1. Whitespacees
	2. Fingerprints
	3. For every fingerprint hash -> [index, doc]
	4. For every doc X: for every h in X: ...
	*/

	scanf("%d\n", &n);
	for (int i = 1; i <= n; i++) {
		getline(cin, f[i]);
        s[i] = processFile(f[i]);
        st[i] = i;
	}

	for (int i = 1; i <= n; i++) {
		for (int j = i + 1; j <= n; j++) {
			if (i == j)
				continue;
			if (process(s[i], s[j], K, W) + process(s[j], s[i], K, W) >= 2.0 * LIM)
				unite(i, j);
		}
	}

	for (int i = 1; i <= n; i++) {
		if (used[i])
			continue;
		used[i] = true;
		
		vector < string > v;
		v.push_back(f[i]);

		for (int j = i + 1; j <= n; j++) {
			if (!used[j] && getSet(j) == getSet(i)) {
				used[j] = true;
				v.push_back(f[j]);	
			}
		}

		if ((int) v.size() > 1)
			ansv.push_back(v);
	}

	printf("%d\n", (int) ansv.size());
	for (int i = 0; i < (int) ansv.size(); i++) {
		for (int j = 0; j < (int) ansv[i].size(); j++) {
			if (j)
				printf(" ");
			cout << ansv[i][j];
		}
		cout << endl;
	}                
	
	return 0;
}