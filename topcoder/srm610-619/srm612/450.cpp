#include<iostream>
#include<cstdio>
#include<cstring>
#include<algorithm>
#include<vector>
#include<queue>
using namespace std;

const int MAXN=200;
int c[MAXN],ss,tt;

void solve(vector <int> &x){
	int n=x.size();
	for (int i=0; i<n; ++i) c[i]=x[i];
	sort(c,c+n);
	int m=unique(c,c+n)-c;
	for (int i=0; i<n; ++i)
		x[i]=lower_bound(c,c+n,x[i])-c+1;
}

int first[MAXN],Next[100000],End[100000],w1[100000],w2[100000];
int tot=0;
int p1[MAXN],p2[MAXN],map[MAXN][MAXN];

void add_edge(int x,int y,int z1,int z2){
	Next[++tot]=first[x];
	first[x]=tot;
	End[tot]=y;
	w1[tot]=z1;
	w2[tot]=z2;
}

void add(int x,int y,int z1,int z2){
	//printf("%d %d %d %d\n",x,y,z1,z2);
	add_edge(x,y,z1,z2);
	add_edge(y,x,0,-z2);
}

int bo[MAXN],dis1[MAXN],dis2[MAXN],pre[MAXN],prd[MAXN];

queue <int> q;
int check(){
	for (int i=1; i<=tt; ++i)
		bo[i]=dis1[i]=0,dis2[i]=1000000;
	while (!q.empty()) q.pop();
	dis1[ss]=1000000;
	dis2[ss]=0;
	q.push(ss);
	while (!q.empty()){
		int x=q.front();
		q.pop();
		bo[x]=0;
		for (int k=first[x]; k!=-1; k=Next[k]){
			int l=End[k],s=dis2[x]+w2[k];
			if (w1[k] && dis2[l]>dis2[x]+w2[k]){
				dis2[l]=dis2[x]+w2[k];
				dis1[l]=min(w1[k],dis1[x]);
				pre[l]=x;  prd[l]=k;
				if (!bo[l]) q.push(l),bo[l]=1;
			}
		}
	}
	return dis1[tt];
}

void sd(int &ans){
	ans+=dis1[tt]*dis2[tt];
	for (int x=tt; x!=ss; x=pre[x]){
		w1[prd[x]]-=dis1[tt];
		w1[prd[x]^1]+=dis1[tt];
	}
}

class SpecialCells{
public:
	int guess(vector <int> x, vector <int> y){
		solve(x);
		solve(y);
		int n=x.size();
		ss=2*n+1;
		tt=ss+1;
		memset(first,-1,sizeof(first));
		tot=-1;
		memset(p1,0,sizeof(p1));
		memset(p2,0,sizeof(p2));
		memset(map,0,sizeof(map));
		for (int i=0; i<n; ++i) p1[x[i]]++,p2[y[i]]++;
		for (int i=0; i<n; ++i){ 
			map[x[i]][y[i]]=1;
			//printf("%d %d#%d\n",x[i],y[i],map[1][2]);
		}
		for (int i=1; i<=n; ++i)
			add(ss,i,p1[i],0),add(i+n,tt,p2[i],0);
		for (int i=1; i<=n; ++i)
			for (int j=1; j<=n; ++j)
				add(i,j+n,1,map[i][j]);
		int ans=0;
		while (check()) sd(ans);
		return ans;
	}
};
