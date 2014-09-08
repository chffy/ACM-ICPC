namespace ISAP {
    
    queue <int> que;
    int d[N], gap[N];
    const int INF = 1e9;

    void bfs(int t, int num) {
        for (int i = 1; i <= num; ++i)
            d[i] = num + 1;
        memset(gap, 0, sizeof(gap));
        d[t] = 0;
        que.push(t);
        while (!que.empty()) {
            int x = que.front(); que.pop();
            for (int k = first[x]; ~k; k = next[k]) 
            if ((k & 1) && d[end[k]] == num + 1) {
                d[end[k]] = d[x] + 1;
                que.push(end[k]);
                ++gap[d[end[k]]];
            }
        }
    }

    int backup[N], p[N], neck[N], cur[N];

    int sap(int s, int t, int num) {
        bfs(t, num);
        int ans = 0, flow = INF, x = s;
        neck[s] = s;
        memcpy(cur, first, sizeof(cur));
        while (d[s] < num) {
            backup[x] = flow;
            int k;
            for (k = cur[x]; ~k; k = next[k])
            if (d[x] == d[end[k]] + 1 && wi[k]) break;
            if (~k) {
                cur[x] = k;
                int y = end[k];
                p[y] = k;
                if (flow > wi[k])
                    flow = wi[k], neck[y] = x;
                else neck[y] = neck[x];
                x = y;
                if (x == t) {
                    ans += flow;
                    for (int i = t; i != s; i = end[p[i] ^ 1]) {
                        wi[p[i]] -= flow;
                        wi[p[i] ^ 1] += flow;
                        backup[i] -= flow;
                    } 
                    x = neck[x]; flow = backup[x];
                } 
            }    
            else {
                int i = -1;
                for (int k = first[x]; ~k ; k = next[k]) 
                    if (wi[k] && (!~i || d[end[i]] > d[end[k]]))
                        i = k;
                if (!~i || --gap[d[x]] == 0) break;
                cur[x] = i;
                d[x] = d[end[i]] + 1;
                ++gap[d[x]];
                if (x != s) x = end[p[x] ^ 1], flow = backup[x];
            }
        }
        return ans;
    }
};
