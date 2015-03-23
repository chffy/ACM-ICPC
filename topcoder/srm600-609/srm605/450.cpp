#include<iostream>
#include<cstdio>
#include<cstring>
#include<vector>
using namespace std;

int f[101][101][1000];
int g[51];

const int P=1000000007;
int c[101][101];

int find(int x,int y){
	c[0][0]=1;
	for (int i=1; i<=x; ++i)
		for (int j=0; j<=min(i,y); ++j)
			c[i][j]=(j==0)?1:(c[i-1][j]+c[i-1][j-1])%P;
	return c[x][y];
}

class AlienAndSetDiv1{
public:
	int getNumber(int N, int K){
		if (K==1) return find(2*N,N);
		N*=2;
		memset(f,0,sizeof(f));
		f[0][0][0]=1;
		--K;
		int m=(1<<K)-1;
		for (int i=0; i<N; ++i)
			for (int j=0; j<=i; ++j)
				for (int k=0; k<=m; ++k)
					if (f[i][j][k]){
						int z=0,opt=((k<<1)+1) & m;
						if ((k & (1<<(K-1)))>0) ++z;
						f[i+1][j+z][opt]=(f[i+1][j+z][opt]+f[i][j][k])%P;
						opt=(k<<1) & m;
						if (j>0)
							f[i+1][j+z-1][opt]=(f[i+1][j+z-1][opt]+f[i][j][k])%P;
					}
		memset(g,0,sizeof(g));
		g[0]=1;
		N/=2;
		for (int i=1; i<=N; ++i)
			for (int j=0; j<i; ++j)
				g[i]=(g[i]+(long long)g[j]*f[(i-j)*2][0][0] %P)%P;
		return g[N]*2%P;
	}
};
