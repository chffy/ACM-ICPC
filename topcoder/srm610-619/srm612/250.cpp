#include<iostream>
#include<cstdio>
#include<cstring>
#include<algorithm>
#include<queue>
using namespace std;

int f[2000],bo[2000];
queue <int> q;

class EmoticonsDiv1{
public:
	int printSmiles(int n){
		memset(f,63,sizeof(f));
		memset(bo,0,sizeof(bo));
		f[1]=0;
		for (int i=1; i<=n; ++i){
			int k=0;
			for (int j=1; j<=n; ++j)
				if (!bo[j] && f[j]<f[k]) k=j;
			if (k==0) break;
			bo[k]=1;
			if (k>1) f[k-1]=min(f[k]+1,f[k-1]);
			for (int j=1; j<=n; ++j){
				int l=k*j;
				if (l>n) 
					f[n]=min(f[n],f[k]+j+l-n);
				else f[l]=min(f[k]+j,f[l]);
			}
		}
		if (n==0) return 1;
		return f[n];
	}
};