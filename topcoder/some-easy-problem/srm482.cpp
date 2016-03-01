#include <iostream>
#include <cstdio>
#include <cstring>
#include <vector>
#include <queue>
#include <algorithm>
using namespace std;

int a[2000005];

class LockersDivOne {
public:
    int lastOpened(int n) {
        int res = -1;
        for (int i = 1; i <= n; ++i)
            a[i] = i;
        for (int j = 1; n > 0; ++j) {
            for (int i = 1; i <= n; i += j + 1) {
                res = a[i];
                a[i] = 0;
            }
            int m = 0;
            for (int i = 1; i <= n; ++i)
                if (a[i] != 0) a[++m] = a[i];
            n = m;
        }
        return res;
    }
};
