#include <iostream>
#include <cstdio>
#include <cstring>
#include <algorithm>
#include <vector>
using namespace std;

typedef long long LL;

const int P = 1e9 + 9;

// sigma(n * 4 + up(n / k)) - n +maxK

class MinskyMystery {
public:
    int computeAnswer(LL n) {
        if (n < 2) return -1;
        int ans = 0;
        LL K = n;
        for (LL i = 2; i * i <= n; ++i)
            if (n % i == 0) {
                K = i;
                break;
            }
        /*for (int i = 2; i <= K; ++i) {
            ans = (ans + n * 4) % P;
            ans = (ans + (n + i - 1) / i) % P; 
        }
        ans = (ans - n % P + K + P) % P;*/
        for (LL x = 2; x <= K; ) {
            LL p = n / x;
            LL i = n / p;
            LL num = min(K, i) - x + 1;
            ans = (ans + num % P * ((p + 1 + n * 4) % P) % P) % P;
            x = i + 1;
        }
        ans = (ans - n % P + K + P - 1) % P;
        return ans;
    }
};
