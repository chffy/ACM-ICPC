#include <iostream>
#include <cstdio>
#include <cstring>
#include <algorithm>
#include <vector>
using namespace std;

typedef long long LL;

class TheKingsFactorization {
public:
    vector<LL> getVector(LL N, vector<LL> primes) {
	vector<LL> ans;
	for (int i = 0; i < primes.size(); ++i) {
	    N /= primes[i];
	    ans.push_back(primes[i]);
	}
	for (LL i = 2; i * i <= N && i <= 1000000; ++i)
	    while (N % i == 0) {
		ans.push_back(i);
		N /= i;
	    } 
	if (N != 1) ans.push_back(N);
	sort(ans.begin(), ans.end());
	return ans;
    }
};
