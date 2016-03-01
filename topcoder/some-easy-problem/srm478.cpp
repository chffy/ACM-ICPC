#include <iostream>
#include <cstdio>
#include <cstring>
#include <vector>
#include <queue>
#include <map>
#include <algorithm>
using namespace std;

typedef long long LL;
const int P = 1e9 + 7;

class CarrotJumping {
public:
    int theJump(int init) {
        int x = (init + 1) % P;
        int num = 0;
        while (num <= 300000 && x != 1) {
            ++num;
            x = x * 2 % P;
        }
        int ans = 1 << 30;
        for (int i = 0; i * 3 <= num; ++i)
            if ((num - i * 3) % 2 == 0) {
                ans = min(ans, i + (num - i * 3) / 2);
            }
        if (ans > 100000) ans = -1;
        return ans;
    }
};
