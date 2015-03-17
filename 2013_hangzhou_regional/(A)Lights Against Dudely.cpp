#include <cstdio>
#include <cstring>
#include <algorithm>
#include <utility>
#include <queue>
using namespace std;

int grid[205][205];
int xx[205], yy[205];
int mark[205][205], f[1 << 15];

int C[4] = {-1, 0, 1, 0};
int D[4] = {0, 1, 0, -1};

int check(int x, int y) {
    if (grid[x][y] == 1) return -2;
    return mark[x][y];
}

int solve(int x, int y, int k) {
    int x1 = x + C[k], y1 = y + D[k];
    int x2 = x + C[(k + 1) % 4], y2 = y + D[(k + 1) % 4];
    int p1 = check(x1, y1);
    int p2 = check(x2, y2);
    int p3 = check(x, y);
    if (p1 == -2 || p2 == -2 || p3 == -2) return -1;
    int mask = 0;
    if (~p1) mask |= 1 << p1;
    if (~p2) mask |= 1 << p2;
    if (~p3) mask |= 1 << p3;
    return mask;
}

int main() {
    int n, m;
    while (scanf("%d%d", &n, &m), n ||m) {
        memset(grid, 0, sizeof(grid));
        memset(mark, -1, sizeof(mark));
        int r = 0;
        for (int i = 1; i <= n; ++i)
            for (int j = 1; j <= m; ++j) {
                int ch;
                while (ch = getchar(), ch != '#' && ch != '.');
                if (ch == '#') grid[i][j] = 1;
                else {
                    xx[r] = i;
                    yy[r] = j;
                    mark[i][j] = r;
                    ++r;
                }
            }
        if (r == 0) {
            puts("0");
            continue;
        }
        for (int i = 0; i < 1 << r; ++i)
            f[i] = 1 << 30;
        f[0] = 0;
        for (int k = 0; k < 4; ++k)
            for (int i = 0; i < r; ++i) {
                int mask = solve(xx[i], yy[i], k);
                if (mask == -1) continue;
                f[mask] = min(1, f[mask]);
            }
        for (int mask = 0; mask < 1 << r; ++mask)
            if (f[mask] < 100)
            for (int i = 0; i < r; ++i) {
                int opt = solve(xx[i], yy[i], 0);
                if (opt == -1) continue;
                f[opt | mask] = min(f[opt | mask], f[mask] + 1);
                //printf("%d %d %d\n", mask, opt | mask, f[mask] + 1);
            }
        if (f[(1 << r) - 1] > 100) printf("-1\n");
        else printf("%d\n", f[(1 << r) - 1]);
    }
    return 0;
}