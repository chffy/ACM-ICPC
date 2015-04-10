#include <iostream>
#include <cstdio>
#include <cstring>
#include <algorithm>
#include <vector>
#include <queue>
using namespace std;

const int zero = 300;
const int C[4] = {-1, -1, 1, 1};
const int D[4] = {-1, 1, -1, 1};
bool f[2][605][605];

bool check(int T, vector<int> x, vector<int> y) {
    int cur = 0, nex = 1;
    memset(f[cur], 0, sizeof(f[cur]));
    for (int i = 0; i < x.size(); ++i) {
        f[cur][x[i]][y[i]] = 1;
    }
    for (int K = 1; K <= T; ++K) {
        memset(f[nex], 0, sizeof(f[nex]));
        for (int i = 0; i <= 600; ++i)
            for (int j = 0; j <= 600; ++j)
                if (f[cur][i][j]) {
                    for (int k = 0; k < 4; ++k) {
                        int xx = i + C[k], yy = j + D[k];
                        if (xx >= 0 && yy <= 600 && xx <= 600 && yy >= 0) {
                            f[nex][xx][yy] = 1;
                            }
                            else puts("1");
                    }
                }
        swap(cur, nex);
    }
    for (int K = 1; K <= T; ++K) {
        memset(f[nex], 0, sizeof(f[nex]));
        for (int i = 1; i <= 600; ++i)
            for (int j = 1; j <= 600; ++j)
                if (f[cur][i - 1][j - 1] && f[cur][i - 1][j + 1] &&
                    f[cur][i + 1][j + 1] && f[cur][i + 1][j - 1]) {
                    f[nex][i][j] = 1;
                    }
        swap(cur, nex);
    }
    for (int i = 0; i <= 600; ++i)
        for (int j = 0; j <= 600; ++j)
            if (f[cur][i][j]) {
            	int p = 1;
            	for (int k = 0; k < x.size(); ++k)
            		if (i == x[k] && j == y[k]) p = 0;
            	if (p) return 0;
            }
    //printf("%d %d\n", T, ans);
    return 1;
}

class DrawingPointsDivOne {
public:
    
    int maxSteps(vector <int> x, vector <int> y) {
        int n = x.size();
        for (int i = 0; i < n; ++i) {
            x[i] = zero + x[i] * 2;
            y[i] = zero + y[i] * 2;
        }
        if (check(151, x, y)) return -1;
        int head = 0, tail = 151;
        while (head < tail - 1) {
            int mid = (head + tail) >> 1;
            if (check(mid, x, y)) head = mid;
            else tail = mid;
        }
        return head;
    }
};
