#include<iostream>
#include<cstdio>
#include<cstring>
#include<vector>
using namespace std;

int d[1000];
class MaxMinTreeGame{
public:
	int findend(vector <int> edges, vector <int> costs){
		memset(d,0,sizeof(d));
		int n=costs.size();
		for (int i=0; i<n-1; ++i)
			++d[i+1],++d[edges[i]];
		int ans=-1;
		for (int i=0; i<n; ++i)
			if (d[i]==1) ans=max(ans,costs[i]);
		return ans;
	}
};
