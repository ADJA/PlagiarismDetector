#include <iostream>
#include <vector>
#include <map>
#include <string>
#include <set>
#include <algorithm>
#include <assert.h>

using namespace std;

string s;
int main()
{
#ifdef TEST
	freopen("input.txt", "r", stdin);
	freopen("output.txt", "w", stdout);
#endif

    cin.sync_with_stdio(0);

    int n, k;
    while (cin >> n >> k)
    {
        string s;
        vector<bool> defined(n, true);
        vector<int> nums(n, 0);
        for (int i = 0; i < n; i++)
        {
            cin >> s;
            if (s == "?")
            {
                defined[i] = false;
            }
            else
            {
                int temp;
                sscanf(s.c_str(), "%d", &temp);
                nums[i] = temp;
            }
        }

        vector<pair<int, int>> vars(n, make_pair(-1000000000, 1000000000));
        bool hasAns = true;

        for (int st = 0; st < k; st++)
        {
            int left = -2000000000;
            int last = st;
            for (int i = st; i < n; i += k)
            {
                if (defined[i])
                {
                    if (nums[i] < left)
                    {
                        hasAns = false;
                        break;
                    }
                    left = nums[i] + 1;
                }
                else
                {
                    vars[i].first = left;
                    left = left + 1;
                }
                last = i;
            }

            int right = 2000000000;
            for (int i = last; i >= 0; i -= k)
            {
                if (defined[i])
                {
                    if (nums[i] > right)
                    {
                        hasAns = false;
                        break;
                    }
                    right = nums[i] - 1;
                }
                else
                {
                    vars[i].second = right;
                    right = right - 1;

                    if (vars[i].second < vars[i].first)
                    {
                        hasAns = false;
                        break;
                    }
                }
            }

            long long minVal = 0;
            for (int i = st; i < n; i += k)
            {
                if (defined[i])
                {
                    continue;
                }

                int end = i;
                int count = 1;
                for (int j = i + k; j < n; j += k)
                {
                    if (defined[j])
                    {
                        break;
                    }
                    
                    end = j;
                    count++;
                }

                int bestStart = max(vars[i].first, min(-(count / 2), vars[i].second));

                for (int j = i; j < n; j += k)
                {
                    if (defined[j])
                    {
                        break;
                    }
                    nums[j] = bestStart;
                    bestStart++;
                }

                i = end;
            }
        }

        if (!hasAns)
        {
            cout << "Incorrect sequence";
        }
        else
        {
            for (int i = 0; i < n; i++)
            {
                printf("%d ", nums[i]);
            }
            printf("\n");
        }
    }

	return 0;
}