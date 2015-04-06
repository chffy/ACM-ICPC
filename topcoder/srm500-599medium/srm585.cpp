#include<iostream>
#include<cstdio>
#include<cstring>
#include<vector>
using namespace std;

int f[37][2000];
typedef long long LL;
const int P=1000000007;
int CC[2000][40];
int F[2000][40],G[2000][40];
int sum[200];

class LISNumber{
public:
    int count(vector <int> ca, int K){
        memset(f,0,sizeof(f));
        int n=ca.size();
        sum[0]=0;
        for (int i=1; i<=n; ++i) sum[i]=sum[i-1]+ca[i-1];
        f[1][ca[0]]=1;
        CC[0][0]=1;
        for (int i=1; i<2000; ++i)
            for (int j=0; j<40; ++j)
                CC[i][j]=(j==0)?1:(CC[i-1][j]+CC[i-1][j-1])%P;
        memset(F,0,sizeof(F));
        memset(G,0,sizeof(G));
        F[0][0]=G[0][0]=1;
        for (int i=1; i<2000; ++i)
            for (int j=0; j<40; ++j)
                for (int k=0; k<=j; ++k){
                    F[i][j]=(F[i][j]+F[i-1][j-k])%P;
                    if (k) G[i][j]=(G[i][j]+G[i-1][j-k])%P;
                }
        for (int i=1; i<n; ++i)
            for (int j=1; j<=K; ++j){
                if (!f[i][j]) continue;
                int m=ca[i];
                for (int k=0; k<=min(j,m); ++k){
                    int J=m-k+j;
                    if (J>K) continue;
                    for (int l=k; l<=m; ++l){
                        int a=l,b=m-l;
                        a=(LL)G[k][l]*CC[j][k]%P;
                        b=F[sum[i]+1-j][b];
                        a=(LL)a*b%P;
                        a=(LL)a*f[i][j]%P;
                        f[i+1][J]=(f[i+1][J]+a)%P;
                    }
                }
            }
        return f[n][K];
    }
};
