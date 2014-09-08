struct SAM {
    int f[N * 2][26], parent[N * 2], rmax[N * 2];
    int tot, len, last, root;
    
    void clear() {
        memset(f, -1, sizeof(f));
        tot = len = last = root = 1;
        rmax[root] = 0;
        parent[root] = -1;
    }
    
    void insert(int ch) {
        int np = ++tot, vp = last;
        last = np;
        rmax[np] = ++len;
        while (~vp && f[vp][ch] == -1)
            f[vp][ch] = np, vp = parent[vp];
        if (vp == -1) {
            parent[np] = root;
            return ;
        }
        int p = f[vp][ch];
        if (rmax[vp] + 1 == rmax[p]) {
            parent[np] = p;
            return ;
        }
        int nq = ++tot; rmax[nq] = rmax[vp] + 1;
        memcpy(f[nq], f[p], sizeof(f[p]));
        parent[nq] = parent[p];
        parent[np] = parent[p] = nq;
        while (~vp && f[vp][ch] == p)
            f[vp][ch] = nq, vp = parent[vp];
    }
};
