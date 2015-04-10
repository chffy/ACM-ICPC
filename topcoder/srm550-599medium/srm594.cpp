#include<iostream>
#include<cstdio>
#include<cstring>
#include<vector>
using namespace std;

const int MAXN=3000;
int first[MAXN],Next[MAXN*10],End[MAXN];
int bb[MAXN],bo[MAXN],my[MAXN];
int mark[100][100];
int tot;
const int c[4]={0,0,1,-1};
const int d[4]={1,-1,0,0};

void add_edge(int x,int y){
    //printf("%d %d\n",x,y);
    Next[++tot]=first[x];
    first[x]=tot;
    End[tot]=y;
}

int check(int x){
    for (int k=first[x]; k ; k=Next[k])
        if (!bo[End[k]]){
            bo[End[k]]=1;
            if (!my[End[k]] || check(my[End[k]])){
                my[End[k]]=x;
                return 1;
            }
        }
    return 0;
}

class FoxAndGo3{
public:
    int maxEmptyCells(vector <string> b){
        memset(bo,0,sizeof(bo));
        memset(first,0,sizeof(first));
        tot=0;
        int FA=0;
        int n=b.size(), m=b[0].size();
        int ans=0;
        memset(my,0,sizeof(my));
        memset(bb,0,sizeof(bb));
        for (int i=0; i<n; ++i)
            for (int j=0; j<m; ++j){
                if (b[i][j]=='.' || b[i][j]=='o') ++ans;
                if (b[i][j]=='.' || b[i][j]=='x') continue;
                int x=++FA;
                bb[x]=1;
                for (int k=0; k<4; ++k){
                    int xx=i+c[k],yy=j+d[k];
                    if (xx<0 || xx==n || yy<0 || yy==m)continue;
                    if (b[xx][yy]=='x') continue;
                    if (!mark[xx][yy]) mark[xx][yy]=++FA;
                    add_edge(x,mark[xx][yy]);
                }
            }	
        for (int i=1; i<=FA; ++i){
            if (!bb[i]) continue;
            memset(bo,0,sizeof(bo));
            if (check(i)) --ans; 
        }
        return ans;
    }
};
