#include<iostream>
#include<cstdio>
#include<cstring>
#include<vector>
using namespace std;

string s1,s2;
int a[1000],b[1000];

void input(const string &tree,int a[]){
    int n=0;
    for (int i=0; i<tree.size(); ){
        while (i<tree.size() && (tree[i]<'0'||tree[i]>'9')) ++i;
        if (i>=tree.size()) break;
        int k=0;
        while (i<tree.size() && tree[i]>='0' && tree[i]<='9') 
            k=k*10+tree[i++]-'0';
        a[n++]=k;
    }
}

int f[301][301],g[301][301];

class TreeUnion{
public:
    double expectedCycles(vector <string> tree1, vector <string> tree2, int K){
        s1=""; s2="";
        for (int i=0; i<tree1.size(); ++i)
            s1+=tree1[i];
        for (int i=0; i<tree2.size(); ++i)
            s2+=tree2[i];
        memset(a,-1,sizeof(a));
        memset(b,-1,sizeof(b));
        input(s1,a);
        input(s2,b);
        int n=0;
        for (int i=0; i<1000; ++i) 
            if (a[i]!=-1) ++n;
        ++n;
        memset(f,63,sizeof(f));
        memset(g,63,sizeof(g));
        for (int i=1; i<=n; ++i)
            f[i][i]=g[i][i]=0;
        for (int i=0; i<n-1; ++i){
            int x=i+2,y=a[i]+1;
            f[x][y]=f[y][x]=1;
            y=b[i]+1;
            g[x][y]=g[y][x]=1;
        }
        for (int k=1; k<=n; ++k)
            for (int i=1; i<=n; ++i)
                for (int j=1; j<=n; ++j){
                    f[i][j]=min(f[i][k]+f[k][j],f[i][j]);
                    g[i][j]=min(g[i][k]+g[k][j],g[i][j]);
                }
        double ans=0;
        memset(a,0,sizeof(a));
        memset(b,0,sizeof(b));
        for (int i=1; i<=K-2; ++i){
            a[i]=0;
            b[i]=0;
            for (int j=1; j<=n; ++j)
                for (int k=j+1; k<=n; ++k){
                    if (f[j][k]==i) ++a[i];
                    if (g[j][k]==i) ++b[i];
                }
        }
        for (int i=1; i<=K-2-1; ++i){
            int x=i,y=K-2-i;
            long long t=(long long)a[x]*b[y];
            double ans1=t*2;
            ans1=ans1/n/(n-1);
            ans+=ans1;
        }
        return ans;
    }
};
