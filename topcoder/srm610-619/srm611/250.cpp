#include<iostream>
#include<cstdio>
#include<cstring>
#include<algorithm>
#include<vector>
using namespace std;

const int MAXN=100;
int a[MAXN],b[MAXN];
int bo[40000];

int gcd(int a,int b){
	return (b==0)?a:gcd(b,a%b);
}

class LCMSet{
public:
	string equal(vector <int> A, vector <int> B){
		int n1=A.size(),n2=B.size();
		for (int i=0; i<n1; ++i){
			int k=1;
			for (int j=0; j<n2; ++j){
				if (A[i]%B[j]!=0) continue;
				int z=gcd(k,B[j]);
				z=B[j]/z;
				k=k*z;
			}
			if (k!=A[i]) return "Not equal";
		}
		for (int i=0; i<n2; ++i){
			int k=1;
			for (int j=0; j<n1; ++j){
				if (B[i]%A[j]!=0) continue;
				int z=gcd(k,A[j]);
				z=A[j]/z;
				k=k*z;
			}
			if (k!=B[i]) return "Not equal";
		}
		return "Equal";
	}
};
