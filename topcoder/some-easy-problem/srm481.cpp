#include <iostream>
#include <cstdio>
#include <cstring>
#include <vector>
#include <queue>
#include <algorithm>
using namespace std;

int check(int n, int ec, int lc, int ac) {
    for (int i = 0; i <= ec && i <= ac; ++i) {
        if (ac - i > n - ec) continue;
        int egg = (ac - i) + ec - i;
        int chi = i + (n - ec - (ac - i));
        if (chi != lc) continue;
        return 1;
    }
    return 0;
}

class ChickenOracle {
public:
    string theTruth(int n, int eggCount, int lieCount, int liarCount) {
        int flag = 2 * check(n, eggCount, lieCount, liarCount) +
            check(n, n - eggCount, lieCount, liarCount);
        if (flag == 3) return "Ambiguous";
        if (flag == 1) return "The chicken";
        if (flag == 2) return "The egg";
        return "The oracle is a lie";
    }
    
};
