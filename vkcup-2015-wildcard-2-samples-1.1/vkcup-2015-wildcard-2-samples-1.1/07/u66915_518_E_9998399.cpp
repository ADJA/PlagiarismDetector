#include <iostream>
#include <fstream>
using namespace std;

ifstream f("wow.in");

#define invalid "Incorrect sequence"
#include <algorithm>
#define LE 100666
#define inf (1001000000)
#define f cin

int mdl(int val)
{
    return val<0?-val:val;
}

bool comp(int i1,int i2)
{
    return mdl(i1)<mdl(i2);
}

#define x first
#define y second
#define mp make_pair
#include <vector>
#define pb push_back

vector<pair<int,bool> > A;
vector<int> S;
bool UNK[LE];
int val[LE],ST[LE*10];
int result[LE];

int main()
{
    int n,k,i,j,it;
    string str;

    f>>n>>k;
    f.get();

    for(i=0; i<n; ++i)
    {
        f>>str;
        if (str[0]=='?')  UNK[i]=true;
        else
        {
            int semn=1;
            j=0;
            if (str[0]=='-') semn=-1,j=1;

            for(; j<(int)str.length(); ++j)
                val[i]=val[i]*10+(str[j]-'0');

            val[i]*=semn;
        }
    }

    for(i=0; i<k; ++i)
    {
        A.clear();
        A.pb(mp(-inf-1,false));
        for(j=i; j<n; j+=k) A.pb(mp(val[j],UNK[j]));
        A.pb(mp(inf+1,false));

        int N=A.size();

        for(j=1; j<N-1; ++j)
        {
            if (A[j].y==false) continue;
            int t=j;
            while (t+1<N&&A[t+1].y==true) ++t;
            int nr_el=t-j+1;

            int vst=A[j-1].x,vdr=A[t+1].x;

            if (vdr-vst-1<nr_el)
            {
                cout<<invalid<<'\n';
                return 0;
            }

            S.clear();
            for(it=0; it+1<=nr_el+2&&it>=vst&&it<=vdr; ++it) S.pb(it);
            for(it=0; (-it)<=nr_el+2&&it>=vst&&it<=vdr; --it) S.pb(it);
            for(it=vst; (it-vst+1)<=nr_el+2&&it<=vdr; ++it) S.pb(it);
            for(it=vdr; (vdr-it+1)<=nr_el+2&&it>=vst; --it) S.pb(it);

            sort(S.begin(),S.end());
            int l=0,N=S.size();

            for(it=0; it<N; ++it)
                if (S[it]!=vst&&S[it]!=vdr)
                {
                    if(l==0)
                        ST[++l]=S[it];
                    else
                    {
                        if (ST[l]!=S[it])
                            ST[++l]=S[it];
                    }
                }

            sort(ST+1,ST+l+1,comp);
            sort(ST+1,ST+nr_el+1);
            for(it=j; it<=t; ++it) A[it].x=ST[it-j+1];
            j=t;
        }

        it=i;
        for(j=1; j<N-1; ++j)
        {
            result[it+(j-1)*k]=A[j].x;

            if (A[j].x<=A[j-1].x)
            {
                cout<<invalid;
                return 0;
            }
        }
    }

    for(i=0; i<n; ++i)
        cout<<result[i]<<" ";

    return 0;
}
