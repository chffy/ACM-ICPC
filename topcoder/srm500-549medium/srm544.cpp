#include <iostream>
#include <cstdio>
#include <cstring>
#include <vector>
#include <algorithm>
using namespace std;

int b[55];
int grid[55][55];

class FlipGame {
public:
    
    int minOperations(vector <string> board) {
        int n = board.size(), m = board[0].size();
        for (int i = 0; i < n; ++i)
            for (int j = 0; j < m; ++j)
                grid[i][j] = (board[i][j] == '1');
        int ans = 0;
        for (int T = 0; T <= n * m; ++T) {
            memset(b, -1, sizeof(b));
            for (int i = 0; i < n; ++i)
                for (int j = 0; j < m; ++j)
                    if (grid[i][j]) b[i] = j;
            for (int i = 1; i < n; ++i)
                b[i] = max(b[i], b[i - 1]);
            if (b[n - 1] == -1) break;
            ++ans;
            for (int i = 0; i < n; ++i)
                for (int j = 0; j <= b[i]; ++j)
                    grid[i][j] ^= 1;
        }
        return ans;
    }
};
