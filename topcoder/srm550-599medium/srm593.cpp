#include<iostream>
#include<cstdio>
#include<cstring>
#include<vector>
using namespace std;

const int MAXN=500001;

int f[2][MAXN];

void swap(int &a,int &b){
    int t=a; a=b; b=t;
}

const int ZERO=250000;
class MayTheBestPetWin{
public:
    int calc(vector <int> A, vector <int> B){
        memset(f,63,sizeof(f));
        int n=A.size();
        int cur=0,nex=1;
        f[0][ZERO]=0;
        for (int i=0; i<n; ++i){
            for (int j=0; j<MAXN; ++j)
                if (f[cur][j]<MAXN){
                    //printf("%d %d %d\n",i,j-ZERO,f[cur][j]);
                    if (j+B[i]<MAXN) 
                        f[nex][j+B[i]]=min(f[nex][j+B[i]],f[cur][j]-A[i]);
                    if (j-A[i]>=0)
                        f[nex][j-A[i]]=min(f[nex][j-A[i]],f[cur][j]+B[i]);
                }
            for (int j=0; j<MAXN; ++j)
                f[cur][j]=100000000;
            swap(cur,nex);
        }
        int ans=10000000;
        for (int i=0; i<MAXN; ++i)
            ans=min(ans,max(i-ZERO,f[cur][i]));
        return ans;
    }
};
