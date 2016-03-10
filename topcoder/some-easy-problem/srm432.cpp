#include <iostream>
#include <cstdio>
#include <cstring>
#include <vector>
#include <algorithm>
#include <cmath>
using namespace std;

int grid[100][100];
int tt[100][100];
int C[100];

class LampsGrid {
public:
    int mostLit(vector <string> initial, int K) {
        int n = initial.size(), m = initial[0].size();
        for (int i = 0; i < n; ++i)
            for (int j = 0; j < m; ++j)
                grid[i][j] = initial[i][j] - '0';
        int ans = 0;
        for (int i = 0; i < n; ++i) {
            memset(C, 0, sizeof(C));
            int res = 0;
            for (int j = 0; j < m; ++j)
                if (grid[i][j] == 0) {
                    ++res;
                    C[j] = 1;
                }
            if (res > K || (K - res) % 2 != 0) continue;
            int tmp = 0;
            for (int j = 0; j < n; ++j) {
                int flag = 1;
                for (int k = 0; k < m; ++k)
                    if (!(grid[j][k] ^ C[k])) flag = 0;
                tmp += flag;
            }
            ans = max(ans, tmp);
        }
        return ans;
    }
};
