#include <iostream>
#include <cstdio>
#include <cstring>
#include <vector>
#include <algorithm>
#include <cmath>
using namespace std;

double f[1 << 16];
int d[55];

class StrangeDictionary2 {
public:
    vector <double> getProbabilities(vector <string> words) {
        int n = words.size(), m = words[0].size();
        vector<double> ans;
        ans.resize(n);
        f[(1 << n) - 1] = 1.0;
        for (int mask = (1 << n) - 1; mask > 0; --mask) {
            int K = 0;
            for (int i = 0; i < m; ++i) {
                d[i] = 0;
                char p = 'z' + 1;
                for (int j = 0; j < n; ++j)
                    if (mask >> j & 1) {
                        if (words[j][i] < p) {
                            d[i] = 1 << j;
                            p = words[j][i];
                        }
                        else if (words[j][i] == p)
                            d[i] |= 1 << j;
                    }
                if (d[i] != mask) ++K;
            }
            for (int i = 0; i < m; ++i)
                if (d[i] != mask)
                    f[d[i]] += f[mask] / K;
        }
        for (int j = 0; j < n; ++j)
            ans[j] = f[1 << j];
        return ans;
    }
};
