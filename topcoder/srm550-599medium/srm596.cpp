#include <iostream>
#include <cstdio>
#include <cstring>
#include <vector>
#include <algorithm>
using namespace std;

typedef long long LL;

class BitwiseAnd {
public:
    
    vector<LL> lexSmallest(vector<LL> subset, int n) {
        vector<LL> ans;
        int m = subset.size();
        LL vis = (1LL << 60) - 1;
        for (int i = 0; i < m; ++i)
            for (int j = i + 1; j < m; ++j)
                if ((subset[i] & subset[j]) == 0)
                    return ans;
                else vis ^= subset[i] & subset[j];
        for (int i = 0; i < m; ++i)
            for (int j = i + 1; j < m; ++j)
                for (int k = j + 1; k < m; ++k)
                    if ((subset[i] & subset[j] & subset[k]) > 0)
                        return ans;
        vector<LL> res;
        int r = n - m;
        res.resize(r);
        for (int i = 0; i < r; ++i) {
            for (int j = 0; j < m; ++j) {
                LL bo = vis & subset[j];
                if (bo == 0) return ans;
                LL lowbit = bo & -bo;
                res[i] ^= lowbit;
                vis ^= lowbit;
            }
        }
        for (int i = 0; i < m; ++i) {
            LL bo = subset[i] & vis;
            vis ^= bo;
        }
        for (int i = 0; i < r; ++i)
            for (int j = i + 1; j < r; ++j) {
                if (vis == 0) return ans;
                LL lowbit = vis & -vis;
                res[i] ^= lowbit;
                res[j] ^= lowbit;
                vis ^= lowbit;
            }
        ans = res;
        ans.insert(ans.end(), subset.begin(), subset.end());
        sort(ans.begin(), ans.end());
        return ans;
    }
};
