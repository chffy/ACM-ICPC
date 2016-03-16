#include <iostream>
#include <cstdio>
#include <cstring>
#include <vector>
#include <algorithm>
#include <set>
#include <cmath>
#include <stack>
using namespace std;

typedef long long LL;

const int N = 1e5 + 5;

int p[35][35][35];

LL val[N];

struct Trans {
    int num[4], lower[4];
};

vector<Trans> ver;

int get_mark(int ch) {
    if (ch == 'A') return 0;
    if (ch == 'B') return 1;
    if (ch == 'C') return 2;
    return 3;
}

vector<int> son[N];
vector<pair<int, int> > E;
int dfn[N], mark[N], tot, f[N];
stack<int> sta;

int find(int x) {
    if (f[x] != x) f[x] = find(f[x]);
    return f[x];
}

void dfs(int x) {
    dfn[x] = mark[x] = ++tot;
    sta.push(x);
    for (auto y : son[x]) {
        if (dfn[y]) mark[x] = min(mark[x], dfn[y]);
        else {
            dfs(y);
            mark[x] = min(mark[x], mark[y]);
        }
    }
    if (mark[x] == dfn[x]) {
        int y;
        do {
            y = sta.top();  sta.pop();
            f[find(x)] = find(y);
            mark[y] = dfn[y] = 1 << 30;
        } while (y != x);
    }
}

LL dp[N];

LL topsort(int x) {
    if (dp[x] != -1) return dp[x];
    dp[x] = 0;
    for (auto y : son[x]) {
        dp[x] = max(dp[x], topsort(y));
    }
    dp[x] += val[x];
    return dp[x];
}

LL C[35][35];

LL get_value(int i, int j, int k, int l) {
    LL ans = C[i + j][i] * C[i + j + k][k] * C[i + j + k + l][l];
    return ans;
}


class ImpossibleGame {
public:
    LL getMinimum(int K, vector <string> before, vector <string> after) {
        int n = 0;
        for (int i = 0; i < 35; ++i)
            for (int j = 0; j <= i; ++j) {
                if (j == 0) C[i][j] = 1;
                else C[i][j] = (C[i - 1][j] + C[i - 1][j - 1]);
            }
        for (int i = 0; i <= K; ++i)
            for (int j = 0; i + j <= K; ++j)
                for (int k = 0; i + j + k <= K; ++k)
                    p[i][j][k] = ++n;
        for (int i = 0; i < before.size(); ++i) {
            Trans tmp;
            for (int j = 0; j < 4; ++j)
                tmp.num[j] = tmp.lower[j] = 0;
            for (int j = 0; j < before[i].size(); ++j) {
                tmp.num[get_mark(before[i][j])] --;
                tmp.lower[get_mark(before[i][j])]++;
                tmp.num[get_mark(after[i][j])] ++;
            }
            ver.push_back(tmp);
        }
        for (int i = 1; i <= n; ++i)
            f[i] = i;
        for (int i = 0; i <= K; ++i)
            for (int j = 0; i + j <= K; ++j)
                for (int k = 0; i + j + k <= K; ++k) {
                    int t = p[i][j][k];
                    for (auto x : ver) {
                    	if (i < x.lower[0] || j < x.lower[1] || k < x.lower[2] ||
                            K - i - j - k < x.lower[3]) continue;
                        int ti = i + x.num[0], tj = j + x.num[1], tk = k + x.num[2];
                        E.push_back(make_pair(t, p[ti][tj][tk]));
                    }
                    val[t] = get_value(i, j, k, K - i - j - k);
                }
        for (auto x : E)
            son[x.first].push_back(x.second);
        for (int i = 1; i <= n; ++i) {
            if (dfn[i] == 0) dfs(i);
        }
        for (int i = 1; i <= n; ++i) {
            if (find(i) != i)
                val[find(i)] += val[i];
            son[i].clear();
        }
        for (auto x : E)
            if (find(x.first) != find(x.second)) {
                son[find(x.first)].push_back(find(x.second));
            }
        memset(dp, -1, sizeof(dp));
        LL ans = 0;
        for (int i = 1; i <= n; ++i) {
            ans = max(topsort(find(i)), ans);
        }
        return ans;
    }
};
