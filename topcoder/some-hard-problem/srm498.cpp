#include <iostream>
#include <cstdio>
#include <cstring>
#include <vector>
#include <algorithm>
#include <set>
#include <cmath>
#include <stack>
using namespace std;

const int P = 10007;

int I[P], inv[P];

void init() {
    I[0] = I[1] = inv[0] = inv[1] = 1;
    for (int i = 2; i < P; ++i) {
        inv[i] = (P - P / i) * inv[P % i] % P;
        I[i] = i;
    }
    for (int i = 2; i < P; ++i) {
        I[i] = I[i] * I[i - 1] % P;
        inv[i] = inv[i] * inv[i - 1] % P;
    }
}

int C(int n, int m) {
    return I[n] * inv[m] % P * inv[n - m] % P;
}

void updata(int &x, int y) {
    x += y;
    if (x >= P) x -= P;
}

int fx[1605][805], fy[1605][805];
int dp[1605][85];

class FoxJumping {
public:
    int getCount(int Tx, int Ty, int Mx, int My, int R, vector <int> bad) {
        init();
        fx[0][0] = 1;
        fy[0][0] = 1;
        for (int i = 1; i <= R; ++i) {
            int res = 0;
            for (int j = 0; j <= Tx; ++j) {
                updata(res, fx[i - 1][j]);
                fx[i][j] = res;
                if (j - Mx >= 0)
                    updata(res, P - fx[i - 1][j - Mx]);
            }
            res = 0;
            for (int j = 0; j <= Ty; ++j) {
                updata(res, fy[i - 1][j]);
                fy[i][j] = res;
                if (j - My >= 0)
                    updata(res, P - fy[i - 1][j - My]);
            }
        }
        int m = 0;
        for (int i = 0; i <= R; ++i)
            for (int j = 0; j * 10 <= Tx && j * 10 <= Ty; ++j) {
                dp[i][j] = fx[i][Tx - j * 10] * fy[i][Ty - j * 10] % P;
                m = j;
            }
        bad.push_back(0);
        for (auto x : bad) {
            x /= 10;
            for (int i = 1; i <= R; ++i)
                for (int j = 0; j <= m; ++j) {
                    for (int k = 1; k <= i && x * k + j <= m; ++k)
                        updata(dp[i][j], P - dp[i - k][j + x * k] * C(i, k) % P);
                }
        }
        return dp[R][0];
    }
};
