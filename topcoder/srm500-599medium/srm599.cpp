#include<iostream>
#include<cstdio>
#include<cstring>
#include<cmath>
#include<algorithm>
using namespace std;

int bo[10000];

int pd(int y,int x){
    int t=x*x+y*y;
    t=sqrt(t);
    while (t*t<x*x+y*y) ++t;
    if (t*t!=x*x+y*y) return 0;
    return t+1;
}

void swap(int &a,int &b){
    int t=a; a=b; b=t;
}

struct cc{
    int x,y,len;
    int operator<(const cc &a)const {
        return len<a.len;
    }
}m[10000];

int f[2600][2600];
int a[4];

int abs(int x) { return x<0?-x:x; }

int check(int len1,int len2,int x1,int y1,int x2,int y2,int &ans,int l){
    int x=abs(x2-x1),y=abs(y2-y1);
    if (x<y) swap(x,y);
    if (x>2500) return 0;
    int t=f[y][x];
    if (t==0) return 0;
    if (t+len1+len2!=l) return 0;
    if (len1+len2<=t) return 0;
    if (len1+t<=len2) return 0;
    if (len2+t<=len1) return 0;
    t=max(abs(t-len1),max(abs(len1-len2),abs(t-len2)));
    ans=min(t,ans);
	
}
class FindPolygons{
public:
    double minimumPolygon(int L){
	if (L%2==1 || L<4) return -1;
	int sum=0;
        for (int i=0 ;i<=2500; ++i)
            for (int j=i; j<=2500; ++j){
                int t=pd(i,j);
                if (t>2501 || t<2) continue;
                --t;
                bo[t]=1;
                f[i][j]=t;
                m[sum].len=t;
                m[sum].x=i;
                m[sum++].y=j;
            }
	int l=L;
	//printf("%d\n",sum);
	sort(m,m+sum);
	int ans=l+1;
	for (int i=0; i<sum; ++i){
            if (m[i].len>=l) break;
            int x1=m[i].len;
            for (int j=i; j<sum; ++j){
                if (x1+m[j].len>=l) break;
                int x2=m[j].len;
                if (!bo[l-x1-x2]) continue;
                a[0]=m[i].x,a[1]=m[i].y;
                a[2]=m[j].x,a[3]=m[j].y;
                for (int I=0; I<2; ++I)
                    for (int J=2; J<4; ++J){
                        int sx=a[I],sy=a[I^1];
                        int tx=a[J],ty=a[((J-2)^1)+2];
                        check(x1,x2,sx,sy,tx,ty,ans,l);
                        check(x1,x2,sx,sy,-tx,ty,ans,l);
                    }
            }
	}
	if (ans>=l){
            if (l%4==0) return 0;
            return 1;
	}
	return ans;
    }
};
