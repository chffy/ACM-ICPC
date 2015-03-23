#include<iostream>
#include<cstdio>
#include<cstring>
#include<algorithm>
using namespace std;

int a[100000],b[100000];
const int P=1000000007;
typedef long long LL;

int power(int x,int n){
	int z=x,ans=1;
	for (; n; n>>=1,z=(LL)z*z%P)
		if (n & 1) ans=(LL)ans*z%P;
	return ans;
}

class PairsOfStrings{
public:
	int getNumber(int n, int k){
		int m=0; 
		for (int i=1; i*i<=n; ++i)
			if (n%i==0){
				a[m++]=i;
				if (i*i!=n) a[m++]=n/i;
			}
		sort(a,a+m);
		int ans=0;
		for (int i=0; i<m; ++i){
			int mark=power(k,a[i]);
			for (int j=0; j<i; ++j)
				if (a[i] % a[j] == 0) mark = (mark - b[j] ) % P;
			b[i] = mark;
			ans = (ans + (LL)a[i] * mark % P) % P;
		}
		return (ans + P) % P; 
	}
};
