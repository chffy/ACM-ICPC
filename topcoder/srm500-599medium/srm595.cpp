#include<iostream>
#include<cstdio>
#include<cstring>
#include<vector>
using namespace std;

string S;
int bo[2501][2501];
typedef long long LL;
LL sum[2501],sum1[2501];
int f[2501][2501];

class LittleElephantAndRGB{
public:
    long long getNumber(vector <string> list, int minGreen){
        S="";
        for (int i=0; i<list.size(); ++i)
            S+=list[i];
        int n=S.size();
        memset(bo,0,sizeof(bo));
        for (int i=0; i<=n-minGreen; ++i){
            int k=0;
            for (int j=i; j<i+minGreen; ++j)
                if (S[j]!='G') ++k;
            if (!k) bo[i][i+minGreen-1]=1;
        }
        for (int j=1; j<n ; ++j)
            for (int i=j-1; i>=0; --i)
                bo[i][j]|=bo[i+1][j] | bo[i][j-1];
        memset(sum,0,sizeof(sum));
        memset(sum1,0,sizeof(sum1));
        memset(f,0,sizeof(f));
        for(int i=0; i<n; ++i){
            if (!bo[0][i]) {
                sum[i]=i+1;
                continue;
            }
            if (bo[i][i]){
                sum1[i]=i+1;
                continue;
            }
            int head=0,tail=i;
            while (head!=tail-1){
                int mid=(head+tail)>>1;
                if (bo[mid][i]) head=mid;
                else tail=mid;
            }
            sum1[i]=head+1;
            sum[i]=i+1-sum1[i];
        } 
        for (int i=0; i<n; ++i)
            for (int j=1; j<minGreen; ++j){
                if (i-j+1<0) break;
                if (S[i-j+1]!='G') break;
                if (j>sum[i]) break;
                if (i-j>=0 && S[i-j]=='G'){
                    f[i][j]=1;
                    continue;
                }
                f[i][j]=sum[i]-j+1;
            }
        for (int i=1; i<n; ++i) sum[i]+=sum[i-1],sum1[i]+=sum1[i-1];
        for (int i=1; i<n; ++i)
            for (int j=1; j<minGreen; ++j) 
                f[i][j]+=f[i-1][j];
        LL ans=0;
        for (int i=0; i<n; ++i)
            for (int j=i+1; j<n; ++j)
                if (bo[i][j]) ans+=j-i;
        for (int i=2; i<n; ++i){
            int p1=0,p2=0;
            if (!bo[i][n-1]) p2=n-i;
            else if (bo[i][i]) p1=n-i;
            else {
                int head=i,tail=n-1;
                while (head!=tail-1){
                    int mid=(head+tail)>>1;
                    if (bo[i][mid]) tail=mid;
                    else head=mid;
                }
                p1=n-tail,p2=tail-i;
            }
            ans=ans+(LL)(p1)*(sum1[i-2]+sum[i-2]);
            ans=ans+(LL)(p2)*sum1[i-2];
            //printf("%d %d %d %d %d\n",i,p1,p2,sum1[i-2],sum[i-2]);
            for (int j=minGreen-2;j>0; --j)
                f[i-2][j]+=f[i-2][j+1];
            for (int j=1; j<minGreen; ++j){
                if (i+j-1==n) break;
                if (S[i+j-1]!='G') break;
                if (j>p2) break;
                if (i+j<n && S[i+j]=='G'){
                    ans=ans+f[i-2][minGreen-j];
                    continue;
                }
                ans=ans+(LL)(p2-j+1)*f[i-2][minGreen-j];
            }
        }
        return ans;	
    }
};
