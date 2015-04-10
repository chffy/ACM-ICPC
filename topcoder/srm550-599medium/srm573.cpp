#include<iostream>
#include<cstdio>
#include<cstring>
#include<vector>
#include<algorithm>
#include<queue>
using namespace std;

typedef long long LL;
int n,a[100],b[100],c[100],m;
int f[100][100],g[100][100];

void calc_floyed(){
    for (int k=1; k<=n; ++k)
        for (int i=1; i<=n; ++i)
            for (int j=1; j<=n; ++j)
                g[i][j] |=g[i][k] & g[k][j];
}

void unique_altitude(){
    for (int i=1; i<=n; ++i) b[i]=a[i];
    sort(b+1,b+1+n);
    m=unique(b+1,b+1+n)-b-1;
    for (int i=1; i<=n; ++i) a[i]=lower_bound(b+1,b+1+m,a[i])-b;
}


LL dp[51][51];
int bo[51][51];

int abs(int x) { return x<0?-x:x; }

int cost(int x,int y){
    return abs(b[x]-b[y]);
}

queue <pair<int,int> > que;

LL spfa(){
    LL ans=1LL<<60;
    memset(bo,0,sizeof(bo));
    memset(dp,63,sizeof(dp));
    for (int i=1; i<=m; ++i) {
        dp[1][i]=cost(i,a[1]);
        bo[1][i]=1;
        que.push(make_pair(1,i));
    }
    while (!que.empty()){
        int x=que.front().first,y=que.front().second;
        que.pop();
        bo[x][y]=0;
        //printf("%d %d %lld\n",x,y,dp[x][y]);
        for (int i=1; i<=n; ++i)
            if (f[x][i]==1)
                for (int j=1; j<=y; ++j)
                    if (dp[i][j]>dp[x][y]+cost(j,a[i])){
                        dp[i][j]=dp[x][y]+cost(j,a[i]);
                        if (!bo[i][j]){
                            bo[i][j]=1;
                            que.push(make_pair(i,j));
                        }
                    }
    }
    for (int i=1; i<=m; ++i) ans=min(ans,dp[n][i]);
    return ans;
}

class SkiResorts{
public:
    LL minCost(vector <string> road, vector <int> altitude){
        n=road.size();
        memset(f,0,sizeof(f));
        for (int i=1; i<=n; ++i)
            for (int j=1; j<=n; ++j)
                if (road[i-1][j-1]=='Y') f[i][j]=1;
        memcpy(g,f,sizeof(f));
        for (int i=1; i<=n; ++i) g[i][i]=1;
        for (int i=1; i<=n; ++i) a[i]=altitude[i-1];
        calc_floyed();
        if (g[1][n]==0) return -1;
        unique_altitude();
        return spfa();
    }
};
