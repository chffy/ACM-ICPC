#include<iostream>
#include<cstdio>
#include<cstring>
#include<string>
#include<vector>
using namespace std;

const int MAXN=2510;
string S1,S2;
int num[MAXN],sum[MAXN];
int a1[MAXN],a2[MAXN];
int f[40000],g[40000];
const int ZERO=20000;

class CombinationLockDiv1{
public:
	int minimumMoves(vector <string> P, vector <string> Q){
		int n=P.size();
		S1="";
		for (int i=0; i<n; ++i) S1+=P[i];
		n=Q.size();
		S2="";
		for (int i=0; i<n; ++i) S2+=Q[i];
		n=S1.size();
		for (int i=0; i<n; ++i) num[i]=S1[i]-S2[i];
		for (int i=1; i<=n; ++i) sum[i]=num[i]-num[i-1];
		sum[0]=num[0];
		if (n==0) return 0;
		for (int i=0; i<=n; ++i){
			while (sum[i]<0) sum[i]+=10;
			while (sum[i]>10) sum[i]-=10;
			a1[i]=10-sum[i];
			a2[i]=sum[i];
		}
		memset(f,63,sizeof(f));
		f[ZERO-a1[0]]=a1[0];
		f[ZERO+a2[0]]=a2[0];
		for (int i=0; i<n; ++i){
			memset(g,63,sizeof(g));
			for (int j=0; j<40000; ++j){
				if (j-a1[i+1]>=0) g[j-a1[i+1]]=min(g[j-a1[i+1]],f[j]+a1[i+1]);
				if (j+a2[i+1]<40000) g[j+a2[i+1]]=min(g[j+a2[i+1]],f[j]+a2[i+1]);
			}
			memcpy(f,g,sizeof(f));
		}
		//for (int i=0; i<=n; ++i) printf("%d %d\n",a1[i],a2[i]);
		return f[ZERO]/2;
	}
};
