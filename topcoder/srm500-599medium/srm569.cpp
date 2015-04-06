#include<iostream>
#include<cstdio>
#include<cstring>
#include<vector>
using namespace std;

typedef long long LL;
int n,k;
LL a[100],b[100];
LL ans;

void dfs(int x,LL s){
    if (a[x-1]<0) return ;
    if (x==n){
        ans=min(ans,s+(a[n-1]+k-1)/k);
        return ;
    }
    int L=a[x-1]%k;
    int R=k-L;
    L=min(L,(int)b[x-1]);
    a[x-1]-=L; a[x]+=L;
    dfs(x+1,s+(a[x-1]+k-1)/k);
    a[x-1]+=L; a[x]-=L;
    R=min((int)b[x],R);
    a[x-1]+=R; a[x]-=R;
    b[x]-=R;
    dfs(x+1,s+(a[x-1]+k-1)/k);
    b[x]+=R;
    a[x-1]-=R; a[x]+=R;
}

class TheJediTest{
public:
    int minimumSupervisors(vector <int> students, int K){
        n=students.size();
        k=K;
        for (int i=0; i<n; ++i) a[i]=b[i]=students[i];
        ans=1LL<<(LL)60;
        dfs(1,0);
        return (int)ans;
    }
};
