#include <cstdio>
#include <cstring>
#include <iostream>
#include <vector>
#include <algorithm>
#include <cmath>
#include <bitset>
using namespace std;

struct employee {
    int a, p; double w;

    int operator < (const employee &b) const {
        return w < b.w;
    }
}em[100];

double f[55][55];

int check(int n, int K, int tot, double x) {
    for (int i = 0; i <= n; ++i)
        for (int j = 0; j <= K; ++j)
            f[i][j] = 1e60;
    f[0][0] = 0;
    for (int i = 0; i < n; ++i)
        for (int j = 0; j <= K; ++j) {
            f[i + 1][j] = min(f[i + 1][j], f[i][j]);
            if (j < K) f[i + 1][j + 1] = min(f[i + 1][j + 1], f[i][j] + (double)tot * em[i].a * em[i].w - x * em[i].a);
        }
    if (f[n][K] > 0) return 1;
    else return 0;
}

class FoxAndBusiness {
public:
    double minimumCost(int K, int totalWork, vector <int> a, vector <int> p) {
        int n = 0;
        for (int i = 0; i < a.size(); ++i) {
            em[n++] = (employee) {a[i], p[i], (double)p[i] + 3600.0 / a[i]};
        }
        double head = 0, tail = 1e12;
        int num = 2500;
        while (num--) {
            double mid = (head + tail) / 2;
            if (check(n, K, totalWork, mid)) head = mid;
            else tail = mid;
        }
        return head;
    }
};
