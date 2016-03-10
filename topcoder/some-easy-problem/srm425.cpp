#include <iostream>
#include <cstdio>
#include <cstring>
#include <vector>
#include <algorithm>
#include <set>
#include <cmath>
using namespace std;

int X[4] = {1, -1, 0, 0};
int Y[4] = {0, 0, 1, -1};

int P[4];
int bo[40][40];

double dfs(int n, int dx, int dy) {
    if (n == 0) return 1;
    double res = 0;
    for (int i = 0; i < 4; ++i) {
        int tx = dx + X[i];
        int ty = dy + Y[i];
        if (bo[tx + 20][ty + 20]) continue;
        bo[tx + 20][ty + 20]++;
        res += P[i] * dfs(n - 1, tx, ty) / 100;
        bo[tx + 20][ty + 20]--;
    }
    return res;
}

class CrazyBot {
public:
    double getProbability(int n, int east, int west, int south, int north) {
        P[0] = east;
        P[1] = west;
        P[2] = south;
        P[3] = north;
        bo[20][20] = 1;
        return dfs(n, 0, 0);
    }
};

