#include<iostream>
#include<cstdio>
#include<cstring>
#include<cmath>
using namespace std;

double calc(double i,double W){
    return (i*W)/(i+W);
}

class TriangleXor{
public:
    int theArea(int W){
        double ans=0;
        if ((W & 1)==0) ans=ans+(double)W/4;
        for (int i=1; i<=W; i+=2){
            double x1=calc(i,W);
            double x2=calc(i-1,W);
            ans=ans+(x1-x2);
        }
        for (int i=1; i<W; i+=2){
            double xx=calc(i,W);
            double w=W-2*xx;
            double y0=calc(i+1,W)/(double)W;
            double y1=calc(i-1,W)/(double)W;
            ans=ans+w*(y0-y1)/2;
        }
        return floor(ans);
    }
};
