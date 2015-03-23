#include<iostream>
#include<cstdio>
#include<cstring>
#include<vector>
#include<string>
using namespace std;

const int MAXN=101;
int f1[MAXN][MAXN],f[MAXN][MAXN];
class TheMatrix{
public:
	int MaxArea(vector <string> board){
		int n=board.size();
		int m=board[0].size();
		for (int i=0; i<n; ++i)
			for (int j=0; j<m; ++j){
				f1[i][j]=i;
				if (i && board[i-1][j]!=board[i][j]) f1[i][j]=f1[i-1][j];
			}
		int ans=0;
		for (int i=0; i<n; ++i)
			for (int j=i; j<n; ++j)
				for (int k=0,k1=0; k<m; ++k){
					if (f1[j][k]>i) {
						k1=k+1;
						continue;
					}
					if ( k && board[j][k]==board[j][k-1]) k1=k;
					ans=max(ans,(j-i+1)*(k-k1+1));
				}
		return ans;
	}
};