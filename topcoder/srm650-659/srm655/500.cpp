#include <iostream>
#include <cstdio>
#include <cstring>
#include <algorithm>
#include <vector>
using namespace std;
 
const int N = 1e5 + 5;
const int P = 1e9 + 7;
typedef long long LL;
int num[100];
int dp[2][N];
int power[6];
 
void updata(int &x, int y) {
    x += y;
    if (x >= P) x -= P;
}
 
void solve(int n, int d[]) {
    for (int j = 0; j < 9; ++j)
        d[j] = 0;
    d[0] = 1;
    static int C[9];
    for (int i = 1; i <= n; ++i) {
        memset(C, 0, sizeof(C));
        for (int j = 0; j < 9; ++j) {
            if (d[j])
                for (int k = 0; k < 10; ++k) {
                    updata(C[(j + k) % 9], d[j]);
                }
        }
        for (int j = 0; j < 9; ++j)
            d[j] = C[j];
    }
}
 
class Nine {
public:
    int count(int n, vector <int> d) {
        int m = d.size();
        for (int i = 0; i < m; ++i)
            num[d[i]] ++;
        power[0] = 1;
        for (int i = 1; i <= n; ++i) power[i] = power[i - 1] * 9;
        int cur = 0, nex = 1;
        dp[cur][0] = 1;
        for (int i = 0; i < 1 << n; ++i) {
            memset(dp[nex], 0, sizeof(dp[nex]));
            static int D[9];
            solve(num[i], D);
            for (int mask = 0; mask < power[n]; ++mask)
                if (dp[cur][mask]) {
                    static int a[9];
                    for (int j = 0; j < n; ++j)
                        a[j] = (mask / power[j]) % 9;
                    for (int k = 0; k < 9; ++k) {
                        int opt = 0;
                        for(int j = 0; j < n; ++j) {
                            int x = a[j];
                          if ((i >> j) & 1)
                            x = (a[j] + k) % 9;
                            opt += x * power[j];
                        }
                        updata(dp[nex][opt], (LL)dp[cur][mask] * D[k] % P);
                    }
                }
            swap(cur, nex);
        }
        return dp[cur][0];
    }
};