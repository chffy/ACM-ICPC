#include <iostream>
#include <cstdio>
#include <cstring>
#include <vector>
#include <algorithm>
#include <set>
#include <cmath>
using namespace std;

typedef long long LL;

int f[205], sum1[205], sum2[205];

int find(int x) {
    if (f[x] != x) f[x] = find(f[x]);
    return f[x];
}

class OneDimensionalBalls {
public:
    LL countValidGuesses(vector <int> fr, vector <int> sd) {
        int n = fr.size(), m = sd.size();
        vector<int> len;
        for (int i = 0; i < n; ++i)
            for (int j = 0; j < m; ++j)
                if (fr[i] - sd[j] != 0)
                    len.push_back(abs(fr[i] - sd[j]));
        sort(len.begin(), len.end());
        len.erase(unique(len.begin(), len.end()), len.end());
        LL ans = 0;
        for (auto L : len) {
            for (int i = 0; i < n + m; ++i) {
                f[i] = i;
                if (i < n) sum1[i] = 1, sum2[i] = 0;
                else {
                    sum1[i] = 0;
                    sum2[i] = 1;
                }
            }
            for (int i = 0; i < n; ++i)
                for (int j = 0; j < m; ++j)
                    if (abs(fr[i] - sd[j]) == L) {
                        int x = find(i), y = find(j + n);
                        if (x == y) continue;
                        sum1[x] += sum1[y];
                        sum2[x] += sum2[y];
                        f[y] = x;
                    }
            LL res = 1;
            for (int i = 0; i < n; ++i)
                if (find(i) == i) {
                    if (sum1[i] > sum2[i]) {
                        res = 0;
                        break;
                    }
                    if (sum1[i] < sum2[i])
                        res = res * sum2[i];
                }
            ans += res;
        }
        return ans;
    }
};
