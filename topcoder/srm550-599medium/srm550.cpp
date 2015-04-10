#include <iostream>
#include <cstdio>
#include <cstring>
#include <algorithm>
#include <vector>
using namespace std;

typedef long long LL;

int C(LL n, LL m) {
    LL num = 0;
    LL r = n - m;
    while (n > 0) {
        num += n / 2;
        n /= 2;
    }
    while (m > 0) {
        num -= m / 2;
        m /= 2;
    }
    
    while (r > 0) {
    	num -= r / 2;
    	r /= 2;
    }
    return num == 0;
}

class CheckerExpansion {
public:
    vector <string> resultAfter(LL t, LL x0, LL y0, int w, int h) {
        vector<string> ans;
        for (int i = 0; i < h; ++i) {
            ans.push_back("");
            for (int j = 0; j < w; ++j)
                ans[i] += '.';
        }
        for (int i = 0; i < h; ++i)
            for (int j = 0; j < w; ++j) {
                LL x = x0 + j, y = y0 + h - i - 1;
                if ((x + y) % 2 != 0) continue;
                LL n = (x + y) / 2;
                if (n > t - 1) continue;
                LL m = n * 2 - x;
                if (m > n || m < 0) continue;
                int S = C(n, m);
                if (S == 0) continue;
                if (n % 2 == 0) ans[i][j] = 'A';
                else ans[i][j] = 'B';
            }
        return ans;
    }
};
