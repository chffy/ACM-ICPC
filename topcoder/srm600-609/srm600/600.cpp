#include<iostream>
#include<cstring>
#include<string>
#include<cstdio>
#include<vector>
using namespace std;

int map[100],value[100][1000],sum;
int p[1000],c[20];

int check(int opt,int n){
	for (int i=0,j=n-1; i<j; ++i,--j){
		if (((opt & (1<<i))>0) != 
		    ((opt & (1<<j))>0)) return 0;
	}
	return 1;
}

int calc_num(int x){
	int ans=0;
	for ( ; x; x-=x & (-x)) ++ans;
	return ans;
}

int f[20][20],t[1000000];

class PalindromeMatrix{
public:
	int minChange(vector <string> A, int N, int M){
		int n=A.size();
		int m=A[0].size();
		memset(map,0,sizeof(map));
		for (int i=0; i<m; ++i)
			for (int j=0; j<n; ++j)
				map[i]|=(A[j][i]-48)<<j;
		sum=0;
		for (int i=0; i<(1<<n); ++i) 
			if (check(i,n)) p[sum++]=i;
		for (int i=0; i<m; ++i) 
			for (int j=0; j<sum; ++j)
				value[i][j]=calc_num(map[i] ^ p[j]);
		for (int i=0; i<(1<<n); ++i) t[i]=calc_num(i);
		int ans=n*m*10;
		for (int opt=0; opt<(1<<n); ++opt)
			if (t[opt]==N){
				for (int i=0; i<=m; ++i)
					for (int j=0; j<=m; ++j) f[i][j]=n*m*10;
				f[0][0]=0;
				for (int i=1; i<=m/2; ++i) c[i]=ans*10;
				for (int k=0; k<sum; ++k)
					for (int l=0; l<sum; ++l)
						if ((p[k] & opt)==(p[l] & opt))
							for (int i=1; i<=m/2; ++i)
								c[i]=min(c[i],value[i-1][k]+value[m-i][l]);
					for (int i=1; i<=m/2; ++i)
					for (int j=0; j<=M; ++j){
						if (f[i-1][j]<ans)
							for (int k=opt; ; k=(k-1)&opt){
							int l0=t[(k^map[i-1])&opt]+
								t[(k^map[m-i])&opt];
							f[i][j]=min(f[i][j],f[i-1][j]+l0);
							if (k==0) break;
							}
						if (j>0 && f[i-1][j-1]<ans)
						for (int k=0; k<sum; ++k){
							int opt1=p[k] & opt;
							int l0=value[i-1][k]
								+t[(opt1^map[m-i])&opt];
							int l1=value[m-i][k]
								+t[(opt1^map[i-1])&opt];
							f[i][j]=min(f[i][j],f[i-1][j-1]+min(l0,l1));
						}
						if (j>1 && f[i-1][j-2]<ans)
							f[i][j]=min(f[i][j],f[i-1][j-2]+c[i]);
							       
					}
				ans=min(ans,f[m/2][M]);
			}
		return ans;
	}
}ABC;
