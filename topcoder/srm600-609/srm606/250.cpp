#include<iostream>
#include<cstdio>
#include<cstring>
#include<string>
#include<vector>
using namespace std;

void swap(int &a,int &b){
	int t=a; a=b; b=t;
}

int abs(int x){ return x<0?-x:x; }

class EllysNumberGuessing{
public:
	int check(int x){
		if (x<1) return 0;
		if (x>1000000000) return 0;
		return 1;
	}

	int getNumber(vector <int> guesses, vector <int> answers){
		int n=guesses.size();
		int ans1=-answers[0]+guesses[0];
		int ans2=answers[0]+guesses[0];
		if (!check(ans1)) ans1=0;
		if (!check(ans2)) ans2=0;
		for (int i=1; i<n; ++i){
			if (ans1 && abs(ans1-guesses[i])!=answers[i]) ans1=0;
			if (ans2 && abs(ans2-guesses[i])!=answers[i]) ans2=0;
		}
		if (ans1 && ans2) return -1;
		if (!ans1 && !ans2) return -2;
		return ans1+ans2;
	}
};
