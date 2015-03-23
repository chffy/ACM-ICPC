#include<iostream>
#include<cstdio>
#include<cstring>
#include<vector>
#include<algorithm>
#include<cstdlib>
#include<ctime>
using namespace std;

int cmp(const int &a,const int &b){
	return a>b;
}

class MysticAndCandies{
public:
	int minBoxes(int C, int X, vector <int> low, vector <int> high){
		int n=high.size();
		sort(low.begin(),low.end(),cmp);
		sort(high.begin(),high.end());
		int ans1=n,ans2=n;
		for (int i=0,t=0; i<n; ++i){
			t+=low[i];
			if (t>=X) {
				ans1=i+1;
				break;
			}
		}
		for (int i=0,t=0; i<n; ++i){
			t+=high[i];
			if (C-t>=X){
				ans2=n-i-1;
			}
		}
		return min(ans1,ans2);
	}
};
