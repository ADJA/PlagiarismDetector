#include <bits/stdc++.h>

using namespace std;

typedef vector<int> vi;
typedef vector<vi> vvi;
typedef pair<int, int> ii;
typedef vector<ii> vii;
typedef vector<string> vs;
typedef vector<vs> vvs;

#define pb(x) push_back(x)
#define all(c) (c).begin(),(c).end()
#define ins(c) inserter((c),(c).begin())
#define mp(x,y) make_pair((x),(y))
#define mt(x,y,z) make_tuple((x),(y),(z))
#define INF (1e9)

ostream& operator<<(ostream& out, vi v)
{
    for (auto a: v)
        out << a << " ";
    return out;
}

ostream& operator<<(ostream& out, ii d)
{
    out << d.first << ", " << d.second << " ";

    return out;
}

ii operator-(ii A, ii B)
{
    return mp(A.first - B.first, A.second - B.second);
}

ii operator+(ii A, ii B)
{
    return mp(A.first + B.first, A.second + B.second);
}

bool is_valid(vi &v)
{
    int n = v.size();
    vii d;

    for (int i = 0; i < n; i++) {
        if (v[i] != 2*INF) {
            d.pb(mp(i, v[i]));
        }
    }

    /*
    cout << "+d " << endl;
    for (auto a: d)
        cout << a.first << " " << a.second << endl;
    cout << "-d" << endl;
    */
    for (int i = 1; i < d.size(); i++) {
        ii L = d[i-1];
        ii R = d[i];
        int diff = R.first - L.first;
        if (L.second + diff > R.second) {
            return false;
        }
    }

    int m = d.size();

    if (m == 0) {
        vi t;
        t.pb(0);
        if (t.size() < n) {
            for (int i = 1;; i++) {
                t.pb(-i);
                if (t.size() == n)
                    break;
                t.pb(i);
                if (t.size() == n)
                    break;
            }
        }
        sort(all(t));
        // cout << "t " << t << endl;
        copy(all(t), v.begin());
        return true;
    }

    if (d[0].first > 0) {
        if (d[0].second > 0) {
            int count = d[0].first;
            vi t;
            t.pb(0);
            if (t.size() < count) {
                for (int i = 1;; i++) {
                    t.pb(-i);
                    if (t.size() == count)
                        break;
                    if (i < d[0].second)
                        t.pb(i);
                    if (t.size() == count)
                        break;
                }
            }
            sort(all(t));
            // cout << "t " << t << endl;
            copy(all(t), v.begin());
        } else {
            int val = d[0].second - 1;
            for (int i = d[0].first - 1; i >= 0; i--) {
                v[i] = val--;
            }
        }
    }

    if (d[m-1].first < n - 1) {
        if (d[m-1].second < 0) {
            int count = n - d[m-1].first - 1;
            vi t;
            t.pb(0);
            if (t.size() < count) {
                for (int i = 1;; i++) {
                    if (d[m-1].second < -i)
                        t.pb(-i);
                    if (t.size() == count)
                        break;
                    t.pb(i);
                    if (t.size() == count)
                        break;
                }
            }
            sort(all(t));
            // cout << "t " << t << endl;
            copy(all(t), v.begin() + d[m-1].first + 1);
        } else {
            int val = d[m-1].second + 1;
            for (int i = d[m-1].first + 1; i < n; i++) {
                v[i] = val++;
            }
        }
    }

    for (int i = 1; i < d.size(); i++) {
        ii L = d[i-1];
        ii R = d[i];
        if (L.first + 1 == R.first)
            continue;
        // cout << "L " << L.first << " " << L.second << endl;
        // cout << "R " << R.first << " " << R.second << endl;
        if (0 <= L.second) {
            int val = L.second+1;
            for (int j = L.first + 1; j < R.first; j++) {
                v[j] = val++;
            }
        } else if (R.second <= 0) {
            int val = R.second - 1;
            for (int j = R.first - 1; j > L.first; j--) {
                v[j] = val--;
            }
        } else {
            int count = R.first - L.first - 1;
            // cout << "count " << count << endl;
            vi t;
            t.pb(0);
            if (t.size() < count) {
                for (int i = 1;; i++) {
                    if (L.second < -i)
                        t.pb(-i);
                    if (t.size() == count)
                        break;
                    if (i < R.second)
                        t.pb(i);
                    if (t.size() == count)
                        break;
                }
            }
            sort(all(t));
            // cout << "t " << t << endl;
            copy(all(t), v.begin() + L.first + 1);
        }
    }

    return true;
}

bool is_valid(vvi &v)
{
    for (auto &a: v) {
        if (!is_valid(a))
            return false;
    }

    return true;
}

int main()
{
    int n, k;
    cin >> n >> k;
    vvi v(k);
    for (int i = 0; i < n; i++) {
        string s;
        cin >> s;
        if (s == "?")
            v[i%k].pb(2*INF);
        else {
            stringstream ss(s);
            int a;
            ss >> a;
            v[i%k].pb(a);
            // v[i%k].pb(stoi(s));
        }
    }

    /*
    for (int i = 0 ;i < k; i++)
        cout << i << " " << v[i] << endl;
    */

    if (!is_valid(v)) {
        cout << "Incorrect sequence" << endl;
    } else {
        // cout << "ans" << endl;
        for (int i = 0; i < n; i++) {
            cout << v[i%k][i/k] << " ";
        }
        cout << endl;
    }

    return 0;
}