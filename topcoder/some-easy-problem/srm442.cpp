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

const int N = 1e5 + 5;

int bo[N];

class Underprimes {
public:
    int howMany(int A, int B) {
        for (int i = 2; i < N; ++i)
            if (!bo[i]) {
                for (int j = i; j < N; j += i)
                    bo[j] = i;
            }
        int ans = 0;
        for (int i = A; i <= B; ++i) {
            int x = i, num = 0;
            while (x > 1) {
                ++num;
                x /= bo[x];
            }
            if (bo[num] == num) ++ans;
        }
        return ans;
    }
};
