#include <cstdio>
#include <cstring>
#include <algorithm>
#include <iostream>
#include <queue>
#include <set>
using namespace std;

const int N = 15e4 + 5; 
string name[N];
char str[300];
int val[N];
pair<int, int> pr[N];
int ans[N];

int main() {
    int T;
    scanf("%d", &T);
    while (T--) {
        int n, m, q;
        scanf("%d%d%d", &n, &m, &q);
        for (int i = 1; i <= n; ++i) {
            scanf("%s%d", str, &val[i]);
            name[i] = str;
        }
        for (int i = 1; i <= m; ++i)
            scanf("%d%d", &pr[i].first, &pr[i].second);
        sort(pr + 1, pr + 1 + m);
        int r = 0, n0 = 0;
        set<pair<int, int> > ext;
        for (int i = 1; i <= m; ++i) {
            int t = pr[i].first, p = pr[i].second;
            while (r < t) {
                ++r;
                ext.insert(make_pair(-val[r], r));
            }
            while (p > 0 && !ext.empty()) {
                --p;
                ans[++n0] = ext.begin() -> second;
                ext.erase(ext.begin());
            }
        }
        while (r < n) {
            ++r;
            ext.insert(make_pair(-val[r], r));
        }
        while (!ext.empty()) {
            ans[++n0] = ext.begin() -> second;
            ext.erase(ext.begin());
        }
        for (int i = 1; i <= q; ++i) {
            int x;
            scanf("%d", &x);
            int len = name[ans[x]].size();
            for (int j = 0; j < len; ++j)
                putchar(name[ans[x]][j]);
            if (i == q) puts("");
            else putchar(' ');
        }
    }
    return 0;
}
