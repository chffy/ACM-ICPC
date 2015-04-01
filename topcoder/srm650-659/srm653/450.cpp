#include <iostream>
#include <cstdio>
#include <cstring>
#include <algorithm>
#include <vector>
#include <cassert>
using namespace std;
 
const int N = 1005;
int first[1005], tot, cur[1005], d[1005];
 
struct Edge {
    int y, s, nex;
}edge[N * 20];
 
int S, T;
 
void addedge(int x, int y, int s) {
    edge[tot] = (Edge) {y, s, first[x]};
    first[x] = tot++;
}
 
void add(int x, int y, int s) {
    addedge(x, y, s);
    addedge(y, x, 0);
}
 
bool bfs() {
    memset(d, -1, sizeof(d));
    static int queue[N];
    int head = 1, tail = 1;
    queue[1] = T;
    d[T] = 1;
    while (head <= tail) {
        int x = queue[head++];
        for (int k = first[x]; ~k; k = edge[k].nex)
            if (edge[k ^ 1].s && (d[edge[k].y] == -1)) {
                d[edge[k].y] = d[x] + 1;
                queue[++tail] = edge[k].y;
            }
    }
    return d[S] != -1;
}
 
int dfs(int x, int flow) {
    if (x == T) return flow;
    int sum = 0;
    for (int &k = cur[x]; ~k; k = edge[k].nex) {
        int y = edge[k].y;
        if (d[y] == d[x] - 1 && edge[k].s) {
            int tmp = dfs(y, min(edge[k].s, flow));
            edge[k].s -= tmp;
            edge[k ^ 1].s += tmp;
            sum += tmp;
            flow -= tmp;
            if (!flow) break;
        }
    }
    if (!sum) d[x] = -1;
    return sum;
}
 
class Singing {
public:
    int solve(int N, int low, int high, vector <int> pitch) {
        int n = pitch.size();
        S = N + 1, T = S + 1;
        memset(first, -1, sizeof(first));
        for (int i = 0; i + 1 < n; ++i) {
            if (pitch[i] != pitch[i + 1]) {
                add(pitch[i], pitch[i + 1], 1);
                add(pitch[i + 1], pitch[i], 1);
            }
        }
        for (int i = 1; i <= N; ++i)
            if (i < low) add(S, i, 1 << 30);
            else if (i > high) add(i, T, 1 << 30);
        int ans = 0;
        while (bfs()) {
            memcpy(cur, first, sizeof(cur));
            ans += dfs(S, 1 << 30);
        }
        return ans;
    }
};
