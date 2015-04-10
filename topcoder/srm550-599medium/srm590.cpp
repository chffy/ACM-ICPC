#include<iostream>
#include<cstdio>
#include<cstring>
#include<vector>
using namespace std;

typedef long long LL;

int a[63][63],b[63];
int map[63][63],c[63][63];

int check(int n,int m){
    for (int i=1; i<n; ++i){
        int z1=-1;
        for (int j=0; j<m; ++j)
            if (c[i][j]) {
                z1=j;
                break;
            }
        if (z1==-1) continue;
        if (c[n][z1]==0) continue;
        for (int j=0; j<=m; ++j)
            c[n][j]^=c[i][j];
    }
    int z1=-1;
    for (int i=0; i<m; ++i)
        if (c[n][i]){ 
            z1=i; 
            break;
        }
    if (z1==-1 && c[n][m]) return 0;
    if (z1==-1) return 1;
    for (int i=1; i<n; ++i){
        if (!c[i][z1]) continue;
        for (int j=0; j<=m; ++j)
            c[i][j]^=c[n][j];
    }
    for (int i=1; i<=n; ++i){
        int z1=-1;
        for (int j=0; j<m; ++j)
            if (c[i][j]) z1=j;
        if (z1==-1 && c[i][m]) return 0;
    }
    return 1;
}

LL find(LL x,int n){
    LL ans=1,z=x;
    for (;n; n>>=1,z*=z)
        if (n & 1) ans*=z;
    return ans;
}

LL calc(int n,int m){
    int p=0;
    for (int i=1; i<=n; ++i){
        int z1=-1;
        for (int j=0; j<m; ++j)
            if (c[i][j]) z1=j;
        if (z1!=-1) ++p; 
    }
    p=m-p;
    return find(2,p);
}

class XorCards{
public:
    LL numberOfWays(vector<LL> number,LL limit){
        int n=number.size();
        LL ans=0;
        for (int I=60; I>=0; --I){
            int n1=61-I;
            LL C=((LL)1)<<(LL(I));
            for (int i=0; i<n; ++i)
                if (number[i] & C) b[i]=1;
                else b[i]=0;
            if ((limit & C)) b[n]=1;
            else b[n]=0;
            memcpy(c,map,sizeof(map));
            for (int i=0; i<n; ++i) c[n1][i]=b[i];
            c[n1][n]=0;
            if (b[n]==0){
                if (!check(n1,n)) break;
                if (I==0) ans=ans+calc(n1,n);
                memcpy(map,c,sizeof(map));
                continue;
            }
            if (check(n1,n))
                ans=ans+calc(n1,n);
            memcpy(c,map,sizeof(map));
            for (int i=0; i<n; ++i) c[n1][i]=b[i];
            c[n1][n]=1;
            if (!check(n1,n)) break;
            if (I==0) ans=ans+calc(n1,n); 
            memcpy(map,c,sizeof(map));
        }
		
        return ans;
    }
};
