#include<iostream>
#include<cstdio>
#include<cstring>
#include<string>
using namespace std;
 
int sum1[100],sum2[100];
 
class MagicalStringDiv1{
public:
  int getLongest(string S){
    int n=S.size();
    memset(sum1,0,sizeof(sum1));
    memset(sum2,0,sizeof(sum2));
    sum1[0]=0;
    for (int i=1; i<=n; ++i)
      sum1[i]=sum1[i-1]+(S[i-1]=='>');
    sum2[n+1]=0;
    for (int i=n; i>0; --i)
      sum2[i]=sum2[i+1]+(S[i-1]=='<');
    int ans=0;
    for (int i=1; i<n; ++i)
      ans=max(ans,min(sum1[i],sum2[i+1])*2);
    return ans;
  }
};