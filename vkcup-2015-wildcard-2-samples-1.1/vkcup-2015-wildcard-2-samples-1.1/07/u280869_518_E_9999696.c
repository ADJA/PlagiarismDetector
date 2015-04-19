#include <stdio.h>


char str[2000010];
int arr[100010];
int dp1[100010], dp2[100010];
int n, k;


int min(int a, int b){return a<b?a:b;}
int max(int a, int b){return a>b?a:b;}


void gao()
{
    int i, j, kk, pos, left, right;
    int start;
    int number;
    for (i = 0; i < n; i++)
    {
        if (i - k >= 0)
        {
            if (arr[i-k] != 2000000000)
                dp1[i] = i-k;
            else
                dp1[i] = dp1[i-k];
        }
        else
            dp1[i] = -1;
    }
    for (i = n-1; i >= 0; i--)
    {
        if (i+k < n)
        {
            if (arr[i+k] != 2000000000)
                dp2[i] = i+k;
            else
                dp2[i] = dp2[i+k];
        }
        else
            dp2[i] = -1;
    }
    
    for (i = 0; i < n; i++) if (arr[i] != 2000000000)
    {
        pos = i, left = dp1[i], right = dp2[i];
        if (left != -1)
        {
            if (arr[i] < arr[left] + (pos - left)/k) goto IRR;
        }
        if (right != -1)
        {
            if (arr[i] > arr[right] + (right-pos)/k) goto IRR;
        }
    }
    for (kk = 0; kk < k; kk++)
    {
        int left_num, right_num;
        left = kk-k; left_num = -2000000000;
        for (i = kk; i < n; i += k) if (arr[i] != 2000000000)
        {
            right_num = arr[i];
            number = (i-left)/k-1;
            if (number != 0)
            {
                
                if (left_num >= 0)
                    start = left_num+1;
                if (right_num <= 0)
                    start = right_num - number;
                else
                {
                    start = max(left_num+1, -(number-1)/2);
                    start = min(right_num - number, start);
                }
            }
            for (j = left+k; j < i; j+=k)
            {
                arr[j] = start++;
            }
            left = i, left_num = arr[i];
        }
        right_num = 2000000000;
        number = (i-left)/k-1;
        if (number != 0){
            if (left_num >= 0)
                start = left_num+1;
            if (right_num <= 0)
                start = right_num - number;
            else
            {
                start = max(left_num+1, -(number-1)/2);
                start = min(right_num - number, start);
            }
        }
        for (j = left+k; j < i; j +=k)
            arr[j] = start++;
        
    }
    for (i = 0; i < n; i++)
        printf ("%d ", arr[i]);
    puts ("");
    return ;
    IRR:
        puts ("Incorrect sequence");
}


int main()
{
    int num, sign, i, idx;
    while (~scanf ("%d%d", &n, &k))
    {
        getchar();
        gets(str);
        idx = 0;
        num = 0;
        sign = 1;
        for (i = 0; str[i]; i++)
        {
            if (str[i] == '?')
                num = 2000000000;
            else if (str[i] == ' ')
            {
                arr[idx++] = num * sign;
                num = 0, sign = 1;
            }
            else if (str[i] == '-')
            {
                sign = -1;
            }
            else
            {
                num = num * 10 + str[i] - '0';
            }
        }
        arr[idx++] = num * sign;
        gao();
    }
    return 0;
}
