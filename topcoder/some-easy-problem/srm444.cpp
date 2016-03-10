#include <iostream>
#include <cstdio>
#include <cstring>
#include <vector>
#include <queue>
#include <map>
#include <algorithm>
#include <set>
#include <cmath>
using namespace std;

class UnfoldingTriangles {
public:
    int solve(vector <string> grid, int Lim) {
        int n = grid.size(), m = grid[0].size();
        int ans = -1;
        for (int i = 0; i < n; ++i)
            for (int j = 0; j < m; ++j) {
                int upper = min(i + 1, j + 1);
                while (upper > 0) {
                    int flag = 1;
                    int num = 0;
                    if (i + 1 < n) {
                        for (int k = j - upper + 1; k <= j; ++k)
                            if (grid[i + 1][k] == '#') flag = 0;
                    }
                    if (j + 1 < m) {
                        for (int k = i - upper + 1; k <= i; ++k)
                            if (grid[k][j + 1] == '#') flag = 0;
                    }
                    for (int k = 0; k < upper; ++k)
                        for (int l = 0; l + k < upper; ++l)
                            if (l + k == upper - 1) {
                                if (grid[i - k][j - l] != '/') flag = 0;
                            }
                            else {
                                if (grid[i - k][j - l] == '/') ++num;
                                else if (grid[i - k][j - l] == '.') flag = 0;
                            }
                    if (num > Lim) flag = 0;
                    if (flag) {
                        ans = max(ans, upper * (upper + 1) / 2);
                        break;
                    }
                    else --upper;
                }
            }
        return ans;
    }
};
