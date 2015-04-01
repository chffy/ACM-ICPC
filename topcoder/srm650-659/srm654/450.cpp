#include <iostream>
#include <cstdio>
#include <cstring>
#include <algorithm>
#include <vector>
using namespace std;

int max1[2005];

class SuccessiveSubtraction2 {
public:
    vector <int> calc(vector <int> a, vector <int> p, vector <int> v) {
        int n = a.size();
        vector<int> ans;
        ans.resize(p.size());
        for (int q = 0; q < p.size(); ++q) {
            a[p[q]] = v[q];
            int sum = a[0];
            for (int i = 1; i < n; ++i) sum -= a[i];
            max1[n] = 0;
            for (int i = n - 1, s1 = 0, mn = 0; i > 1; --i) {
                s1 += a[i];
                max1[i] = max(max1[i + 1], s1 - mn);
                mn = min(s1, mn);
            }
            ans[q] = sum;
            for (int i = 2, s1 = 0, mn = 0; i < n; ++i) {
                s1 += a[i];
                ans[q] = max(sum + 2 * (s1 - mn + max1[i + 1]), ans[q]);
                mn = min(s1, mn);
            }
        }
        return ans;
    }
};
