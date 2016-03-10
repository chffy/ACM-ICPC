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

const int C[4] = {1, 0, -1, 0};
const int D[4] = {0, -1, 0, 1};

char grid[3][3] = {{'G', 'B', 'B'},
                   {'B', 'R', 'R'},
                   {'B', 'R', 'R'}};

class CubeWalking {
public:
    string finalPosition(string mov) {
        int x = 0, y = 0, dic = 0;
        for (auto ch : mov) {
            if (ch == 'W') {
                x = (x + C[dic] + 3) % 3; 
                y = (y + D[dic] + 3) % 3;
            }
            else if (ch == 'L') {
                dic = (dic + 3) % 4;
            }
            else dic = (dic + 1) % 4;
        }
        if (grid[x][y] == 'G') return "GREEN";
        else if (grid[x][y] == 'B') return "BLUE";
        else return "RED";
    }
};
