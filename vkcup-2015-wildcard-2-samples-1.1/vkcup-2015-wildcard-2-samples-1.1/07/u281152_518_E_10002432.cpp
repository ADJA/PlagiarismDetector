#include <iostream>
#include <fstream>
#include <algorithm>
#include <cstdio>
#include <bitset>
#include <string.h>
#include <sstream>
#include <cmath>
#include <vector>

using namespace std;

#define ll long long
#define INF (1LL<<30)

int N, K;
ll A[100005];
int main() {
    scanf("%d %d",&N,&K);
    for (int i = 1;i <= N; i++) {
        string s;
        cin>>s;
        if (s == "?") {
            A[i] = INF;
        } else {
            stringstream(s) >> A[i];
        }
    }

    bool ok = true;
    for (int k = 1; k <= K; k++) {
        vector<ll> seq;
        vector<int> pos;
        seq.push_back(-2 * INF);
        pos.push_back(-1);
        for (int j = k; j <= N; j += K) {
            seq.push_back(A[j]);
            pos.push_back(j);
        }
        seq.push_back(2 * INF);
        pos.push_back(-1);
        int lastPos = 0;
        for (int i = 1; i < seq.size(); i++) {
            if (seq[i] != INF) {
                ll q = i - lastPos - 1;
                if (seq[lastPos] >= seq[i]) {
                    ok = false;
                }
                if (q == 0) {
                    lastPos = i;
                    continue;
                }
                ll diff = seq[i] - seq[lastPos] - 1;
                if (diff < q) {
                    ok = false;
                } else {
                    vector<ll> v;
                    if (seq[lastPos] < 0 && seq[i] > 0) {
                        ll l = -1, r = 1;
                        int numLeft = (int)(q - 1);
                        v.push_back(0);
                        while (numLeft) {
                            if (r < seq[i] && numLeft) {
                                v.push_back(r);
                                r++;
                                numLeft--;
                            }
                            if (l > seq[lastPos] && numLeft) {
                                v.push_back(l);
                                l--;
                                numLeft--;
                            }
                        }
                    } else if (seq[i] <= 0) {
                        for (int j = seq[i] - 1; j >= seq[i] - q; j--)
                            v.push_back(j);
                    } else {
                        for (int j = seq[lastPos] + 1; j <= seq[lastPos] + q; j++)
                            v.push_back(j);
                    }
                    sort(v.begin(), v.end());
                    int idx = 0;
                    for (int j = lastPos + 1; j < i; j++) {
                        int p = pos[j];
                        A[p] = v[idx];
                        idx++;
                    }
                }

                lastPos = i;
            }
        }
    }
    if (!ok) {
        printf("Incorrect sequence\n");
    } else {
        for (int i = 1; i <= N; i++)
            printf("%d ", (int)A[i]);
        printf("\n");
    }
    return 0;
}
