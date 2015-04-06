#include<iostream>
#include<cstdio>
#include<cstring>
#include<vector>
using namespace std;

int RR[10000],GG[10000],WW[10000];
int PR[10000],PG[10000];
int f[200][5000];

class KeyDungeonDiv1{
public:
    int maxKeys(vector <int> dR,vector <int> dG,vector <int> rR, vector <int> rG, vector <int> rW, vector <int> keys){
        int n=dR.size();
        int inR=keys[0],inG=keys[1],inW=keys[2];
        for (int i=0; i<(1<<n); ++i){
            RR[i]=inR,GG[i]=inG,WW[i]=inW;
            PR[i]=0;  PG[i]=0;
            for (int j=0; j<n; ++j)
                if (i &(1<<j)) {
                    RR[i]+=rR[j];
                    GG[i]+=rG[j];
                    WW[i]+=rW[j];
                    PR[i]+=dR[j];
                    PG[i]+=dG[j];
                }
        }
        memset(f,-1,sizeof(f));
        f[inG][0]=inW;
        for (int i=0; i<(1<<n); ++i)
            for (int j=0; j<200; ++j){
                if (f[j][i]==-1) continue;
                int rr=RR[i],gg=j,ww=WW[i];
                int dr=PR[i],dg=PG[i];
                if (dg>GG[i]-j) ww-=dg-(GG[i]-j);
                if (ww>f[j][i]) dr-=ww-f[j][i];
                rr-=dr;  ww=f[j][i];
                for (int k=0; k<n; ++k){
                    if (i & (1<<k)) continue;
                    int r=rr,g=gg,w=ww;
                    if (r>=dR[k]) r-=dR[k];
                    else w-=dR[k]-r,r=0;
                    if (g>=dG[k]) g-=dG[k];
                    else w-=dG[k]-g,g=0;
                    if (w<0) continue;
                    f[g+rG[k]][i| (1<<k)]=max(f[g+rG[k]][i|(1<<k)],w+rW[k]);
                }
            }
        int ans=0;
        for (int i=0; i<200; ++i)
            for (int j=0; j<(1<<n); ++j){
                if (f[i][j]==-1) continue;
                ans=max(ans,RR[j]+GG[j]+WW[j]-PR[j]-PG[j]);
            }
        return ans;
    }
	
};
