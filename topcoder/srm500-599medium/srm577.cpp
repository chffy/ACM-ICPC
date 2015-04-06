#include<iostream>
#include<cstdio>
#include<cstring>
#include<vector>
using namespace std;

typedef pair<int,int> point;

vector <point> a;
int f[15][15][15][15];

int in(int x,int y,int x1,int y1,int x2,int y2){
    if (x>=x1 && x<=x2 && y>=y1 && y<=y2) return 1;
    return 0;
}

class EllysChessboard{
public:
    int minCost(vector <string> board){
        a.clear();
        for (int i=0; i<8; ++i)
            for (int j=0; j<8; ++j)
                if (board[i][j]=='#') a.push_back(make_pair(i+j,i-j+7));
        memset(f,63,sizeof(f));
        if (a.size()==0) return 0;
        for (int i=0; i<a.size(); ++i) f[a[i].first][a[i].second][a[i].first][a[i].second]=0;
        for (int i1=0; i1<15; ++i1)
            for (int i0=i1; i0>=0; --i0)
                for (int j1=0; j1<15; ++j1)
                    for (int j0=j1; j0>=0; --j0){
                        if (f[i0][j0][i1][j1]>1000000000) continue;
                        for (int i=0; i<a.size(); ++i){
                            if (in(a[i].first,a[i].second,i0,j0,i1,j1)) continue;
                            int I0=min(i0,a[i].first),I1=max(i1,a[i].first);
                            int J0=min(j0,a[i].second),J1=max(j1,a[i].second);
                            int p=0;
                            for (int j=0; j<a.size(); ++j){
                                if (in(a[j].first,a[j].second,i0,j0,i1,j1)) continue;
                                if (!in(a[j].first,a[j].second,I0,J0,I1,J1)) continue;
                                p+=max(max(I1-a[j].first,a[j].first-I0),
                                       max(J1-a[j].second,a[j].second-J0));
                            }
                            f[I0][J0][I1][J1]=min(f[I0][J0][I1][J1],f[i0][j0][i1][j1]+p);
                        }
                    }
        int mni=100,mnj=100,mxi=0,mxj=0;
        for (int i=0; i<a.size(); ++i){
            mni=min(mni,a[i].first);
            mxi=max(mxi,a[i].first);
            mnj=min(mnj,a[i].second);
            mxj=max(mxj,a[i].second);
        }
        return f[mni][mnj][mxi][mxj];
    }
};
