#include <iostream>
#include <cstdio>
#include <cstring>
#include <iostream>
using namespace std;

typedef long long LL;

LL calc(LL n1, LL n2, LL ans, LL x) {
    return x * x + (n1 - x) * x + (n2 - x) * (ans - x);
}

class MaximumBipartiteMatchingProblem {
public:
    LL solve(int n1, int n2, int ans, int d) {
	if (n1 > n2) swap(n1, n2);
	if (d > n1) return -1;
	if (ans == n1) return (LL)n1 * n2;
	if (ans - d < d) return -1;
	LL sum = max(calc(n1, n2, ans, d), calc(n1, n2, ans, ans - d));
	LL x1 = (n1 - n2 - ans) / 2, x2 = (n1 - n2 - ans + 1) / 2;
	if (x1 >= d && x1 <= ans - d) 
	    sum = max(sum, calc(n1, n2, ans, x1));
	if (x2 >= d && x2 <= ans - d) 
	    sum = max(sum, calc(n1, n2, ans, x2));
	return sum;
    }
};