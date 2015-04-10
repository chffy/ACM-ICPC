#include<iostream>
#include<cstdio>
#include<cstring>
#include<ctime>
#include<vector>
#include<cstdlib>
#define MAXN 3000
using namespace std;

double f[MAXN];
int a[MAXN];
double sum[MAXN];

void swap(int &a,int &b){
    int t=a; a=b; b=t;
}

double fabs(double x){
    return x<0?-x:x;
}

string S;

class TheSwapsDivOne{
public:
    double find(vector <string> sequence, int K){
        S="";
        for (int i=0; i<sequence.size(); ++i)
            S+=sequence[i];
        int n=S.size();
        for (int i=1; i<=n; ++i) a[i]=S[i-1]-'0';
        double p=1;
        for (int i=1; i<=K; ++i)
            p=p*(n-2)/n+(1-p)/(n-1)*2/n;
        double ans=0;
        double sum=0;
        for (int i=1; i<=n; ++i) sum=sum+a[i];
        for (int i=1; i<=n; ++i){
            ans+=(a[i]*p+(sum-a[i])*(1-p)/(n-1))*i*(n-i+1);
        }
        return ans/((double)n*(n+1)/2);
    }
};
