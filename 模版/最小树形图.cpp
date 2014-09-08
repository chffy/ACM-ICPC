int used[N], pass[N], eg[N], more, queue[N];

void combine(int id, int &sum) {
    if (sum == -1) return ;
    int tot = 0, from, i, j, k;
    for (; id != 0 && !pass[id]; id = eg[id]) {
        queue[tot++] = id;
        pass[id] = 1;
    }
    for (from = 0; from < tot && queue[from] != id; ++from);
    if (from == tot) return;
    more = 1;
    for (i = from; i < tot; ++i) {
        sum +=g[eg[queue[i]]][queue[i]];
        if (sum > 1000000000) sum = -1;
        if (sum == -1) return ;
        if (i != from) {
            used[queue[i]] = 1;
            for (j = 1; j < n; ++j) 
                if (!used[j]) {
                    if (g[queue[i]][j] < g[id][j])
                    g[id][j] = g[queue[i]][j];
                }
        }
    }
for (i = 1; i <= n; ++i) 
    if (!used[i] && i !=id) {
            for (j = from; j < tot; ++j) {
                k =queue[j];
                if (g[i][id] > g[i][k] - g[eg[k]][k])
                    g[i][id] = g[i][k] - g[eg[k]][k];
            }
        }
}

int mdst(int root) {
    int i, j, k;
    int sum = 0;
    memset(used, 0, sizeof(used));
    for (more = 1; more; ) {
        more = 0;
        memset(eg, 0, sizeof(eg));
    for (i = 1; i <= n; ++i) 
        if (!used[i] && i != root) {
                for (j = 1, k = 0; j <= n; ++j) 
                    if (!used[j] && i != j) {
                        if (k == 0 || g[j][i] < g[k][i]) 
                            k = j;
                    }
                eg[i] = k;
            }
        memset(pass, 0, sizeof(pass));
    for (int i = 1; i <= n; ++i) 
        if (!used[i] && !pass[i] && i !=root)
                combine(i, sum);
        if (sum == -1) return -1;
    }
for (i = 1; i <= n; ++i) 
    if (!used[i] && i != root) {
            sum += g[eg[i]][i];
            if (sum > 1000000000) sum = -1;
            if (sum == -1) return sum;
        }
    return sum;
}
