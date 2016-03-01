#include <iostream>
#include <cstdio>
#include <cstring>
#include <vector>
#include <queue>
#include <map>
#include <algorithm>
using namespace std;

int C[2][6] = {{-1, -1, 0, 0, 1, 1}, {-1, -1, 0, 0, 1, 1}};
int D[2][6] = {{-1, 0, -1, 1, -1, 0}, {1, 0, -1, 1, 1, 0}};

class Islands {
public:
    int beachLength(vector <string> kingdom) {
        int n = kingdom.size();
        int m = kingdom[0].size();
        int ans = 0;
        for (int i = 0; i < n; ++i)
            for (int j = 0; j < m; ++j)
                if (kingdom[i][j] == '.') {
                    for (int k = 0; k < 6; ++k) {
                        int x = i + C[i & 1][k];
                        int y = j + D[i & 1][k];
                        if (x < n && x >= 0 && y < m && y >= 0) {
                            if (kingdom[x][y] == '#')
                                ++ans;
                        }
                    }                    
                }
        return ans;
    }
};
