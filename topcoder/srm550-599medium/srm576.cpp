#include<iostream>
#include<cstdio>
#include<cstring>
#include<vector>
#include<algorithm>
using namespace std;

string S;
int a[1000],sum[1000];
int f[301][301],g[301][301],h[301][301];
const int p=1000000009;

class TheExperiment{
public:
    int countPlacements(vector <string> intensity, int M, int L, int A, int B){
        S="";
        for (int i=0; i<intensity.size(); ++i) S+=intensity[i];
        int n=S.size();
        for (int i=1; i<=n; ++i) a[i]=S[i-1]-'0';
        for (int i=1; i<=n; ++i) sum[i]=a[i];
        sum[0]=0;
        for (int i=1; i<=n; ++i) sum[i]+=sum[i-1];
        memset(f,0,sizeof(f));
        memset(g,0,sizeof(g));
        for (int i=0; i<=n; ++i)
            h[i][0]=1;
        for (int j=1; j<=M; ++j){
            for (int i=1; i<=n; ++i){
                h[i][j]=(h[i-1][j]+f[i-1][j])%p;
                for (int k=0; k<i; ++k){
                    if(sum[i]-sum[k]<A || sum[i]-sum[k]>B) continue;
                    if (i-k>L) continue;
                    if (i-k<L) g[i][j]=((g[i][j]+g[k][j-1])%p+h[k][j-1])%p;
                    if (i-k==L) f[i][j]=(f[i][j]+(g[k][j-1]+h[k][j-1])%p)%p;
                    f[i][j]=(f[i][j]+f[k][j-1])%p;
                }
                //printf("%d %d %d %d %d\n",i,j,f[i][j],h[i][j],g[i][j]);
            }
        }
        int ans=0;
        for (int i=1; i<=n; ++i)
            ans=(ans+f[i][M])%p;
        return ans;
    }
};
