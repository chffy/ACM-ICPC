#include<iostream>
#include<cstdio>
#include<cstring>
#include<vector>
#include<string>
using namespace std;

string S;

double calc(int l,int r,int n){
	double ans=1,ans1=0;
	while (l-1>=0 && r+1<n){
		if (S[l-1]!=S[r+1])
			if (S[l-1]!='?' && S[r+1]!='?') return ans1;
		if ((S[l-1]=='?' || S[r+1]=='?') && l-1!=r+1)
			ans=ans/26;
		ans1=ans1+ans;
		--l;
		++r;
	}
	return ans1;
}

class PalindromicSubstringsDiv1{
public:
	double expectedPalindromes(vector <string> S1, vector <string> S2){
		S="";
		int n=S1.size();
		for (int i=0; i<n; ++i) S+=S1[i];
		n=S2.size();
		for (int i=0; i<n; ++i) S+=S2[i];
		double ans=0;
		n=S.size();
		for (int i=0; i<n; ++i){
			ans+=calc(i+1,i-1,n);
			ans+=calc(i+1,i,n);
		}
		return ans;
	}
};
