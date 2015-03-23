#include<iostream>
#include<cstdio>
#include<cstring>
#include<vector>
using namespace std;

int f[100][2300];

class TypoCoderDiv1{
public:
	int getmax(vector <int> D, int X){
		int n=D.size();
		for (int i=0; i<100; ++i)
			for (int j=0; j<2300; ++j) f[i][j]=-100000;
		f[0][X]=0;
		for (int i=0; i<n; ++i)
			for (int j=0; j<2200; ++j){
				int c=D[i];
				if (j+c<2200) f[i+1][j+c]=max(f[i+1][j+c],f[i][j]);
				f[i+1][max(0,j-c)]=max(f[i+1][max(0,j-c)],f[i][j]);
				if (i<n-1 && j+c>=2200 && j+c-D[i+1]<2200)
					f[i+2][max(j+c-D[i+1],0)]=max(f[i+2][max(j+c-D[i+1],0)],
								      f[i][j]+2);
			}
		int ans=0;
		for (int i=0; i<2200; ++i) {
			ans=max(ans,f[n][i]);
			if (i+D[n-1]>=2200) ans=max(ans,f[n-1][i]+1);
		}
		return ans;
	}
};
