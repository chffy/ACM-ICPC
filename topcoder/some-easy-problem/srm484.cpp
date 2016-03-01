#include <iostream>
#include <cstdio>
#include <cstring>
#include <vector>
#include <queue>
#include <algorithm>
using namespace std;

typedef long long LL;

int ans;

int S(LL x) {
    int res = 0;
    while (x > 0) {
        res += x % 10;
        x /= 10;
    }
    return res;
}

void dfs(int x, LL y, int low, int high) {
    if (y > high) return;
    if (x == 10) {
        if (y < low) return ;
       	if ((LL)S(y) * S(y) == S(y * y)) ++ans;
        return ;
    }
    for (int i = 0; i < 4; ++i)
        dfs(x + 1, y * 10 + i, low, high);
}

class RabbitNumber {
public:
    int theCount(int low, int high) {
        ans = 0;
        dfs(0, 0, low, high);
        return ans;
    }
};
