#include <iostream>
#include <cstdio>
#include <cstring>
#include <algorithm>
#include <vector>
using namespace std;

const int N = 1e5 + 5;
typedef long long LL;

int I[N], inv[N];
int a[N], p[N];

void init(int P) {
    I[0] = I[1] = inv[0] = inv[1] = 1;
    for (int i = 2; i < P; ++i) {
        I[i] = i;
        inv[i] = ((LL)P - P / i) * inv[P % i] % P; 
    }
    for (int i = 2; i < P; ++i) {
        inv[i] = (LL)inv[i - 1] * inv[i] % P;
        I[i] = (LL)I[i] * I[i - 1] % P;
    }
}

int C(int n, int m, int P) {
    if (n < m) return 0;
    return (LL)I[n] * inv[m] % P * inv[n - m] % P;
}

int calc(LL n, LL m, int P) {
    //if (n < P && m < P) return C(n, m, )
    if (m == 0) return 1;
    return (LL)calc(n / P, m / P, P) * C(n % P, m % P, P) % P;
}

LL M;

LL mu(LL a, LL b, LL M) {
    LL ans = 0;
    while (b > 0) {
        if (b & 1) ans = (ans + a) % M;
        a = (a + a) % M;
        b >>= 1;
    }
    return ans;
}

void exgcd(LL a, LL b, LL &x, LL &y) {
    if (b == 0) {
        x = 1, y = 0;
        return ;
    }
    exgcd(b, a % b, x, y);
    LL tmp = x;
    x = y;
    y = tmp - a / b * y;
}


LL power(LL a, LL n, LL P) {
    LL ans = 1, z = a;
    while (n > 0) {
        if (n & 1) ans = mu(ans, z, P);
        n >>= 1, z = mu(z, z, P);
    }
    return ans;
}

LL inverse(LL x, LL y) {
    return power(x % y, y - 2, y);
}

int main() {
    int T;
    scanf("%d", &T);
    while (T--) {
        LL n, m;
        int K;
        scanf("%lld%lld%d", &n, &m, &K);
        for (int i = 1; i <= K; ++i) {
            scanf("%d", &p[i]);
            init(p[i]);
            a[i] = calc(n, m, p[i]);
            //printf("%d\n", a[i]);
        }
        //cout << 1 << endl;
        M = 1;
        for (int i = 1; i <= K; ++i)
            M = M * p[i];
        LL ans = 0;
        for (int i = 1; i <= K; ++i) {
            LL tmp = a[i];
            LL ti = inverse(M / p[i], p[i]);
            LL Mi = M / p[i];
            tmp = mu(mu(tmp, Mi, M), ti, M);
            ans = (ans + tmp) % M;
        }
        printf("%lld\n", ans);
    }
    return 0;
}
       
