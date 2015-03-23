#include <iostream>
#include <cstdio>
#include <cstring>
#include <algorithm>
#include <vector>
using namespace std;

int map[105][105];
const int C[4] = {1, -1, 0, 0};
const int D[4] = {0, 0, 1, -1};

int dfs(int x, int y, int cx, int cy) {
    if (map[x][y] == -1) return 0;
    if (map[x][y] == 1) return -1;
    int num = dfs(x + cx, y + cy, cx, cy);
    if (num == -1) return num;
    else return num + 1;
}

class RobotOnMoon {
public:
    int longestSafeCommand(vector <string> board) {
	int n = board.size(), m = board[0].size();
	memset(map, -1, sizeof(map));
	pair<int, int> S;
	for (int i = 0; i < n; ++i)
	    for (int j = 0; j < m; ++j) {
		if (board[i][j] == '#') map[i + 1][j + 1] = 1;
		else map[i + 1][j + 1] = 0;
		if (board[i][j] == 'S') S = make_pair(i + 1, j + 1);
	    }
	int ans = 0;
	for (int i = 0; i < 4; ++i) {
	    int x = dfs(S.first + C[i], S.second + D[i], C[i], D[i]);
	    if (x == -1) return -1;
	    ans += x;
	}
	return ans;
    }
};
