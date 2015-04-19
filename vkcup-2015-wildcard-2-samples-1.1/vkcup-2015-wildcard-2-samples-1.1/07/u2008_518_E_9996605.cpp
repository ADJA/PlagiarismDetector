#include <bits/stdc++.h>
using namespace std;

FILE *in = stdin;//fopen("f.in", "r");

#define MAXN 111111
int n, k;
bool here[MAXN];
int arr[MAXN];

vector<tuple<int, bool>> fill(vector<tuple<int, bool>> v){
	int siz = v.size();
	vector<int> pulses;
	for(int q = 0; q < siz; q++){
		if(get<1>(v[q]) == true){
			pulses.push_back(q);
		}
	}
	for(int q = 1; q < pulses.size(); q++){
		int ind = pulses[q];
		int prevind = pulses[q - 1];
		if(get<0>(v[ind]) <= get<0>(v[prevind])){
			return vector<tuple<int, bool>>(0);
		}
	}
	if(pulses.size() == 0){
		int left = - (siz - 1) / 2;
		for(int q = 0; q < siz; q++){
			v[q] = make_tuple(left + q, true);
		}
		return v;
	}
	for(int q = 0; q < pulses.size(); q++){
		int ind = pulses[q];
		if(q == 0){
			int left = - (ind - 1) / 2;
			if(left + ind > get<0>(v[ind])){
				left -= left + ind - get<0>(v[ind]);
			}
			for(int w = 0; w < ind; w++){
				v[w] = make_tuple(left + w, true);
			}
		}
		if(q == (int)pulses.size() - 1){
			int rem = siz - ind - 1;
			int left = - (rem - 1) / 2;
			if(left <= get<0>(v[ind])){
				left += get<0>(v[ind]) - left + 1;
			}
			for(int w = ind + 1; w < siz; w++){
				v[w] = make_tuple(left + (w - (ind + 1)), true);
			}
		}
		if(q != 0){
			int prevind = pulses[q - 1];
			int rem = ind - prevind - 1;
			int left = - (rem - 1) / 2;
			if(rem > get<0>(v[ind]) - get<0>(v[prevind]) - 1){
				return vector<tuple<int, bool>>(0);
			}
			if(left <= get<0>(v[prevind])){
				left += get<0>(v[prevind]) - left + 1;
			}
			if(left + rem > get<0>(v[ind])){
				left -= left + rem - get<0>(v[ind]);
			}
			for(int w = prevind + 1; w < ind; w++){
				v[w] = make_tuple(left + w - (prevind + 1), true);
			}
		}
	}

	return v;
}

int main(){
	fscanf(in, "%d%d\n", &n, &k);
	for(int q = 0; q < n; q++){
		char inp[111];
		fscanf(in, "%s", inp);
		if(inp[0] == '?'){
			arr[q] = 0;
			here[q] = 0;
		}
		else{
			int v;
			sscanf(inp, "%d", &v);
			arr[q] = v;
			here[q] = 1;
		}
	}

	for(int q = 0; q < k; q++){
		vector<tuple<int, bool>> v;
		for(int w = q; w < n; w += k){
			v.push_back(make_tuple(arr[w], here[w]));
		}
		v = fill(v);
		if(v.size() == 0){
			printf("Incorrect sequence\n");
			return 0;
		}
		for(int w = q; w < n; w += k){
			tie(arr[w], here[w]) = v[w / k];
		}
	}

	for(int q = 0; q < n; q++){
		if(q){
			printf(" ");
		}
		printf("%d", arr[q]);
	}
	printf("\n");
	return 0;
}