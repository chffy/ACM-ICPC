#include<iostream>
#include<cstdio>
#include<cstring>
#include<vector>
#include<string>
#include<algorithm>
using namespace std;

string C1000,C100,C10,C1;
string D1000,D100,D10,D1;
int bo[3000];
int mark[3000];

pair<int,int> a[3000];
pair<int,int> b[3000];

int cmp(pair<int,int> a,pair<int,int> b){
    if (a.first==b.first) return a.second>b.second;
    return a.first<b.first;
}

class ShoutterDiv1{
public:
    int count(vector <string> s1000, vector <string> s100, vector <string> s10, vector <string> s1, vector <string> t1000, vector <string> t100, vector <string> t10, vector <string> t1){
        int n=0;
        C1000=""; C100="";  C10=""; C1="";
        D1000=""; D100="";  D10=""; D1="";
        for(int i=0; i<s1000.size(); ++i) C1000+=s1000[i];
        for(int i=0; i<s100.size(); ++i) C100+=s100[i];
        for(int i=0; i<s10.size(); ++i) C10+=s10[i];
        for(int i=0; i<s1.size(); ++i) C1+=s1[i];
        for(int i=0; i<t1000.size(); ++i) D1000+=t1000[i];
        for(int i=0; i<t100.size(); ++i) D100+=t100[i];
        for(int i=0; i<t10.size(); ++i) D10+=t10[i];
        for(int i=0; i<t1.size(); ++i) D1+=t1[i];
        n=C1.size();
        for (int i=0; i<n; ++i){
            a[i+1].first=(C1000[i]-'0')*1000+(C100[i]-'0')*100+(C10[i]-'0')*10+C1[i]-'0';
            a[i+1].second=(D1000[i]-'0')*1000+(D100[i]-'0')*100+(D10[i]-'0')*10+D1[i]-'0';
        }
        sort(a+1,a+n+1,cmp);
        memset(bo,0,sizeof(bo));
        int m=1; b[1]=a[1];
        for (int i=2; i<=n; ++i)
            if (a[i].second>b[m].second) b[++m]=a[i];
        for (int i=2; i<=m; ++i)
            if (b[i].first>b[i-1].second) return -1;
        int ans=0;
        for (int i=1; i<=n; ++i){
            int m1=100000,m2=-100000;
            for (int j=1; j<=n; ++j){
                m1=min(m1,a[j].second);
                m2=max(m2,a[j].first);
            }
            int j;
            for (j=1; m1<a[i].first; ++j){
                if (b[j].second<m1) continue;
                if (j<m && b[j+1].first<=m1) continue;
                ++ans;
                m1=b[j].second;
            }
            m1=max(m1,a[i].second);
            for (;m1<m2; ++j){
                if (b[j].second<m1) continue;
                if (j<m && b[j+1].first<=m1) continue;
                ++ans;
                m1=b[j].second;
            }
        }
        return ans;
    }
};
