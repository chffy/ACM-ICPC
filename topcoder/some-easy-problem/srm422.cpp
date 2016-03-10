#include <iostream>
#include <cstdio>
#include <cstring>
#include <vector>
#include <algorithm>
#include <set>
#include <cmath>
using namespace std;

double f[20][20][20];

int check(int x) {
    if (x < 2) return 0;
    for (int i = 2; i < x; ++i)
        if (x % i == 0) return 0;
    return 1;
}

class PrimeSoccer {
public:
    double getProbability(int A, int B) {
        f[0][0][0] = 1;
        double pA[2];
        pA[1] = A / 100.0;
        pA[0] = 1 - pA[1];
        double pB[2];
        pB[1] = B / 100.0;
        pB[0] = 1 - pB[1];
        double ans1 = 0, ans2 = 0;
        for (int i = 0; i < 18; ++i)
            if (check(i)) {
                long double sum1 = 1, sum2 = 1;
                for (int k = 1; k <= 18; ++k) {
                    sum1 = sum1 * k;
                    if (k <= i) sum1 /= k;
                    else sum1 /= k - i;
                }
                sum2 = sum1;
                for (int k = 1; k <= 18; ++k) {
                    if (k <= i) sum1 *= pA[1];
                    else sum1 *= pA[0];
                    if (k <= i) sum2 *= pB[1];
                    else sum2 *= pB[0];
                }
                ans1 += sum1;
                ans2 += sum2;
            }
        return ans1 + ans2 - ans1 * ans2;
    }
};
