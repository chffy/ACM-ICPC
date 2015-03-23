#include<iostream>
#include<cstdio>
#include<cstring>
#include<vector>
#include<algorithm>
using namespace std;

class WinterAndPresents{
public:
	long long getNumber(vector <int> apple, vector <int> orange){
		int n=apple.size();
		long long ans=0;
		int m=3000000;
		for (int i=0; i<n; ++i) m=min(m,apple[i]+orange[i]);
		sort(apple.begin(),apple.end());
		sort(orange.begin(),orange.end());
		int t1=0,t2=0;
		for (int i=1,j=0,k=0; i<=m; ++i){
			while (j<n && apple[j]<i) t1+=apple[j++];
			while (k<n && orange[k]<i) t2+=orange[k++];
			int k1=t1+(n-j)*i,k2=t2+(n-k)*i;
			k2=i*n-k2;
			ans=ans+k1-k2+1;
		}
		return ans;
	}
};
