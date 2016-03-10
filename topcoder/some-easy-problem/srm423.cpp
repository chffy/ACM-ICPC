#include <iostream>
#include <cstdio>
#include <cstring>
#include <vector>
#include <algorithm>
#include <set>
#include <cmath>
using namespace std;

pair<int, int> pr[105];

class TheTower {
public:
    vector <int> count(vector <int> x, vector <int> y) {
        int n = x.size();
        for (int i = 0; i < n; ++i) {
            pr[i] = make_pair(x[i], y[i]);
        }
        sort(pr, pr + n);
        vector<int > ans;
        for (int i = 0; i < n; ++i)
            ans.push_back(1 << 30);
        for (int i = 0; i < n; ++i)
            for (int j = 0; j < n; ++j) {
                int X = pr[i].first, Y = pr[j].second;
                vector<int> V;
                for (int k = 0; k < n; ++k)
                    V.push_back(abs(X - pr[k].first) + abs(Y - pr[k].second));
                sort(V.begin(), V.end());
                for (int k = 0, p = 0; k < n; ++k) {
                    p += V[k];
                    ans[k] = min(ans[k], p);
                }
            }
        return ans;
    }
};
