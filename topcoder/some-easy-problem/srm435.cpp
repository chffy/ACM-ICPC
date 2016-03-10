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

int bo[100];

class CellRemoval {
public:
    int cellsLeft(vector <int> parent, int deletedCell) {
        int n = parent.size();
        bo[deletedCell] = 1;
        for (int i = 1; i <= n; ++i)
            for (int j = 0; j < n; ++j)
                if (parent[j] != -1)
                    bo[j] |= bo[parent[j]];
        for (int i = 0; i < n; ++i)
            if (parent[i] != -1)
                bo[parent[i]] = 1;
        int ans = 0;
        for (int i = 0; i < n; ++i)
            ans += bo[i] ^ 1;
        return ans;
    }
};
