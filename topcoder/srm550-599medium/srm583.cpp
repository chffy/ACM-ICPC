#include<iostream>
#include<cstdio>
#include<cstring>
#include<vector>
using namespace std;

int first[100],Next[1000],End[1000],w1[1000],w2[1000];
int tot,n,sum[100];

void add_edge(int x,int y,int c1,int c2){
    Next[++tot]=first[x];
    first[x]=tot;
    End[tot]=y;
    w1[tot]=c1;
    w2[tot]=c2;
}

int f[53][53];
int g[2][53][53];

void swap(int &a,int &b){
    int t=a; a=b; b=t;
}

void dfs(int x,int fa){
    f[x][0];
    sum[x]=1;
    for (int i=0; i<=n; ++i) 
        g[0][x][i]=f[0][0];
    int cur=0,nex=1;
    g[0][x][0]=0;
    for (int k=first[x]; k; k=Next[k]){
        int l=End[k];
        if (l==fa) continue;
        dfs(l,x);
        sum[x]+=sum[l];
        for (int i=0; i<=n; ++i)
            g[nex][x][i]=f[0][0];
        for (int i=0; i<=n; ++i){
            if (g[cur][x][i]==f[0][0]) continue;
            for (int j=0; j<=sum[l]; ++j){
                if (f[l][j]>=1000) continue;
                int z=0;
                if (w2[k] && ((j&1)&&(w1[k])))z=1;
                if (w2[k]&&(!(j&1)&&(!w1[k])))z=1;
                int z1=j+z;
                for (int k=0; k<=min(z1,i); ++k){
                    int c=z1+i-2*k;
                    if (c>n) continue;
                    g[nex][x][c]=min(g[nex][x][c],g[cur][x][i]+f[l][j]+k);
                }
            }
        }
        swap(nex,cur);
    }
    for (int i=n-1; i>=0; --i)
        g[cur][x][i]=min(g[cur][x][i],g[cur][x][i+1]+1);
    for (int i=0; i<=n; ++i)
        f[x][i]=g[cur][x][i];
}

class TurnOnLamps{
public:
    int minimize(vector <int> roads, string initState, string isImportant){
        n=roads.size()+1;
        memset(first,0,sizeof(first));
        tot=0;
        for (int i=0; i<n-1; ++i){
            int x=i+2, y=roads[i]+1;
            int c1=initState[i],c2=isImportant[i];
            add_edge(x,y,c1-'0',c2-'0');
            add_edge(y,x,c1-'0',c2-'0');	
        }
        memset(f,63,sizeof(f));
        dfs(1,0);
        return f[1][0];
    }
};
