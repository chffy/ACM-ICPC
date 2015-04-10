#include<iostream>
#include<cstdio>
#include<cstring>
#include<map>
#include<vector>
using namespace std;

typedef unsigned long long ULL;
int n,m,N,tot;
int a[100];
int aa[100];
string b[100];
string str[100000];
map<ULL,int> C;
const int P=1000000009;

void dfs(int x,string S){
    for (int i=1; i<=n; ++i)
        if (aa[i]>a[i]) return ;
    if (x>m){
        ULL c=0;
        for (int i=1; i<=n; ++i) 
            c=c*P+aa[i];
        if (C[c]) C[c]=-1;
        else{
            C[c]=++tot;
            str[tot]=S;
        }
        return ;
    }
    for (char i='0'; i<='9'; ++i){
        for (int j=1; j<=n; ++j)
            if (i==b[j][x-1]) ++aa[j];
        dfs(x+1,S+i);
        for (int j=1; j<=n; ++j)
            if (i==b[j][x-1]) --aa[j];
    }
}

int flag;
string Sans;

void dfs1(int x,string S){
    if (flag==-1) return ;
    for (int i=1; i<=n; ++i)
        if (aa[i]>a[i]) return ;
    if (x>N){
        ULL c=0;
        for (int i=1; i<=n; ++i) 
            c=c*P+a[i]-aa[i];
        if (!C.count(c)) return ;
        int t=C[c];
        if (t==-1){
            flag=-1; return;
        }
        if (flag) {
            flag=-1; return ;
        }
        flag=1;
        Sans=S+str[t];
        return;
    }
    for (char i='0'; i<='9'; ++i){
        for (int j=1; j<=n; ++j)
            if (i==b[j][x-1]) ++aa[j];
        dfs1(x+1,S+i);
        for (int j=1; j<=n; ++j)
            if (i==b[j][x-1]) --aa[j];
    }
}

class EllysBulls{
public:
    string getNumber(vector <string> guesses, vector <int> bulls){
        n=guesses.size();
        m=guesses[0].size();
	cout<<n<<" "<<m<<endl;
        for (int i=1; i<=n; ++i) b[i]=guesses[i-1],a[i]=bulls[i-1];
        N=(m+1)/2;
        cout<<1<<endl;
        memset(aa,0,sizeof(aa));
        C.clear();
        tot=0;
        dfs(N+1,"");
        cout<<1<<endl;
        flag=0;
        dfs1(1,"");
        if (flag==-1) return "Ambiguity";
        if (flag==1) return Sans;
        return "Liar";
    }
};
