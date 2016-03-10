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

vector<int> LS;
typedef long long LL;

struct Opt {
    int x, d;
    LL num;

    int operator < (const Opt &a) const {
        return make_pair(num, x) > make_pair(a.num, a.x);
    }
};

set<int> ext;

LL getnum(int x) {
    for (auto y : LS)
        if (y == x) return 0;
    if (x < LS.front()) return (LL)x * (LS.front() - x);
    if (x > LS.back()) return 1LL << 60;
    for (int i = 0; i + 1 < LS.size(); ++i)
        if (x > LS[i] && x < LS[i + 1])
            return (LL)(LS[i + 1] - x) * (x - LS[i]);
}

class UnluckyIntervals {
public:
    vector <int> getLuckiest(vector <int> luckySet, int n) {
        LS = luckySet;
        sort(LS.begin(), LS.end());
        priority_queue<Opt> que;
        vector<int> ans;
        for (auto x : LS) {
            ans.push_back(x);
            ext.insert(x);
        }
        for (int i = 0, j = 1; i < LS.size(); ++i) {
            if (LS[i] - j == 1) {
                ans.push_back(j);
                ext.insert(j);
            }
            j = LS[i] + 1;
        }
        sort(ans.begin(), ans.end());
        if (!ext.count(1)) que.push((Opt){1, 1, getnum(1)});
        for (auto x : LS) {
            if (!ext.count(x + 1))que.push((Opt) {x + 1, 1, getnum(x + 1)});
            if (!ext.count(x - 1) && x > 1)
                que.push((Opt) {x - 1, -1, getnum(x - 1)});
        }
        if (ans.size() > n) ans.resize(n);
        while (ans.size() < n) {
            int x, d;
            do {
                x = que.top().x, d = que.top().d;
                que.pop();
            } while (ext.count(x));
            if (x + d > 0 && !ext.count(x + d))
                que.push((Opt) {x + d, d, getnum(x + d)});
           // cout << x + d << endl;
            ans.push_back(x);
            ext.insert(x);
           // printf("%d %lld %lld\n", x, getnum(x), getnum(2));
        }
        return ans;
    }
};
