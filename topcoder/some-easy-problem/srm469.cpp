#include <iostream>
#include <cstdio>
#include <cstring>
#include <vector>
#include <queue>
#include <map>
#include <algorithm>
#include <set>
using namespace std;

typedef long long LL;

pair<int, int> pr[50];

class TheMoviesLevelOneDivOne {
public:
    LL find(int n, int m, vector <int> row, vector <int> seat) {
        int r = row.size();
        for (int i = 0; i < r; ++i)
            pr[i] = make_pair(row[i], seat[i]);
        sort(pr, pr + r);
        LL ans = (LL)n * (m - 1);
        for (int i = 0; i < r; ++i) {
            int j = i;
            set<int> ext;
            while (j + 1 < r && pr[j + 1].first == pr[i].first) {
                ++j;
            }
            for (int k = i; k <= j; ++k)
                ext.insert(pr[k].second);
            for (int k = i; k <= j; ++k) {
                int x = pr[k].second;
                if (x - 1 > 0) --ans; 
                if (x + 1 <= m && !ext.count(x + 1)) --ans;
            }
            i = j;
            --n;
        }
        return ans;
    }
};
