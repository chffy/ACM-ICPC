#include <cstdio>
#include <cstring>
#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

typedef long long LL;

LL f[20][20][20][2];

void updata(LL &x, LL y) {
    x = min(x, y);
}

class FavouriteDigits {
public:
    LL findNext(long long N, int digit1, int count1, int digit2, int count2) {
        memset(f, 63, sizeof(f));
        static int a[20], n = 0;
        while (N > 0) {
            a[++n] = N % 10;
            N /= 10;
        }
        LL maxNum = 1e17;
        while (n < 16) a[++n] = 0;
        reverse(a + 1, a + 1 + n);
        f[0][0][0][0] = 0;
        for (int i = 0; i < n; ++i)
            for (int j = 0; j <= count1; ++j)
                for (int k = 0; k <= count2; ++k)
                    for (int opt = 0; opt < 2; ++opt) {
                        if (f[i][j][k][opt] > maxNum) continue;
                        LL ret = f[i][j][k][opt];
                        for (int l = 0; l < 10; ++l) {
                            int mask = 0;
                            if (opt == 0) {
                                if (l < a[i + 1]) continue;
                                if (l > a[i + 1]) mask = 1;
                                else mask = 0;
                            }
                            else mask = 1;
                            int _j = j, _k = k;
                            if (l == digit1 && !(l == 0 && ret == 0))
                                ++_j;
                            if (l == digit2 && !(l == 0 && ret == 0))
                                ++_k;
                            if (_j > count1) _j = count1;
                            if (_k > count2) _k = count2;
                            updata(f[i + 1][_j][_k][mask], ret * 10 + l);
                        }
                    }
        return min(f[n][count1][count2][0], f[n][count1][count2][1]);
    }
};
