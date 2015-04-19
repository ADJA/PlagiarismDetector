#include <bits/stdc++.h>
using namespace std;

int n, m;
int a[7];
int b[22];
int p[7];
vector<int> state[22];
int change[32][32];
char f[21][32][161051];

int get_dec(int n, int i) {
    return (n / p[i]) % 11;
}
int set_dec(int n, int i, int val) {
    int right = n % p[i];
    int left = n / p[i + 1];
    return left * p[i + 1] + val * p[i] + right;
}

int get_bit(int n, int i) {
    return (n >> i) & 1;
}
int set_bit(int n, int i, int val) {
    if (val == 1)
        return n | (1<<i);
    else 
        return n & ((-1) ^ (1<<i));
}

char ans[7][22];

void parse(int s, int j) {
    for (int i = 0; i < n; i++)
        if (get_bit(s, i) == 1)
            ans[i][j] = '*';
        else 
            ans[i][j] = '.';
}

int main() {

    // freopen("F.in", "r", stdin);
    ios::sync_with_stdio(false);
    cin.tie(0);

    p[0] = 1;
    for (int i = 1; i <= 5; i++)
        p[i] = p[i - 1] * 11;

    cin >> n >> m;
    int target = 0;
    for (int i = 0; i < n; i++) {
        cin >> a[i];
        target += a[i] * p[i];
    }

    state[0].push_back(0);
    for (int i = 1; i <= m; i++) {
        cin >> b[i];
        for (int j = 0; j < (1<<n); j++) {
            int count = 0;
            for (int k = 0; k < n; k++)
                if (get_bit(j, k) && (j == 0 || get_bit(j, k - 1) == 0))
                    count++;
            if (count == b[i]) {
                state[i].push_back(j);
            }
        }
    }

    for (int i = 0; i < (1<<n); i++)
        for (int j = 0; j < (1<<n); j++) {
            change[i][j] = 0;
            for (int k = 0; k < n; k++)
                if (get_bit(i, k) == 0 && get_bit(j, k) == 1)
                    change[i][j] += p[k];
        }

    memset(f, -1, sizeof f);
    f[0][0][0] = 0;
    for (int i = 0; i < m; i++) {
        for (int s: state[i]) {
            for (int k = 0; k <= target; k++)
                if (f[i][s][k] != -1) {
                    for (int ss: state[i + 1]) {
                        int new_k = k + change[s][ss];
                        f[i + 1][ss][new_k] = s;
                    }
                }
        }
    }

    for (int s: state[m]) {
        if (f[m][s][target] != -1) {
            for (int j = m; j >= 1; j--) {
                parse(s, j);
                int old_s = f[j][s][target];
                target -= change[old_s][s];
                s = old_s;
            }

            for (int i = 0; i < n; i++) {
                for (int j = 1; j <= m; j++)
                    cout << ans[i][j];
                cout << "\n";
            }

            break;
        }
    }

    return 0;
}