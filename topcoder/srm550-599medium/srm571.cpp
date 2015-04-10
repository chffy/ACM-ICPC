#include<iostream>
#include<cstdio>
#include<cstring>
#include<vector>
using namespace std;

int m,N;
int m1[10000],m2[10000];
int ans;
int a[10000];
int bo[10000];

void dfs(int x,int n,int s){
    if (n>N) return ;
    if (x>m){
        ans=min(ans,s);
        return ;
    }
    if (bo[m1[x]] || bo[m2[x]])
        dfs(x+1,n,s);
    else {
        bo[m1[x]]=1;
        dfs(x+1,n+1,s+a[m1[x]]);
        bo[m2[x]]=1;
        bo[m1[x]]=0;
        dfs(x+1,n+1,s+a[m2[x]]);
        bo[m2[x]]=0;
    }
}

class MagicMolecule{
public:
    int maxMagicPower(vector <int> magicPower, vector <string> magicBond){
        int n=magicPower.size();
        m=0;
        for (int i=0; i<n; ++i)
            for (int j=i+1; j<n; ++j){
                if (magicBond[i][j]=='N'){
                    ++m;
                    m1[m]=i+1;
                    m2[m]=j+1;
                }
            }
        ans=1000000000;
        for (int i=1; i<=n; ++i) a[i]=magicPower[i-1];
        N=n/3;
        memset(bo,0,sizeof(bo));
        dfs(1,0,0);
        if (ans==1000000000) return -1;
        ans=-ans;
        for (int i=1; i<=n; ++i) ans+=a[i];
        //printf("%d\n",N);
        return ans;
    }
};
