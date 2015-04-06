#include<iostream>
#include<cstring>
#include<cstdio>
#include<vector>
using namespace std;


typedef long long LL;
string s1,s2;
int a[10000];
const int P=1000000009;
int f[1300][1300];
int sum[1300];
int mark[1300][3000];
int Next[1300];
int xc[1300][1300];


void swap(int &a,int &b){
    int t=a; a=b; b=t;
}

int solve(char ch){
    if (ch>='a' && ch<='z') return ch-'a';
    return ch-'A'+26;
}

class ColorfulBuilding{
public:
    int count(vector <string> c1, vector <string> c2, int L){
        int n=0;
        s1="";  s2="";
        for (int i=0; i<(int)c1.size(); ++i) s1+=c1[i];
        for (int i=0; i<(int)c2.size(); ++i) s2+=c2[i];
        n=s1.size();
        for (int i=1; i<=n; ++i){
            int x1=solve(s1[i-1]),
                x2=solve(s2[i-1]);
            a[i]=x1*52+x2;
        }
        for (int i=1; n-i+1>i; ++i)
            swap(a[i],a[n-i+1]);
        memset(f,0,sizeof(f));
        memset(sum,0,sizeof(sum));
        memset(mark,0,sizeof(mark));
        memset(Next,0,sizeof(Next));
        for (int i=1; i<=n; ++i)
            for (int j=1; j<i; ++j)
                if (a[j]==a[i]) Next[i]=j;
        for (int i=1; i<=n; ++i){
            xc[i][i]=i;
            for (int j=i+1; j<=n; ++j)
                xc[i][j]=((LL)xc[i][j-1])*j%P;
        }
        f[0][0]=1;
        sum[0]=1;
        for (int i=1; i<=n; ++i){
            if (Next[i]<=i-2)
                for (int j=1; j<=L; ++j)
                    mark[j][a[i]]=((LL)mark[j][a[i]])*xc[Next[i]][i-2]%P;
            for (int j=1; j<=L; ++j){
                f[i][j]=sum[j-1]-mark[j-1][a[i]]+P;
                f[i][j]%=P;
                f[i][j]+=mark[j][a[i]];
                f[i][j]%=P;
            }
            for (int j=1; j<=L; ++j)
                mark[j][a[i]]=((LL)mark[j][a[i]])*(i-1)%P;
            for (int j=0; j<=L; ++j)
                sum[j]=((LL)sum[j])*(i-1)%P;
            for (int j=1; j<=L; ++j)
                sum[j]=(sum[j]+f[i][j])%P;
            for (int j=1; j<=L; ++j){
                mark[j][a[i]]+=f[i][j];
                mark[j][a[i]]%=P;
            }
        }
        return sum[L];
    }
};
