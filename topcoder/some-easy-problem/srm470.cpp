#include <iostream>
#include <cstdio>
#include <cstring>
#include <vector>
#include <queue>
#include <map>
#include <algorithm>
#include <set>
using namespace std;

int f[1 << 16];
int bo[1 << 16];

int open(char c, int mask) {
    if (mask >> (c - 'A') & 1) return 0;
    return 1;
}

int dp(int mask, string &dr, int tr) {
    if (bo[mask]) return f[mask];
   // printf("%d\n", mask);
    bo[mask] = 1;
    int x = 0;
    for (int i = 1; i <= tr; ++i)
        if (open(dr[i - 1], mask))
            x = i;
        else break;
    int y = dr.size() + 1;
    for (int i = (int)dr.size() - 1; i >= tr; --i)
        if (open(dr[i], mask))
            y = i;
        else break;
    if (x == tr && y == tr) return f[mask] = 0;
    else if (x == tr) return f[mask] = 1;
    else if (y == tr) return f[mask] = -1;
    vector<int> ver;
    for (int i = 0; i < 16; ++i)
        if (mask >> i & 1)  {
            string T = dr;
            reverse(T.begin(), T.end());
            int c = dp(mask ^ (1 << i), T, (int)dr.size() - tr);
            ver.push_back(-c);
        }
    sort(ver.begin(), ver.end());
    int flag = -1;
    for (int i = 0; i < ver.size(); ++i)
        if (ver[i] > 0) {
            flag = i;
            break;
        }
    if (flag != -1) {
        return f[mask] = ver[flag] + 1;
    }
    if (ver.back() == 0) return f[mask] = 0;
    return f[mask] = ver[0] - 1;
}

class DoorsGame {
public:
    int determineOutcome(string doors, int trophy) {
        int c = dp((1 << 16) - 1, doors, trophy);
        if (c > 0) c --;
        if (c < 0) c ++;
        return c;
    }
};
