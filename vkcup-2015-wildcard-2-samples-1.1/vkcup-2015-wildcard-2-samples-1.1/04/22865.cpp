#include <iostream>
#include<vector>
using namespace std;
int reb1[10000],rebnext[10000],startreb[5000],zalup[5000],canbe[5000];
int n;
int dfs(int v,int mark){
    if (zalup[v]==mark)return 0;
    zalup[v]=mark;
    int sum=0;
    for (int i=startreb[v];i!=-1;i=rebnext[i]) {
        sum+=dfs(reb1[i],mark);
    }
    return sum+1;
}

int main()
{
    int n;
    cin >> n;
    for (int i=0;i<n;++i) {
        startreb[i]=-1;
        zalup[i]=0;
        canbe[i]=0;
    }
    for (int i=0;i<n-1;++i){
        cin >> reb1[i] >> reb1[i+n-1];
        reb1[i]--;reb1[i+n-1]--;
        rebnext[i]=startreb[reb1[i+n-1]];
        rebnext[i+n-1]=startreb[reb1[i]];
        startreb[reb1[i]]=i+n-1;
        startreb[reb1[i+n-1]]=i;
    }
    //mark[0]
    //dfs(i,1);
    
    for (int i=0;i<n;++i) {
        int tmark=i+100;
        canbe[0]=tmark;
        zalup[i]=tmark;
        for (int j=0;j<n;++j) {
            int t=dfs(j,tmark);
            if (t) {
                for (int hui=n-1;hui>=t;hui--) {
                    if (canbe[hui-t]==tmark) {
                        canbe[hui]=tmark;
                        //cout << "fun " << endl;
                    }
                }
                //cout << j << " " << i << " " <<  " " << t << endl;
                //for (int hui=0; hui<n-1;++hui) cout << canbe[hui] << " " ;
                //cout << endl;
            }
            
        }
    }
    int cnt=0;
    for (int i=1;i<n-1;++i) {
        if (canbe[i]) cnt+=1;
    }
    cout << cnt << endl;
    for (int i=1;i<n-1;++i) {
        if (canbe[i]) {
            cout << i << " " << n-1-i << endl;
        }
    }
    return 0;
}
