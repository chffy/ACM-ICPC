#include <iostream>
#include <cstdio>
#include <cstring>
#include <algorithm>
#include <vector>
using namespace std;
 
int grid[100][100];
int bo[100][100];
 
class BichromePainting {
public:
    string isThatPossible(vector <string> board, int k) {
        int n = board.size(), m = board[0].size();
        for (int K = 0; K <= n * n; ++K) {
            int flag = 0;
            for (int i = 0; i + k <= n; ++i)
                for (int j = 0; j + k <= m; ++j) {
                    int opt = 0;
                    for (int ii = i; ii < i + k; ++ii)
                        for (int jj = j; jj < j + k; ++jj)
                            if (!bo[ii][jj])
                                opt |= 1 << (board[ii][jj] == 'B');
                    if (opt == 3 || opt == 0) continue;
                    for (int ii = i; ii < i + k; ++ii)
                        for (int jj = j; jj < j + k; ++jj)
                            if (!bo[ii][jj]) {
                                if (opt == 2) grid[ii][jj] = 1;
                                else grid[ii][jj] = 0;
                                bo[ii][jj] = 1;
                            }
                    flag = 1;
                }
            if (!flag) break;
        }
        for (int i = 0; i < n; ++i)
            for (int j = 0; j < m; ++j)
                if (grid[i][j] != (board[i][j] == 'B')) return "Impossible";
        return "Possible";
    }
};
