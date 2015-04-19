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

const int K = 8;
const int W = 9;
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

	for (int i = 0; i < len; i++) {
		if (i + K - 1 >= len)
			continue;
		long long curHash = getHash(s, i, K);
		hv.push_back(curHash);
	}              

	map < long long, vector <int> > mp;

	for (int i = 0; i < len; i++) {
		if (i + W - 1 >= (int) hv.size())
			continue;
		int mn = -1;
		for (int j = i + W - 1; j >= i; j--) {
			if (mn == -1 || hv[j] < hv[mn])
				mn = j;
		}
		
		long long mnH = hv[mn];
		if (!mp[mnH].empty() && mp[mnH].back() == mn)
			continue;
		mp[hv[mn]].push_back(mn);
	}

	return mp;
}

string processFile(string fileName) {
	ifstream in(fileName.c_str(), ifstream::in);

	string res = "";
	string cur;
	while (in >> cur) {
		res += cur;
	}              

	in.close();
	return res;
}

double process(char* f1, char* f2, int K, int W) {
	string file1(f1), file2(f2);

	string text1 = processFile(file1);
	string text2 = processFile(file2);

	map < long long, vector <int> > fp1 = getFingerprints(text1, K, W);
	map < long long, vector <int> > fp2 = getFingerprints(text2, K, W);

	int total = 0, match = 0;
	
	for (map < long long, vector <int> > :: iterator it = fp1.begin(); it != fp1.end(); it++) 
		total += (int) it->second.size();

	for (map < long long, vector <int> > :: iterator it = fp2.begin(); it != fp2.end(); it++) 
		total += (int) it->second.size();

	for (map < long long, vector <int> > :: iterator it = fp1.begin(); it != fp1.end(); it++) {
		long long h = it->first;
		if (fp2.count(h)) 
			match += (it->second).size() + fp2[h].size();
	}

	cerr << "MATCHED " << match << " OUT OF " << total << endl;
	cerr << "PERCENTILE IS " << 1.0 * match / total << endl;

	return 1.0 * match / total;
}

int main(int argc, char * argv[]) {
	//assert(freopen("input.txt","r",stdin));
	//assert(freopen("output.txt","w",stdout));

	/*
	1. Whitespacees
	2. Fingerprints
	3. For every fingerprint hash -> [index, doc]
	4. For every doc X: for every h in X: ...
	*/

	if (argc == 3) {
		process(argv[1], argv[2], K, W);
		return 0;
	}

	double mx = -1.0;
	double bestK = -1, bestW = -1;

	for (int K = 3; K <= 50; K++) {
		for (int W = 1; W <= 10; W++) {
			double diff = process(argv[1], argv[2], K, W) - process(argv[3], argv[4], K, W);
			if (diff > mx) {
				mx = diff;
				bestK = K; bestW = W;
				cout << mx << " " << bestK << " " << bestW << endl;
			}
		}
	}
	
	cout << mx << " " << bestK << " " << bestW << endl;
	
	return 0;
}