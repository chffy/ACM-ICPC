#include <iostream>
#include <cstdio>
#include <cstring>
#include <vector>
#include <algorithm>
#include <cmath>
using namespace std;

int check(int z) {
    if (z < 2) return 1;
    int y = sqrt(z);
    while (y * y < z) ++y;
    if (y * y == z) return 1;
    return 0;
}

class FindingSquareInTable {
public:
    
    int findMaximalSquare(vector <string> table) {
        int n = table.size(), m = table[0].size();
        int ans = -1;
        for (int i = 0; i < n; ++i)
            for (int j = 0; j < m; ++j) {
                for (int k = -n; k <= n; ++k)
                    for (int l = -m; l <= m; ++l)
                        if (k != 0 || l != 0) {
                            int x = i, y = j;
                            int z = 0;
                            while (x >= 0 && x < n && y >= 0 && y < m) {
                                z = z * 10 + table[x][y] - '0';
                                
                            if (check(z)) ans = max(ans, z);
                                x += k;
                                y += l;
                            }
                        }
                
            }
        return ans;
    }
};
