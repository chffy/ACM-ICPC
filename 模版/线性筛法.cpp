int prime[N], mu[N], m, bo[N];

void mobius() {
    mu[1] = 1;
    memset(bo, 0, sizeof(bo));
    for (int i = 2; i < N; ++i) {
        if (!bo[i]) {
            mu[i] = -1;
            prime[m++] = i;
        }
        for (int j = 0; j < m && prime[j] * i < N; ++j) {
            bo[i * prime[j]] = 1;
            if (i % prime[j]) mu[i * prime[j]] = -mu[i];
            else {
                mu[i * prime[j]] = 0;
                break;
            }
        }
    }
}
