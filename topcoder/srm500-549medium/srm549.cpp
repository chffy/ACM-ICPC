#include <iostream>
#include <cstdio>
#include <cstring>
#include <algorithm>
#include <vector>
using namespace std;

const int N = 20;
int row[N], col[N], row1[N], col1[N];
pair<int, int> position[N];

int dp[2000000];
int power[13];

int encode(int m, int a[]) {
    int mask = 0;
    for (int i = 0; i < m; ++i)
        mask += a[i] * power[i];
    return mask;
}

void decode(int m, int mask, int a[]) {
    for (int i = 0; i < m; ++i)
        a[i] = mask / power[i] % 3;
}

class MagicalHats {
public:
    int findMaximumReward(vector <string> board, vector <int> coins, int numGuesses) {
        int nx = board.size(), ny = board[0].size();
        int m = 0;
        for (int i = 0; i < nx; ++i)
            for (int j = 0; j < ny; ++j)
                if (board[i][j] == 'H') {
                    position[m++] = make_pair(i, j);
                    row[i] ^= 1;
                    col[j] ^= 1;
                }
        vector<int> opt;
        for (int mask = 0; mask < 1 << m; ++mask)
            if (__builtin_popcount(mask) == coins.size()) {
                memset(row1, 0, sizeof(row1));
                memset(col1, 0, sizeof(col1));
                for (int i = 0; i < m; ++i)
                    if (mask >> i & 1) {
                        row1[position[i].first] ^= 1;
                        col1[position[i].second] ^= 1;
                    }
                int flag = 0;
                for (int i = 0; i < nx; ++i)
                    if ((row[i] ^ row1[i])) {
                        flag = 1;
                    }
                for (int i = 0; i < ny; ++i)
                    if (col[i] ^ col1[i]) {
                    	flag = 1;
                    }
                if (!flag)
                    opt.push_back(mask);
            }
        if (opt.empty()) return -1;
        power[0] = 1;
        for (int i = 1; i <= m; ++i) power[i] = power[i - 1] * 3;
        memset(dp, -1, sizeof(dp));
        for (int mask = 0; mask < 1 << m; ++mask)
            if (__builtin_popcount(mask) == numGuesses) {
                for (int i = 0; i < opt.size(); ++i) {
                    static int a[20];
                    for (int j = 0; j < m; ++j)
                        if (mask >> j & 1) {
                            if (opt[i] >> j & 1)
                                a[j] = 2;
                            else a[j] = 1;
                        } else a[j] = 0;
                    int mask1 = encode(m, a);
                    dp[mask1] = 0;
                }
            }
        for (int mask = power[m] - 1; mask >= 0; --mask)
            if (dp[mask] == -1) {
                static int a[20];
                decode(m, mask, a);
                for (int i = 0; i < m; ++i)
                    if (a[i] == 0) {
                        a[i] = 1;
                        int mask1 = encode(m, a);
                        a[i] = 2;
                        int mask2 = encode(m, a);
                        a[i] = 0;
                        if (dp[mask1] == -1 && dp[mask2] != -1)
                            dp[mask] = max(dp[mask], dp[mask2] + 1);
                        if (dp[mask1] != -1 && dp[mask2] == -1)
                            dp[mask] = max(dp[mask], dp[mask1]);
                        if (dp[mask1] != -1 && dp[mask2] != -1)
                            dp[mask] = max(dp[mask], min(dp[mask1], dp[mask2] + 1));
                    }
            }
        int ans1 = dp[0], ans = 0;
        sort(coins.begin(), coins.end());
        for (int i = 0; i < ans1; ++i)
            ans += coins[i];
        return ans;
    }
};
