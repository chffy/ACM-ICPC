#include<iostream>
#include<cstdio>
#include<cstring>
using namespace std;

typedef long long LL;

int f[51][51][2501];

const int P=1000000007;

class LittleElephantAndPermutationDiv1{
public:
    int getNumber(int N, int K){
        f[0][0][0]=1;
        for (int i=0; i<N; ++i)
            for (int j=0; j<N; ++j)
                for (int k=0; k<=2500; ++k)
                    if (f[i][j][k]>0){
                        int d=i*2-j;
                        if (k+i+1<=2500 && j+1<=N){
                            f[i+1][j+1][k+i+1]+=(LL)f[i][j][k]*(N-d)%P;
                            f[i+1][j+1][k+i+1]%=P;
                        }
                        f[i+1][j][k]+=(LL)f[i][j][k]*(N-d)*(N-d-1)%P;
                        f[i+1][j][k]%=P;
                        if (k+i+1<=2500 && j+1<=N){
                            f[i+1][j+1][k+i+1]+=(LL)f[i][j][k]*(i-j)*(N-d)*2%P;
                            f[i+1][j+1][k+i+1]%=P;
                        }
                        if (k+(i+1)*2 && j+2<=N){
                            f[i+1][j+2][k+(i+1)*2]+=(LL)f[i][j][k]*(i-j)*(i-j)%P;
                            f[i+1][j+2][k+(i+1)*2]%=P;
                        }
                    }
        int ans=0;
        for (int k=K; k<=2500; ++k)
            ans=(ans+f[N][N][k])%P;
        return ans;
    }
};
