#include <cstdio>
#include <cstring>
#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;
 
double f[300][300];
 
class RandomPancakeStack {
public:
    double expectedDeliciousness(vector <int> d) {
        int n = d.size();
        double ans = 0;
        reverse(d.begin(), d.end());
        for (int i = 0; i < n; ++i) {
            for (int j = 0; j <= i; ++j) {
                double p = 1;
                for (int k = 1; k <= j; ++k)
                    p = p * (i - k + 1) / k / (n - k + 1);
                p = p / (n - j);
                ans += p * d[i];
            }
        }
        return ans;
    }
};
