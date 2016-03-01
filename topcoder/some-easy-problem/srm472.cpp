#include <iostream>
#include <cstdio>
#include <cstring>
#include <vector>
#include <queue>
#include <map>
#include <algorithm>
#include <set>
using namespace std;

int C[4] = {0, -1, 0, 1};
int D[4] = {1, 0, -1, 0};
int f[100];

class PotatoGame {
public:
    string theWinner(int n) {
        memset(f, -1, sizeof(f));
        int ans = 0;
        if (n >= 1 && (n - 1) % 5 == 0)
            ans = 1;
        if (n >= 3 && (n - 3) % 5 == 0)
            ans = 1;
        if (n >= 4 && (n - 4) % 5 == 0)
            ans = 1;
        if (ans) return "Taro";
        else return "Hanako";
    }
};
