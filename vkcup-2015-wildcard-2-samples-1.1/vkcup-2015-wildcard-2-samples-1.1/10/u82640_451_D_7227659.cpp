#include <iostream>
#include <stdio.h>
#include <string.h>
#include <algorithm>
using namespace std;

int l;
char s[110000];

int main()
{
    while (~scanf("%s",s)){
        int l=strlen(s);
        long long  a1=0,a2=0,b1=0,b2=0,e=0,o=0;

        for (int i=0;i<l;i++)
        {
            if (s[i]=='a')
            {
                if (i%2)
                {
                       a1++;
                    o+=a1;
                    e+=a2;

                }
                else
                {
                    a2++;
                    o+=a2;
                    e+=a1;

                }
            }
            else
            {
                if (i%2)
                {
                    b1++;
                    o+=b1;
                    e+=b2;

                }
                else
                {
                     b2++;
                    o+=b2;
                    e+=b1;

                }

            }
        }
        cout<<e<<" "<<o<<endl;
    }

    return 0;
}
