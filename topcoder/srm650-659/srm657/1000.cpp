#include <iostream>
#include <cstdio>
#include <cstring>
#include <algorithm>
#include <vector>
using namespace std;

typedef long long LL;
const int P = 1e9 + 7;

int bo[55];
int f[2][55][55], a[50], b[50], bb[50], markr[50], markc[50];
int xx[50], yy[50];

class RookGraph {
public:
    int countPlacements(int n, vector <string> graph) {
        int m = graph.size();
        int cur = 0, nex = 1;
        f[cur][n][n] = 1;
        memset(bo, -1, sizeof(bo));
        for (int i = 0; i < m; ++i)
            if (bo[i] == -1) {
                xx[i] = yy[i] = 1;
                bo[i] = i;
               // printf("%d\n", i);
                while (1) {
                    int k = -1;
                    for (int j = 0; j < m; ++j)
                        if (bo[j] == -1) {
                            int l;
                            for (l = 0; l < m; ++l)
                                if (bo[l] != -1 && graph[j][l] == '1')
                                    break;
                            if (l < m) {
                                k = j;
                                break;
                            }
                        }
                    if (k == -1) break;
                    xx[k] = yy[k] = 0;
                    for (int x = 1; x <= n && xx[k] == 0; ++x)
                        for (int y = 1; y <= n && yy[k] == 0; ++y) {
                            int flag = 1;
                            for (int j = 0; j < m; ++j)
                                if (bo[j] == i) {
                                    if (graph[k][j] == '1' && (xx[j] != x && yy[j] != y))
                                        flag = 0;
                                    if (graph[k][j] == '0' && (xx[j] == x || yy[j] == y))
                                        flag = 0;
                                	if (xx[j] == x && yy[j] == y) flag = 0;
                                	//printf("%d %d\n", k, j);
                                }
                            if (flag) {
                                xx[k] = x;
                                yy[k] = y;
                            }
                        }
                    bo[k] = i;
                  //  printf("%d\n", k);
                    if (xx[k] == 0) return 0;
                }
            }
        memset(bo, 0, sizeof(bo));
        memset(markr, -1, sizeof(markr));
        memset(markc, 0, sizeof(markc));
        for (int i = 0; i < m; ++i)
            if (!bo[i]) {
                memset(f[nex], 0, sizeof(f[nex]));
                memcpy(bb, bo, sizeof(bb));
                for (int r = 0; r <= n; ++r)
                    for (int c = 0; c <= n; ++c)
                        if (f[cur][r][c]) {
                            memcpy(bo, bb, sizeof(bb));
                            int ans = (LL)f[cur][r][c] * r * c % P;
                            bo[i] = 1;
                            vector<int> a1, a2;
                            int r1 = r - 1, c1 = c - 1;
                            int r2 = c - 1, c2 = r - 1;
                            int tmp1 = 1, tmp2 = 1;
                            int sum = 0;
                            for (int j = 0; j < m; ++j)
                                if (!bo[j] && graph[i][j] == '1') {
                                    bo[j]  = 1;
                                    ++sum;
                                    if (a1.empty()) {
                                        tmp1 = (LL)tmp1 * r1 % P;
                                        tmp2 = (LL)tmp2 * r2 % P;
                                        a1.push_back(j);
                                        continue;
                                    }
                                    if (graph[a1[0]][j] == '1') {
                                        tmp1 = (LL)tmp1 * (r1 - a1.size()) % P;
                                        tmp2 = (LL)tmp2 * (r2 - a1.size()) % P;
                                        a1.push_back(j);
                                    }
                                    else {
                                        tmp1 = (LL)tmp1 * (c1 - a2.size()) % P;
                                        tmp2 = (LL)tmp2 * (c2 - a2.size()) % P;
                                        a2.push_back(j);
                                    }
                                }
                            for (int z1 = 0, z2 = 0; z1 < a1.size() || z2 < a2.size(); ) {
                                int a1len = a1.size(), a2len = a2.size();
                                if (z1 < a1len) {
                                    while (1) {
                                        int K = -1;
                                        for (int j = 0; j < m; ++j)
                                            if (!bo[j] && graph[a1[z1]][j] == '1') {
                                                K = j;
                                                break;
                                            }
                                        if (K == -1) break;
                                        bo[K] = 1;
                                        int flag = 0;
                                        for (int j = 0; j < a2len; ++j)
                                            if (graph[K][a2[j]] == '1') flag = 1;
                                        if (flag) {
                                            tmp1 = (LL)tmp1 * (c1 - a2.size()) % P;
                                            tmp2 = (LL)tmp2 * (c2 - a2.size()) % P;
                                        }
                                    }
                                    ++z1;
                                }
                                
                                if (z2 < a2len) {
                                    while (1) {
                                        int K = -1;
                                        for (int j = 0; j < m; ++j)
                                            if (!bo[j] && graph[a2[z2]][j] == '1') {
                                                K = j;
                                                break;
                                            }
                                        if (K == -1) break;
                                        bo[K] = 1;
                                        int flag = 0;
                                        for (int j = 0; j < a1len; ++j)
                                            if (graph[K][a1[j]] == '1') flag = 1;
                                        if (flag) {
                                            tmp1 = (LL)tmp1 * (r1 - a1.size()) % P;
                                            tmp2 = (LL)tmp2 * (r2 - a1.size()) % P;
                                        }
                                    }
                                    ++z2;
                                }
                            }
                            r1 -= a1.size();
                            r2 -= a1.size();
                            c1 -= a2.size();
                            c2 -= a2.size();
                            if (r1 >= 0 && c1 >= 0)
                                f[nex][r1][c1] = (f[nex][r1][c1] + (LL)tmp1 * ans) % P;
                            if (r2 >= 0 && c2 >= 0 && !(r1 == r - 1 && c1 == c - 1))
                                f[nex][r2][c2] = (f[nex][r2][c2] + (LL)tmp2 * ans) % P;
                        }
                swap(cur, nex);
            }
        int ans = 0;
        for (int i = 0; i <= n; ++i)
            for (int j = 0; j <= n; ++j)
                ans = (ans + f[cur][i][j]) % P;
        return ans;
    }
};
