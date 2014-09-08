bool find(int x, int m) {
    visx[x] = 1;
    for (int i = 0; i < m; ++i) 
        if (lx[x] + ly[i] == w[x][i]) {
            if (visy[i]) continue;
            visy[i] = 1;
            if ( my[i] == -1 || find(my[i], m)) {
                my[i] = x;
                return 1;
            }
        } else slack[i] = min(slack[i], lx[x] + ly[i] - w[x][i]);
    return 0;
}

int minvalue(int n, int m) {
    memset(lx, 130, sizeof(int) * n);
    memset(ly, 0, sizeof(int) * m);
    memset(my, -1, sizeof(int) * n);
    for (int i = 0; i < n; ++i)
        for (int j = 0; j < m; ++j) {
            lx[i] = max(lx[i], w[i][j] = -w[i][j]);
        }
    for (int i = 0; i < n; ++i)
        for (memset(slack, 63, sizeof(int) * m);;) {
            memset(visx, 0, sizeof(bool) * n);
            memset(visy, 0, sizeof(bool) * m);
            if (find(i, m)) break;
            int d = 1 << 30;
            for (int j = 0; j < m; ++j)
                if (!visy[j]) d = min(d, slack[j]);
            for (int j = 0; j < n; ++j)
                if (visx[j]) lx[j] -= d;
            for (int j = 0; j < m; ++j)
                if (visy[j]) ly[j] += d;
                else slack[j] -= d;
        }
    int ans = 0;
    for (int i = 0; i < m; ++i)
        if (~my[i]) ans += w[my[i]][i];
    return -ans;
}
