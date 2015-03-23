#include<iostream>
#include<cstdio>
#include<cstring>
#include<string>
using namespace std;

int abs(int x){ return x<0?-x:x; }
void swap(int &a,int &b){
	int t=a; a=b; b=t;
}

class PowerOfThree{
public:
	string ableToGet(int x, int y){
		x=abs(x);
		y=abs(y);
		while (1){
			if (x==0 && y==0) return "Possible";
			if (x%3==0 && y%3==0) return "Impossible";
			if (x%3!=0 && y%3!=0) return "Impossible";
			if (x%3==0) swap(x,y);
			if (x%3==2) ++x;
			else --x;
			x/=3;  y/=3;
		}
	}
};
