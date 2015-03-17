#include <iostream>
#include <cstdio>
#include <cstring>
using namespace std;

int grid1[35][35];
int grid2[35][35];
int grid3[35][35];

int main() {
    int n;
    while (scanf("%d", &n), n) {
        for (int i = 1; i <= n; ++i)
            for (int j = 1; j <= n; ++j)
                scanf("%d", &grid1[i][j]);
        for (int i = 1; i <= n; ++i)
            for (int j = 1; j <= n; ++j)
                scanf("%d", &grid2[i][j]);
        int ans = 0;
        for (int T = 0; T < 4; ++T) {
            for (int i = 1; i <= n; ++i)
                for (int j= 1; j <= n; ++j)
                    grid3[n - j + 1][i] = grid2[i][j];
            memcpy(grid2, grid3, sizeof(grid2));
            int sum = 0;
            for (int i = 1; i <= n; ++i)
                for (int j = 1; j<= n; ++j)
                    sum += grid1[i][j] == grid2[i][j];
            ans = max(ans, sum);
        }
        printf("%d\n", ans);
    }
    return 0;
}