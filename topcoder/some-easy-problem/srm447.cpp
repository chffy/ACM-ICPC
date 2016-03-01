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

const int C[8] = {-2, -2, -1, -1, 1, 1, 2, 2};
const int D[8] = {-1, 1, -2, 2, -2, 2, -1, 1};

int grid[8][8];

int access_num(int x, int y) {
    if (x < 0 || x >= 8 || y < 0 || y >= 8 || grid[x][y])
        return 1 << 30; 
    int res = 0;
    for (int i = 0; i < 8; ++i) {
        int xx = x + C[i], yy = y + D[i];
        if (xx < 0 || xx >= 8 || yy < 0 || yy >= 8 || grid[xx][yy]) continue;
        ++res;
    }
    return res;
}

int dfs(int x, int y) {
    int num = 1 << 30, tx = -1, ty = -1;
    for (int i = 0; i < 8; ++i) {
        int xx = x + C[i];
        int yy = y + D[i];
        int tmp = access_num(xx, yy);
        if (tmp < num) {
            num = tmp;
            tx = xx;
            ty = yy;
        }
    }
    if (num >= (1 << 30)) return 0;
    grid[tx][ty] = 1;
    return dfs(tx, ty) + 1;
}

class KnightsTour {
public:
    int visitedPositions(vector <string> board) {
        int sx, sy;
        for (int i = 0; i < 8; ++i)
            for (int j = 0; j < 8; ++j) {
                grid[i][j] = (board[i][j] != '.');
                if (board[i][j] == 'K') {
                    sx = i;
                    sy = j;
                }
            }
        return dfs(sx, sy) + 1;
    }
};
