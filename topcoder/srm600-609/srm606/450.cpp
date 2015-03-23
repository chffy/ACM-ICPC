#include<iostream>
#include<cstdio>
#include<cstring>
#include<vector>
using namespace std;

void solve(int& ans,int& sum,int x){
	if (x==ans){
		++sum;
		return ;
	}
	if (sum==0){
		ans=x;
		sum=1;
		return ;
	}
	--sum;
}

class EllysPairing{
public:
	int getMax(int m, vector <int> count, vector <int> first, vector <int> mult, vector <int> add){
		int ans1=0,sum1=0;
		int n=count.size();
		for (int i=0; i<n; ++i){
			int x=first[i];
			solve(ans1,sum1,x);
			for (int j=1; j<count[i]; ++j){
				long long y=x;
				y=(y*mult[i])&(long long)(m-1);
				x=(y+add[i])&(m-1);
				solve(ans1,sum1,x);
			}
		}
		int T=0;
		sum1=0;
		for (int i=0; i<n; ++i){
			T+=count[i];
			int x=first[i];
			if (x==ans1) ++sum1;
			for (int j=1; j<count[i]; ++j){
				long long y=x;
				y=(y*mult[i])&(long long )(m-1);
				x=(y+add[i])&(m-1);
				if (x==ans1) ++sum1;
			}
		}
		if (sum1>=T-sum1) return T-sum1;
		return T/2;
	}
};