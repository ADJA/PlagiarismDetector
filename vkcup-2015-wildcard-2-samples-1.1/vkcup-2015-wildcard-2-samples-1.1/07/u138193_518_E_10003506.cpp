#include <iostream>
#include <vector>
#include <string>
#include <cstdlib>

using namespace std;

#define QMARK -1791791791

int main()
{
    int n, k;
    cin >> n >> k;
    vector<int> arr(n);
    for (int i = 0; i < n; i++)
    {
        string s;
        cin >> s;
        if (s == "?")
            arr[i] = QMARK;
        else
            arr[i] = atoi(s.c_str());
    }
    vector<vector<int> > vecs(k);
    for (int i = 0; i < n; i++)
        vecs[i % k].push_back(arr[i]);
    for (int i = 0; i < k; i++)
    {
        size_t j = 0;
        if (vecs[i][0] == QMARK)
        {
            while (j < vecs[i].size() && vecs[i][j] == QMARK)
                j++;
            if (j == vecs[i].size())
            {
                for (int t = 0; t < (int)j; t++)
                    vecs[i][t] = t - (int)j / 2;
            }
            else
            {
                for (int t = 0; t < (int)j; t++)
                    if (vecs[i][j] <= (int)(j - 1) / 2)
                    {
                        vecs[i][t] = vecs[i][j] - (int)j + t;
                    }
                    else
                        vecs[i][t] = t - (int)j / 2;
            }
        }
        while (j < vecs[i].size())
        {
            if (vecs[i][j] == QMARK)
            {
                /*size_t t = j;
                while (t < vecs[i].size() && vecs[i][t] == QMARK)
                {
                    vecs[i][t] = vecs[i][j - 1] + (int)t - (int)j + 1;
                    t++;
                }
                j = t;*/
                size_t t = j;
                int first = vecs[i][j - 1];
                while (t < vecs[i].size() && vecs[i][t] == QMARK)
                    t++;
                int last = 1791791791;
                if (t != vecs[i].size())
                    last = vecs[i][t];
                for (int p = j; p < (int)t; p++)
                    if (first >= -((int)t - (int)j) / 2 || last <= ((int)t - (int)j - 1) / 2)
                    {
                        if (first >= -((int)t - (int)j - 1) / 2 || last <= ((int)t - (int)j - 1) / 2)
                        {
                            if (last == 1791791791 || abs(first) < abs(last))
                                vecs[i][p] = vecs[i][j - 1] + (int)p - (int)j + 1;
                            else
                                vecs[i][p] = last - ((int)t - (int)j) + p - (int)j;
                        }
                        else
                            vecs[i][p] = (p - (int)j) - ((int)t - (int)j - 1) / 2;
                    }
                    else
                        vecs[i][p] = (p - (int)j) - ((int)t - (int)j) / 2;
                 j = t;
            }
            else
                j++;
        }
    }
    vector<int> new_arr(n);
    for (int i = 0; i < k; i++)
    {
        for (int j = 0; j < (int)vecs[i].size() - 1; j++)
        {
            if (vecs[i][j] >= vecs[i][j + 1])
            {
                cout << "Incorrect sequence" << endl;
                return 0;
            }
            new_arr[j * k + i] = vecs[i][j];
        }
        new_arr[((int)vecs[i].size() - 1) * k + i] = vecs[i][(int)vecs[i].size() - 1];
    }
    for (int i = 0; i < n; i++)
        cout << new_arr[i] << " ";
    cout << endl;
    return 0;
}
