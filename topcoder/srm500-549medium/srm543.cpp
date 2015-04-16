#include <iostream>
#include <cstdio>
#include <cstring>
#include <vector>
#include <algorithm>
#include <cmath>
using namespace std;

const int N = 1e5 + 5;
double f[2][N];

double calc(double x, double y, double S) {
    return sqrt(x * x + y * y) / S;
}

class EllysRivers {
public:
    double getMin(int length, int walk, vector <int> width, vector <int> speed) {
        int cur = 0, nex = 1;
        for (int i = 0; i <= length; ++i)
            f[cur][i] = calc(0, i, walk);
        for (int i = 0; i < width.size(); ++i) {
            f[nex][0] = f[cur][0] + (double)width[i] / speed[i];
            for (int j = 1, k = 0; j <= length; ++j) {
                f[nex][j] = f[nex][j - 1] + 1.0 / walk;
                while (k < j) {
                    double p1 = f[cur][k] + calc(width[i], j - k, speed[i]);
                    double p2 = f[cur][k + 1] + calc(width[i], j - k - 1, speed[i]);
                    if (p2 < p1) ++k;
                    else break;
                }
                f[nex][j] = min(f[nex][j], f[cur][k] + calc(width[i], j - k, speed[i]));
            }
            swap(cur, nex);
        }
        return f[cur][length];
    }
};
