#include <iostream>
#include <cstdio>
#include <cstring>
#include <algorithm>
#include <vector>
using namespace std;

const int N = 1e5 + 5;
int bo[N];
typedef long long LL;
const int P = 1e9 + 7;

class ThePermutationGame {
public:
    int findMin(int n) {
	int ans = 1;
	for (int i = 2; i <= n; ++i)
	    if (!bo[i]) {
		for (int j = i * 2; j <= n; j += i)
		    bo[j] = 1;
		int x = n;
		while (x >= i) {
		    x /= i;
		    ans = (LL)ans * i % P;
		}
	    }
	return ans;
    }
};
