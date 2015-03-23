#include<iostream>
#include<cstdio>
#include<cstring>
#include<vector>
using namespace std;

int bo[100];

int lowbit(int x){ return x & -x; }

class ORSolitaire{
public:
	int getMinimum(vector <int> a, int goal){
		memset(bo,0,sizeof(bo));
		int n=a.size();
		for (int i=0; i<n; ++i)
			if ((a[i] & goal)!=a[i]) bo[i]=1;
		int ans=10000;
		for (; goal; goal-=lowbit(goal)){
			int x=lowbit(goal);
			int ans1=0;
			for (int i=0; i<n; ++i)
				if (!bo[i] && ((x & a[i])>0)) ++ans1;
			ans=min(ans1,ans);
		}
		return ans;
	}
};
