#include<iostream>
#include<cstdio>
#include<cstring>
#include<vector>
#include<algorithm>
using namespace std;

int f[200];

class AlienAndHamburgers{
public:
	int getNumber(vector <int> type, vector <int> taste){
		int n=type.size();
		for (int i=0; i<=100; ++i) f[i]=-200000;
		for (int i=0; i<n; ++i)
			f[type[i]]=max(f[type[i]],max(f[type[i]]+taste[i],taste[i]));
		sort(f,f+101);
		int ans=0,ans1=0;
		for (int i=100; i>=1; --i){
			ans1+=f[i];
			if (f[i]<-150000) break;
			ans=max(ans1*(101-i),ans);
		}  
		return ans;
	}
};
