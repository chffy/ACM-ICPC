#include<iostream>
#include<cstdio>
#include<cstring>
#include<vector>
#include<algorithm>
using namespace std;

typedef long long LL;

int bo[100],b[100];
pair<int,int> a[100],C[100],D[100];
LL f[53][53][53],g[53][53];
LL F[53][53][53];

class Excavations{
public:
    LL solve(int N,int K){
        int n=0,m=0;
        for (int i=0; i<N; ++i)
            if (bo[a[i].first]) C[n++]=a[i];
            else D[m++]=a[i];
        memset(f,0,sizeof(f));
        f[0][0][52]=1;
        for (int i=1; i<=m; ++i)
            for (int j=0; j<=K; ++j)
                for (int k=0; k<53; ++k){
                    if (f[i-1][j][k]==0) continue;
                    int d=min(k,D[i-1].second);
                    if (j<K) f[i][j+1][d]+=f[i-1][j][k];
                    f[i][j][k]+=f[i-1][j][k];
                }
        memset(g,0,sizeof(g));
        for (int j=0; j<=K; ++j)
            for (int k=0; k<53; ++k) {g[j][k]+=f[m][j][k]; }
        memset(F,0,sizeof(F));
        memset(f,0,sizeof(f));
        F[0][0][0]=1;
        for (int i=0; i<n; ++i)
            for (int j=0; j<=K; ++j)
                for (int k=0; k<53; ++k){
                    int d=max(k,C[i].second);
                    if (f[i][j][k]&&(i>0 && C[i].first==C[i-1].first)){
                        f[i+1][j][k]+=f[i][j][k];
                        if (j<K)F[i+1][j+1][d]+=f[i][j][k];
                    }
                    if (F[i][j][k]){
                        if (j<K){
                            if(i && C[i].first==C[i-1].first)
                                F[i+1][j+1][k]+=F[i][j][k];
                            else F[i+1][j+1][d]+=F[i][j][k];
                        }
                        if (i>0&&C[i].first==C[i-1].first)
                            F[i+1][j][k]+=F[i][j][k];
                        else f[i+1][j][k]+=F[i][j][k];
                    }
                }
        LL ans=0;
        for (int j=0; j<=K; ++j)
            for (int k1=0; k1<53; ++k1)
                for (int k2=k1+1; k2<53; ++k2)
                    ans+=F[n][j][k1]*g[K-j][k2];
        return ans;
    }

    LL count(vector <int> kind, vector <int> depth, vector <int> found, int K){
        int n=depth.size();
        for (int i=0; i<n; ++i) b[i]=depth[i];
        sort(b,b+n);
        int m=unique(b,b+n)-b;
        for (int i=0; i<n; ++i) depth[i]=lower_bound(b,b+m,depth[i])-b+1;
        memset(bo,0,sizeof(bo));
        for (int i=0; i<found.size(); ++i) bo[found[i]]=1;
        for (int i=0; i<n; ++i) a[i]=make_pair(kind[i],depth[i]);
        sort(a,a+n);
        return solve(n,K);
    }
}ZZ;
