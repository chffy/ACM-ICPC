#include <iostream>
#include <cstdio>
#include <cstring>
#include <vector>
#include <algorithm>
#include <set>
#include <cmath>
#include <stack>
#include <deque>
using namespace std;

int b[100], t[100];
int x[100];

int power[11];

int n;
int grid[11][11];
int color[11];

int dfs(int x, int k) {
    if (x >= n) return 1;
    for (int i = 1; i <= k; ++i) {
        int flag = 0;
        for (int j = 0; j < n; ++j)
            if (grid[x][j] && color[j] == i) {
                flag = 1;
                //printf("%d %d %d\n", x, j, i);
                break;
            }
        if (flag == 1) continue;
        color[x] = i;
        if (dfs(x + 1, k)) return 1;
        color[x] = 0;
    }
    return 0;
}

class BunnyExam {
public:
    double getExpected(int m, int k, vector <int> linkage) {
        double ans = (double)m / k;
        n = linkage.size() / 2;
        if (k == 1) {
            if (m != 1) return -1; 
        }
        else {
            for (int i = 0; i < n * 2; ++i)
                for (int j = 0; j < n * 2; ++j) {
                    if (abs(linkage[i] - linkage[j]) == 1) {
                        grid[i / 2][j / 2] = 1;
                    }
                }
            for (int i = 0; i < n; ++i)
                if (grid[i][i]) return -1.0;
            if (k == 2) {
                for (int i = 0; i < n; ++i)
                    if (linkage[i * 2] % 2 != linkage[i * 2 + 1] % 2) return -1;
            }
            else if (k <= 4) {
                if (!dfs(0, k)) return -1;
            }
        }
        return ans;
    }
};
