#include <iostream>
#include <cstdio>
#include <cstring>
#include <algorithm>
#include <vector>
using namespace std;

int f[2][100][100];

class Mutalisk {
public:

    int check(vector<int> &x, int ans) {
        int n = x.size();
        memset(f, 63, sizeof(f));
        int cur = 0, nex = 1;
        f[cur][0][0] = 0;
        for (int i = 0; i < n; ++i) {
            memset(f[nex], 63, sizeof(f[nex]));
            for (int j = 0; j <= ans; ++j)
                for (int k = 0; k <= ans; ++k)
                    for (int _j = 0; (_j - 1) * 9 <= x[i] && _j <= j; ++_j)
                        for (int _k = 0; (_k - 1) * 3 <= max(x[i] - _j * 9, 0) && _k <= k; ++_k) {
                            int p = min(x[i], _j * 9 + _k * 3), m = _j + _k + x[i] - p;
                            if (m > ans) continue;
                            f[nex][j][k] = min(f[cur][j - _j][k - _k] + x[i] - p, f[nex][j][k]);
                        }
            swap(cur, nex);
        }
        for (int j = 0; j <= ans; ++j)
            for (int k = 0; k <= ans; ++k) {
                if (f[cur][j][k] <= ans) return 1;
            }
        return 0;
    }
    
    int minimalAttacks(vector <int> x) {
        int head = 0, tail = 99;
        while (head < tail - 1) {
            int mid = (head + tail) >> 1;
            if (check(x, mid)) tail = mid;
            else head = mid;
        }
        return tail;
    }
};
