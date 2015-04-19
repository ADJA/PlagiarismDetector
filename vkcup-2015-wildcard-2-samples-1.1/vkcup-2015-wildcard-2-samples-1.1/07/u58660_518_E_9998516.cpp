#include <cstdio>
#include <algorithm>
#define INF (1123123123)

using namespace std;

int vals[100005];
int knw[100005];

char in[20];
int pl,ret;

inline int ucitaj(int &marker)
{
    scanf("%s",in);
    if (in[0]=='?')
    {
        marker=0;
        return 0;
    }
    int pl=0;
    int mult=1;
    if (in[0]=='-')
    {
        mult=-1;
        pl++;
    }
    ret=0;
    while (in[pl])
    {
        ret=ret*10+in[pl]-'0';
        pl++;
    }
    marker=1;
    return ret*mult;
}

int n,k;

int main()
{
    scanf("%d%d",&n,&k);
    for (int i=1; i<=n; i++)
        vals[i]=ucitaj(knw[i]);
    for (int it=1; it<=k; it++)
    {
        long long mn,mx;
        int st,ln;
        ln=0;
        mn=-INF;
        mx=INF;
        for (int i=it; i<=n; i+=k)
        {
            if (knw[i])
            {
                if (i>it && vals[i]<=mn)
                {
                    printf("Incorrect sequence\n");
                    return 0;
                }
                if (ln>0)
                {
                    mx=vals[i];
                    //handle insert
                    if (mx-mn-1<ln)
                    {
                        printf("Incorrect sequence\n");
                        return 0;
                    }
                    int fp=INF;
                    if (mn>=0)
                        fp=mn+1;
                    if (mx<=0)
                        fp=mx-ln;
                    if (mn<0 && mx>0)
                    {
                        long long mdst=min(mx,-mn);
                        if (mdst*2-1>=ln)
                            fp=-((ln-1)/2);
                        else
                        {
                            if (mx>-mn)
                                fp=mn+1;
                            else
                                fp=mx-ln;
                        }
                    }
                    for (int cnt=0; cnt<ln; cnt++)
                        vals[st+cnt*k]=fp+cnt;

                    ln=0;
                    st=-1;
                }
                mn=vals[i];
                mx=INF;
            }
            else
            {
                if (i==it)
                {
                    mn=-INF;
                    mx=INF;
                    st=i;
                    ln=1;
                }
                else
                {
                    if (ln==0)
                    {
                        mx=INF;
                        st=i;
                        ln=1;
                    }
                    else
                    {
                        ln++;
                    }
                }
            }
        }
        if (ln>0)
        {
            //handle insert
            if (mx-mn-1<ln)
            {
                printf("Incorrect sequence\n");
                return 0;
            }
            int fp=INF;
            if (mn>=0)
                fp=mn+1;
            if (mx<=0)
                fp=mx-ln;
            if (mn<0 && mx>0)
            {
                long long mdst=min(mx,-mn);
                if (mdst*2-1>=ln)
                    fp=-((ln-1)/2);
                else
                {
                    if (mx>-mn)
                        fp=mn+1;
                    else
                        fp=mx-ln;
                }
            }
            for (int cnt=0; cnt<ln; cnt++)
                vals[st+cnt*k]=fp+cnt;

            ln=0;
            st=-1;
        }


    }
    for (int i=1; i<=n; i++)
        printf("%d ",vals[i]);
}
