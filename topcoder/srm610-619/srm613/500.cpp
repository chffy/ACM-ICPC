#include<iostream>
#include<cstdio>
#include<cstring>
using namespace std;

int f[200000],sum[200000];
const int P=1000000007;

int find(int t, int x){
	if (x==0) return 1;
	if (x==1) return t;
	int z=find(t,x>>1);
	z=(long long)z*z%P;
	if (x%2==1) z=(long long)z*t%P;
	return z;
}

class RandomGCD{
public:
	int countTuples(int N, int K, int low, int high){
		int ll=-1,rr=-1;
		for (int i=low; i<=high; ++i)
			if (i%K==0) {
				ll=i/K;
				break;
			}
		for (int i=high; i>=low; --i)
			if (i%K==0){
				rr=i/K;
				break;
			}
		if (ll==-1) return 0;
		for (int i=1; i<=100000; ++i){
			int k=(ll-1)/i+1,l=rr/i;
			if (l>=k) sum[i]=l-k+1;
		}
		for (int i=ll; i<=rr; ++i)
			if (i<=100000) ll=i+1;
		for (int i=100000; i>0; --i){
			//printf("%d\n",sum[i]);
		//	if (sum[i]) printf("%d %d\n",i,sum[i]);
			f[i]=find(sum[i],N);
			for (int j=i*2; j<=100000; j+=i) f[i]=(f[i]-f[j])%P;
			int k=(ll-1)/i+1,l=rr/i;
			if (l>=k) f[i]=(f[i]-(l-k+1))%P;
			//for (int j=k; j<=l; ++j) f[i]=(f[i]-1)%P;
		}
		return (f[1]+P)%P;
	}
};