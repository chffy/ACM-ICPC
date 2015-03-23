#include<iostream>
#include<cstdio>
#include<cstring>
#include<vector>
using namespace std;

int f[100][100];
int size1[100],size2[100];
int bo[100];
int a[100],tot=0;
int first[100],Next[200],End[200];

void add_edge(int x,int y){
	Next[++tot]=first[x];
	first[x]=tot;
	End[tot]=y;
}

int ans=10000000;

int g[100][100];

int abs(int x) { return x<0?-x:x; }

void dfs(int x,int fa){
	size1[x]=1;
	size2[x]=bo[x];
	for (int k=first[x]; k; k=Next[k]){
		int l=End[k];
		if (l==fa) continue;
		dfs(l,x);
		size1[x]+=size1[l];
		size2[x]+=size2[l];
	}
	int p=0;
	for (int k=first[x]; k; k=Next[k])
		if (End[k]!=fa) a[++p]=End[k]; 
	if (size1[x]==1){
		f[x][0]=0;
		if (bo[x]) f[x][1]=0;
		return ;
	}
	memset(g,63,sizeof(g));
	g[0][0]=0;
	for (int i=1; i<=p; ++i)
		for (int j=0; j<=size1[x]; ++j)
			for (int k=0; k<=j; ++k){
				g[i][j]=min(g[i][j],g[i-1][j-k]+abs(size2[a[i]]-k)+f[a[i]][k]);
			}
	f[x][0]=g[p][0];
	for (int i=1; i<=size1[x]; ++i)
		f[x][i]=g[p][i-1];
}

class FoxConnection{
public:
	int minimalDistance(vector <int> A, vector <int> B, string haveFox){
		memset(bo,0,sizeof(bo));
		int n=haveFox.size();
		for (int i=0; i<n-1; ++i){
			add_edge(A[i],B[i]);
			add_edge(B[i],A[i]);
		}
		for (int i=0; i<n; ++i)
			if (haveFox[i]=='Y') bo[i+1]=1;
		for (int i=1; i<=n; ++i){
			memset(f,63,sizeof(f));
			memset(size1,0,sizeof(size1));
			memset(size2,0,sizeof(size2));
			dfs(i,0);
			//printf("%d %d %d\n",i,size2[i],f[3][size2[3]]);
			ans=min(ans,f[i][size2[i]]);
		}
		return ans;
	}
};
