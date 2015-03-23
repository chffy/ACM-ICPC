#include<iostream>
#include<cstdio>
#include<cstring>
using namespace std;

int f[2001][2048][2][2];
int edge[100000][2],mark[100000];
int tot;

const int P=1000000007;

class WinterAndSnowmen{
public:
	int getNumber(int N, int M){
		int ans=0;
		for (int l = 10; l >= 0; --l){
			memset(f,0,sizeof(f));
			f[0][0][0][0] = 1;
			int n = max(N,M);
			for (int i = 0; i < n; ++i)
				for (int j = 0; j < 2048; ++j)
					for (int k1 = 0; k1 < 2; ++k1)
						for (int k2 = 0; k2 < 2; ++k2){
							int k=((i+1)>>(l+1))^j;
							if (i<N){
								int p1=k1^(((i+1)&(1<<l))>0);
								f[i+1][k][p1][k2]=(f[i+1][k][p1][k2]+
										   f[i][j][k1][k2]);
								if (f[i+1][k][p1][k2]>P) f[i+1][k][p1][k2]-=P;
							}
							if (i<M){
								int p1=k2^(((i+1)&(1<<l))>0);
								f[i+1][k][k1][p1]=(f[i+1][k][k1][p1]+
										   f[i][j][k1][k2]);
								if (f[i+1][k][k1][p1]>P) f[i+1][k][k1][p1]-=P;
							}
							f[i+1][j][k1][k2]=(f[i+1][j][k1][k2]+
									   f[i][j][k1][k2]);
							if (f[i+1][j][k1][k2]>P) f[i+1][j][k1][k2]-=P;
						}
			ans=(ans+f[n][0][0][1]);
			if (ans>P) ans-=P;
		}
		return ans;
	}
}AB;
