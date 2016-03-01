#include <iostream>
#include <cstdio>
#include <cstring>
#include <vector>
#include <queue>
#include <map>
#include <algorithm>
#include <set>
#include <cmath>
using namespace std;

int a[100], b[100];
int num[6];

class TheBasketballDivOne {
public:
    int find(int n, int m) {
        int r = 0;
        for (int i = 1; i <= n; ++i)
            for (int j = 1; j <= n; ++j)
                if (i != j) {
                    a[r] = i;
                    b[r++] = j;
                }
        set<vector<int> > ext;
        for (int mask = 0; mask < 1 << r; ++mask) {
            memset(num, 0, sizeof(num));
            for (int i = 0; i < r; ++i)
                if (mask >> i & 1) ++num[a[i]];
                else ++num[b[i]];
            sort(num + 1, num + n + 1);
            reverse(num + 1, num + n + 1);
            if (num[1] == m) {
                vector<int> ver;
                for (int i = 1; i <= n; ++i) {
                    ver.push_back(num[i]);
                }
                ext.insert(ver);
            }
        }
        return (int)ext.size();
    }
};
