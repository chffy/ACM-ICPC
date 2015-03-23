#include<iostream>
#include<cstdio>
#include<cstring>
#include<algorithm>
using namespace std;
 
int xx[100010],yy[100010];
 
class PackingBallsDiv1{
public:
    int minPacks(int K, int A, int B, int C, int D){
	xx[0]=A;
	for (int i=1; i<K; ++i){
	    long long k=xx[i-1];
	    k=(k*B+C)%D+1;
	    xx[i]=k;
	}
	long long ans=0;
	for (int i=0; i<K; ++i){
	    ans=ans+(xx[i]-1)/K+1;
	    yy[i]=(xx[i]-1)%K+1;
	}
	sort(yy,yy+K);
	long long ans1=0;
	for (int i=0; i<K; ++i) ans1=min(ans1,(long long)yy[i]-i-1);
	return (int)(ans+ans1);
    }
};
