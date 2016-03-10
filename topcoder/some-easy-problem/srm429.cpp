#include <iostream>
#include <cstdio>
#include <cstring>
#include <vector>
#include <algorithm>
#include <cmath>
using namespace std;

typedef long long LL;

class SubrectanglesOfTable {
public:
    vector<LL> getQuantity(vector <string> table) {
        for (int i = 0; i < table.size(); ++i)
            table[i] += table[i];
        int n = table.size();
        for (int i = 0; i < n; ++i)
            table.push_back(table[i]);
        n *= 2;
        int m = table[0].size();
        vector<LL> ans;
        for (int i = 0; i < 26; ++i)
            ans.push_back(0);
        for (int i = 0; i < n; ++i)
            for (int j = 0; j < m; ++j)
                ans[table[i][j] - 'A'] += (LL)(n - i) * (m - j) * (i + 1) * (j + 1);
        return ans;
    }
};
