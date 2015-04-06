#include<iostream>
#include<cstdio>
#include<cstring>
#include<vector>
#include<string>
#include<algorithm>
using namespace std;

string sL,sR;
int ll[400],rr[400];
pair<int,int> a[400];

int getnum(const string &s,int p,int &x){
    x=0;
    while (p<s.size() && s[p]==' ') ++p;
    while (p<s.size() && s[p]!=' ') x=x*10+s[p++]-'0';
    while (p<s.size() && s[p]==' ') ++p;
    return p;
}

int getarray(const string &s,int a[]){
    int m=0,p=0;
    while (p!=s.size()) p=getnum(s,p,a[m++]);
    return m;
}

int cmp(const pair<int,int> &a,const pair<int,int> &b){
    if (a.first==b.first) return a.second>b.second;
    return a.first<b.first;
}

int dp[301][301];
const int P=1000000007;

class WolfInZooDivOne{
public:
    int count(int n, vector <string> L, vector <string> R){
        sL="", sR="";
        for (int i=0; i<L.size(); ++i) sL+=L[i];
        for (int j=0; j<R.size(); ++j) sR+=R[j];
        int m=getarray(sL,ll);
        getarray(sR,rr);
        for (int i=0; i<m; ++i) a[i]=make_pair(ll[i]+1,rr[i]+1);
        sort(a,a+m,cmp);
        int M=0;
        for (int i=0; i<m; ++i)
            if (M==0 || a[M-1].second<a[i].second)a[M++]=a[i]; 
        m=M;
        memset(dp,0,sizeof(dp));
        dp[0][0]=1;
        for (int i=0; i<n; ++i)
            for (int j=0; j<=i; ++j){
                if (i!=0 && i==j) continue;
                if (!dp[j][i]) continue;
                int t=-1;
                for (int k=0; k<m; ++k)
                    if (a[k].first<=j && a[k].second>=i) t=k;
                for (int k=i+1; k<=n; ++k)
                    if (t==-1 || k>a[t].second) dp[i][k]=(dp[i][k]+dp[j][i])%P;
            }
        int ans=0;
        for (int i=0; i<=n; ++i)
            for (int j=0; j<=i; ++j) {ans=(ans+dp[j][i])%P; }
        return ans;
    }
};
