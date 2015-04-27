#include <iostream>
#include <cstdio>
#include <cstring>
#include <vector>
#include <algorithm>
using namespace std;

int graph[55][55], f[55][55], parent[55], sumn[55], summ[55], degree[55], bo[55], pp[55], grid[55][55];
int dp[55], bo1[55];

typedef long long LL;
const int P = 1e9 + 7;

int find(int x) {
    if (parent[x] != x) parent[x] = find(parent[x]);
    return parent[x];
}

int n;

void dfs(int x) {
    if (bo1[x]) {
    	int mm = summ[x];
    	if (sumn[x] > 1 || mm != 0)
    		for (int i = 1; i <= n; ++i)
    			if (grid[x][i]) mm = 1 << 30;
    	if (mm > sumn[x]) dp[x] = -1;
    }
    bo[x] = 1;
    for (int i = 1; i <= n; ++i)
        if (grid[x][i]) {
            if (bo1[x]) {
                if (dp[x] != -1 && dp[i] != -1) dp[i] = (dp[i] + (LL)dp[x] * grid[x][i]) % P;
                else dp[i] = -1;
                bo1[i] = 1;
            }
            if (--degree[i] == 0) {
                dfs(i);
            }
        }
}

class MonsterFarm {
public:
    int numMonsters(vector <string> transforms) {
        n = transforms.size();
        for (int i = 0; i < n; ++i) {
            int m = transforms[i].size();
            for (int j = 0; j < m; ++j)
                if (isdigit(transforms[i][j])) {
                    int x = 0;
                    while (j < m && isdigit(transforms[i][j])) {
                        x = x * 10 + transforms[i][j] - '0';
                        ++j;
                    }
                    graph[i + 1][x]++;
                    f[i + 1][x] = 1;
                    j = j - 1;
                }
        }
        for (int k = 1; k <= n; ++k)
            for (int i = 1; i <= n; ++i)
                for (int j = 1; j <= n; ++j)
                    f[i][j] |= f[i][k] & f[k][j];
        for (int i = 1; i <= n; ++i)
            parent[i] = i;
        for (int i = 1; i <= n; ++i)
            for (int j = 1; j <= n; ++j)
                if (f[i][j] && f[j][i]) parent[find(i)] = find(j);
        for (int i = 1; i <= n; ++i)
            for (int j = 1; j <= n; ++j)
                if (graph[i][j]) {
                    if (find(i) == find(j))
                        summ[find(i)] += graph[i][j];
                    else {
                        grid[find(i)][find(j)] += graph[i][j];
                        ++degree[find(j)];
                    }
                }
        for (int i = 1; i <= n; ++i) ++sumn[find(i)];
        dp[find(1)] = 1;
        bo1[find(1)] = 1;
        for (int i = 1; i <= n; ++i)
            if (!bo[find(i)] && degree[find(i)] == 0 && find(i) == i) dfs(i);
        int ans = 0;
        for (int i = 1; i <= n; ++i)
            if (find(i) == i) {
            	int flag = 0;
            	for (int j = 1; j <= n; ++j)
            		if (grid[i][j]) flag = 1;
            	if (flag) continue;
                if (dp[i] == -1) return -1;
                ans = (ans + dp[i]) % P;
            }
        return ans;
    }
};
