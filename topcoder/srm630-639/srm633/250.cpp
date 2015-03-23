#include <iostream>
#include <cstdio>
#include <cstring>
#include <vector>
using namespace std;

typedef long long LL;

class PeriodicJumping {
public:
    int minimalTime(int x, vector <int> ju) {
	LL sum = 0;
	int n = ju.size(), ans = 0;
	int max1 = 0, max2 = 0;
	if (x < 0) x = -x;
	LL y = 0;
	for (int i = 0; i < n; ++i) { 
	    sum += ju[i];
	    max1 = max(max1, ju[i]);
	}
	if (x >= sum) {
	    ans = x / sum;
	    y = sum * ans;
	    ans *= n;
	    max2 = max1;
	}
	for (int i = 0; y < x || x + y - max2 < max2; i = (i + 1) % n) {
	    y += ju[i];
	    max2 = max(ju[i], max2);
	    ++ans;
	}
	return ans;
    }
};
