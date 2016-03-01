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

int deal(LL x, string ID) {
    int n = ID.size();
    int ans = 0;
    for (int i = 0; i < n; ++i) {
        ans += (((LL)ID[i] - '0') != (x % 10));
        x /= 10;
    }
    if (x != 0) ans = 1 << 30;
    return ans;
}

class LotteryCheating {
public:
    int minimalChange(string ID) {
        reverse(ID.begin(), ID.end());
        int ans = 1 << 30;
        for (int i = 0; i <= 100000; ++i) {
            ans = min(ans, deal((LL)i * i, ID));
        }
        return ans;
    }
};
