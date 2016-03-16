#include <iostream>
#include <cstdio>
#include <cstring>
#include <vector>
#include <algorithm>
#include <set>
#include <cmath>
#include <stack>
using namespace std;
       
int num[26] = {2, 2, 2, 3, 3, 3, 4, 4, 4, 5, 5, 5, 6, 6, 6, 7, 7, 7, 7, 8, 8, 8, 9, 9, 9, 9};

const int N = 1e5 + 5;

int f[N][26], mn[N];
int tot;

void build(int &x, int p, string &s, int val) {
    if (x == -1) {
        x = tot++;
        memset(f[x], -1, sizeof(f[x]));
        mn[x] = 1 << 29;
    }
    if (p + 1 == s.size() || p == s.size()) {
        mn[x] = min(mn[x], val + 1);
    }
    if (p == s.size()) return ;
    build(f[x][s[p] - 'a'], p + 1, s, val);
}

int dp[55];

class QuickT9 {
public:
    int minimumPressings(vector <string> t9, string word) {
        vector<string> tmp;
        for (auto str : t9) {
            int p = 0;
            while (p < str.size()) {
                string s = "";
                while (p < str.size() && isalpha(str[p])) {
                    s += str[p];
                    ++p;
                }
                tmp.push_back(s);
                ++p;
            }
        }
        t9 = tmp;
        int n = t9.size();
        int root = -1;
        for (int i = 0; i < n; ++i)
            for (int j = 1; j <= t9[i].size(); ++j) {
                vector<string> ver;
                for (int k = 0; k < n; ++k) {
                    if (t9[k].size() < j) continue;
                    int flag = 1;
                    string s = "";
                    for (int l = 0; l < j; ++l)
                        if (num[t9[k][l] - 'a'] != num[t9[i][l] - 'a']) {
                            flag = 0;
                            break;
                        }
                    else s += t9[k][l];
                    if (flag == 1) ver.push_back(s);
                }
                sort(ver.begin(), ver.end());
                ver.erase(unique(ver.begin(), ver.end()), ver.end());
                for (int k = 0; k < ver.size(); ++k) {
                    build(root, 0, ver[k], k + j);
                }
            }
        for (int i = tot - 1; i >= 0; --i)
            for (int j = 0; j < 26; ++j)
                if (f[i][j] != -1) mn[i] = min(mn[i], mn[f[i][j]] + 1);
        int m = word.size();
        memset(dp, 63, sizeof(dp));
        dp[0] = 0;
        for (int i = 0; i < m; ++i) {
            int x = root;
            for (int j = 1; i + j <= m; ++j) {
                x = f[x][word[i + j - 1] - 'a'];
                if (x == -1) break;
                dp[i + j] = min(dp[i + j], dp[i] + mn[x]);
            }
        }
        if (dp[m] > 100000000) dp[m] = -1;
        return dp[m];
    }
};

