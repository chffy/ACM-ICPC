#include <iostream>
#include <cstdio>
#include <cstring>
#include <algorithm>
#include <vector>
using namespace std;

typedef long long LL;
const int N = 1005;
const int P = 1e9 + 7;
int C[N][N];

class RockPaperScissorsMagic {
public:
    
    int count(int win, int lose, int tie, vector <int> card) {
        int n = card.size();
        if (win == lose && win == tie) {
            int ans = 1;
            for (int i = 1; i <= n; ++i) {
                ans = (LL)ans * 3 % P;
            }
            return ans;
        }
        for (int i = 0; i < N; ++i) {
            C[i][0] = 1;
            for (int j = 1; j <= i; ++j)
                C[i][j] = (C[i - 1][j - 1] + C[i - 1][j]) % P;
        }
        int cnt[3];
        memset(cnt, 0, sizeof(cnt));
        for (int i = 0; i < n; ++i) ++cnt[card[i]];
        sort(cnt, cnt + 3);
       
        if ((cnt[1] - cnt[0]) % 3 == 0 && (cnt[2] - cnt[1]) % 3 == 0) {
            int ans = 0;
            int e1 = (cnt[1] - cnt[0]) / 3;
            int e2 = (cnt[2] - cnt[1]) / 3;
            for (int x = 0; x <= cnt[0]; ++x)
                for (int y = 0; x + y <= cnt[1]; ++y) {
                    ans += (LL)C[cnt[0]][x] * C[cnt[0] - x][y] % P *
                        C[cnt[1]][x + e1] % P * C[cnt[1] - x - e1][y + e1] % P *
                        C[cnt[2]][x + e2] % P * C[cnt[2] - x - e2][y + e2] % P;
                    ans %= P;
                }
            return ans;
        }
        else return 0;
    }
};
