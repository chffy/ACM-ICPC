#include <iostream>
#include <cstdio>
#include <cstring>
#include <vector>
#include <queue>
#include <map>
#include <algorithm>
using namespace std;

int num[20], cnt[20];
int sum[20], pre[20], prd[20];

class RabbitStepping {
public:
    double getExpected(string field, int r) {
        int n = field.size();
        int tot = 0;
        for (int i = 0; i < 1 << n; ++i) {
            if (__builtin_popcount(i) != r) continue;
            ++tot;
            for (int j = 0; j < n; ++j)
                if (i >> j & 1) ++sum[j];
        }
        double ans = 0;
        for (int pos = 0; pos < n; ++pos) {
            for (int mask = 0; mask < 1 << n; ++mask) {
                if (__builtin_popcount(mask) != r) continue;
                if (!(mask >> pos & 1)) continue;
                for (int i = 0; i < n; ++i)
                    if (mask >> i & 1) num[i] = 1;
                    else num[i] = 0;
               	memset(pre, -1, sizeof(pre));
                int m = n, x = pos;
                while (m > 2) {
                    int flag = 0;
                    memset(cnt, 0, sizeof(cnt));
                    memset(prd, 0, sizeof(prd));
                    for (int i = 0; i < m; ++i) {
                        int y;
                        if (i == 0) y = 1;
                        else if (i >= m - 2) y = i - 1;
                        else if (field[i] == 'W') y = i - 1;
                        else if (field[i] == 'B') y = i + 1;
                        else if (field[i] == 'R') {
                            if (pre[i] == -1) y = i - 1;
                            else y = pre[i];
                        }
                        cnt[y] += num[i];
                        prd[y] = i;
                        if (i == x && !flag) {
                            x = y;
                            flag = 1;
                        }
                    }
                    memcpy(pre, prd, sizeof(pre));
                    memcpy(num, cnt, sizeof(num));
                    for (int i = 0; i < m; ++i)
                        if (num[i] > 1) num[i] = 0;
                   	if (num[x] == 0) break;
                    --m;
                }
                if (num[x]) ans += 1.0 / tot;
            }
        }
        return ans;
    }
};
