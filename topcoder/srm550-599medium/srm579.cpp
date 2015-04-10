#include<iostream>
#include<cstdio>
#include<cstring>
#include<string>
#include<vector>
using namespace std;

int ss[100],tt[100],du[100];
int f[100][100];
int dp[1<<16][20];
const int inf=1000000000;

int gett(const string &s,int p,int &x){
    x=0;
    while (s[p]>'9' || s[p]<'0') ++p;
    while (p<s.size() && s[p]>='0' && s[p]<='9')
        x=x*10+s[p++]-'0';
    return p;
}

int find(int i,int j,int t){
    t+=f[i][j];
    if (t>tt[j]) return -1;
    return max(t,ss[j])+du[j];
}

int solve(int x){
    int ans=0;
    for (;x; x-=x & -x) ++ans;
    return ans;
}

class TravellingPurchasingMan{
public:
    int maxStores(int N, vector <string> interestingStores, vector <string> roads){
        int m=interestingStores.size();
        for (int i=0; i<m; ++i){
            int p=0;
            p=gett(interestingStores[i],p,ss[i]);
            p=gett(interestingStores[i],p,tt[i]);
            p=gett(interestingStores[i],p,du[i]);
        }
        memset(f,63,sizeof(f));
        for (int i=0; i<roads.size(); ++i){
            int p=0,x,y,z;
            p=gett(roads[i],p,x);
            p=gett(roads[i],p,y);
            p=gett(roads[i],p,z);
            f[x][y]=f[y][x]=min(f[x][y],z);
        }
        for (int i=0; i<N; ++i) f[i][i]=0;
        for (int k=0; k<N; ++k)
            for (int i=0; i<N; ++i)
                for (int j=0; j<N; ++j)
                    f[i][j]=min(f[i][k]+f[k][j],f[i][j]);
        memset(dp,63,sizeof(dp));
        for (int i=0; i<m; ++i){
            int p=find(N-1,i,0);
            if (p==-1) continue;
            dp[1<<i][i]=p;
        }
        for (int opt=0; opt<(1<<m); ++opt)
            for (int i=0; i<m; ++i){
                if (dp[opt][i]>=inf) continue;
                for (int j=0; j<m; ++j)
                    if (!((1<<j) & opt)){
                        int p=find(i,j,dp[opt][i]);
                        if (p==-1) continue;
                        dp[opt | (1<<j)][j]=min(dp[opt | (1<<j)][j],p);
                    }
            }
        int ans=0;
        for (int opt=0; opt<1<<m; ++opt)
            for (int i=0; i<m; ++i)
                if (dp[opt][i]<inf) ans=max(ans,solve(opt));
        return ans;
    }
};
