#include<iostream>
#include<cstdio>
#include<cstring>
#include<algorithm>
using namespace std;

struct point{
	int a, b;
	int operator<(const point &A) const {
		return b>A.b;
	}
};

const int MAXN=100;
point a[MAXN];
int f[5001];

class AlbertoTheAviator{
public:
	int MaximumFlights(int F, vector <int> duration, vector <int> refuel){
		int n=duration.size();
		for (int i=0; i<n; ++i) 
			a[i].a=duration[i],a[i].b=refuel[i];
		
		sort(a,a+n);
		memset(f,0,sizeof(f));
		for (int i=0; i<n; ++i)
			for (int j=a[i].a; j<=F; ++j)
				f[j-a[i].a+a[i].b]=max(f[j-a[i].a+a[i].b],f[j]+1);
		int ans=0;
		for (int i=0; i<=F; ++i) ans=max(ans,f[i]);		
		return ans;
	}
};