#include <iostream>
#include <cstdio>
#include <cstring>
#include <algorithm>
#include <vector>
using namespace std;

typedef long long LL;
const int P = 1e9 + 7;
const int N = 55;

int first[N * 2], tot;

struct Edge {
    int y, wi, nex;
}edge[N * N * 10];

void addedge(int x, int y, int s) {
    edge[tot] = (Edge) {y, s, first[x]};
    first[x] = tot++;                                          
}

int bo[N * 2], bo1[N * 2], n, m;
int val[N * 2];

int dfs(int x, int t) {
    int flag = 0;
    if (t == 0 && x <= n) flag = 1;
    if (t > 9 || t < 0) flag = -1;
    bo1[x] = 1;
    val[x] = t;
    for (int k = first[x]; ~k; k = edge[k].nex) {
        int y = edge[k].y;
        if (bo1[y]) {
            if (val[y] + val[x] != edge[k].wi)
                flag = -1;
        }
        else {
            int K = dfs(y, edge[k].wi - t);
            if (K == -1) flag = -1;
            if (K == 1 && flag != -1) flag = 1;
        }
    }
    return flag;
}

class EqualSums {
public:
    int count(vector <string> board) {
        n = board.size(), m = board[0].size();
        memset(first, -1, sizeof(first));
        tot = 0;
        for (int i = 0; i < n; ++i)
            for (int j = 0; j < m; ++j)
                if (board[i][j] != '-') {
                    int s = board[i][j] - '0';
                    addedge(i + 1, j + n + 1, s);
                    addedge(j + n + 1, i + 1, s);
                }
        int ans1 = 0, ans0 = 1;
        for (int i = 1; i <= n + m; ++i)
            if (!bo[i]) {
                int res0 = 0, res1 = 0;
                for (int j = 0; j < 10; ++j) {
                    memcpy(bo1, bo, sizeof(bo1));
                    int flag = dfs(i, j);
                    if (flag == -1) continue;
                    if (flag == 0) res0 ++;
                    else res1 ++;
                }
                //printf("%d %d %d\n", i, res0, res1);
                memcpy(bo, bo1, sizeof(bo));
                int tmp = ans0;
                ans0 = (LL)ans0 * res0 % P;
                ans1 = ((LL)tmp * res1 + (LL)ans1 * (res0 + res1)) % P;
            }
        return ans1;
    }
};
