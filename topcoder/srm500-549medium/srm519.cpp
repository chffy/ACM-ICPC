#include <iostream>
#include <cstring>
#include <cstdio>
#include <vector>
#include <queue>
using namespace std;

int f[400][26], tot;
int dp[55][400][1 << 6], mask[400];
const int P = 1e9 + 9;

void build(int x, char *str, int ma) {
    if (*str == (char)0) {
        mask[x] |= ma;
        return ;
    }
    int ch = *str - 'a';
    int y = f[x][ch];
    if (y == 0) {
        f[x][ch] = y = ++tot;
    }
    build(y, str + 1, ma);
}

int fail[400];

void AC() {
    memset(fail, 0, sizeof(fail));
    queue<int> que;
    que.push(0);
    while (!que.empty()) {
        int x = que.front(); que.pop();
        for (int i = 0; i < 26; ++i)
            if (f[x][i] != 0) {
                int y = f[x][i];
                int t = fail[x];
                while (t != 0 && f[t][i] == 0)
                    t = fail[t];
                if (f[t][i] != 0 && f[t][i] != y)
                    t = f[t][i];
                fail[y] = t;
                mask[y] |= mask[t];
                que.push(y);
            }
    }
}

class RequiredSubstrings {
public:

    void updata(int &x, int y) {
        x += y;
        if (x >= P) x -= P;
    }
    
    int solve(vector <string> words, int C, int L) {
        int n = words.size();
        for (int i = 0; i < n; ++i) {
            char str[100];
            memcpy(str, words[i].c_str(), sizeof(str));
            build(0, str, 1 << i);
        }
        AC();
        dp[0][0][0] = 1;
        for (int i = 0; i < L; ++i)
            for (int j = 0; j <= tot; ++j)
                for (int k = 0; k < 1 << n; ++k) {
                    if (dp[i][j][k] == 0) continue;
                    for (int l = 0; l < 26; ++l) {
                        int y = j;
                        while (y != 0 && f[y][l] == 0)
                            y = fail[y];
                        if (f[y][l] != 0)
                            y = f[y][l];
                        updata(dp[i + 1][y][k | mask[y]], dp[i][j][k]);
                    }
                }
        int ans = 0;
        for (int i = 0; i < 1 << n; ++i)
            if (__builtin_popcount(i) == C)
                for (int j = 0; j <= tot; ++j)
                    updata(ans, dp[L][j][i]);
        return ans;
    }
};
