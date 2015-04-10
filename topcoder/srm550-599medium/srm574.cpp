#include<iostream>
#include<cstdio>
#include<cstring>
#include<vector>
using namespace std;

typedef long long LL;

LL f[1<<18][20];

void swap(int &a,int &b){
    int t=a; a=b; b=t;
}

int check(int opt,int i,int j){
    int t1=0,t2=0;
    if (i>j) swap(i,j);
    if (opt & ((1<<(i-1))-1)) t1=1;
    if (opt>>j) t1=1;
    if ((opt>>i) & ((1<<(j-i-1))-1)) t2=1;
    return t1 && t2;
}

class PolygonTraversal{
public:
    LL count(int n, vector <int> points){
        int m=points.size();
        memset(f,0,sizeof(f));
        int t=0;
        for (int i=0; i<m; ++i)
            t+=1<<(points[i]-1);
        f[t][points[m-1]]=1;
        for (int i=t; i<(1<<n); ++i)
            for (int j=1; j<=n; ++j){
                if (!f[i][j]) continue;
                for (int k=1; k<=n; ++k){
                    if ((i>>(k-1)) & 1) continue;
                    if (!check(i,j,k)) continue;
                    f[i | (1<<(k-1))][k]+=f[i][j];
                }
            }
        LL ans=0;
        for (int i=1; i<=n; ++i){
            if (i%n+1==points[0]) continue;
            if ((i-2+n)%n+1==points[0]) continue;
            ans+=f[(1<<n)-1][i];
        }
        return ans;
    }
};
