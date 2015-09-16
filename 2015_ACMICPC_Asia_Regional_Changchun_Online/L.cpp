#include <iostream>
#include <cstdio>
#include <cstring>
#include <vector>
#include <algorithm>
using namespace std;

const int N = 1e5 + 5;
const int P = 1e9 + 7;
typedef long long LL;

int xx[N], yy[N];
int power[N];

void updata(int &x, int y) {
    x += y;
    if (x >= P) x -= P;
}

int main() {
    int T;
    scanf("%d", &T);
    power[0] = 1;
    for (int i = 1; i < N; ++i)
        power[i] = (power[i - 1] + power[i - 1]) % P;
    while (T--) {
        int n;
        scanf("%d", &n);
        for (int i = 0; i < n; ++i) scanf("%d%d", &xx[i], &yy[i]);
        int ans = 0, res = 0;
        for (int i = 0; i < n; ++i)
            updata(res, (LL)yy[i] * power[n - 1 - i] % P);
        for (int i = 0; i < n; ++i) {
            updata(ans, (LL)xx[i] * res % P);
            updata(res, P - (LL)yy[i] * power[n - 1] % P);
            updata(res, res);
            updata(res, yy[i]);
        }
        res = 0;
        for (int i = 0; i < n; ++i) {
            swap(xx[i], yy[i]);
            updata(res, (LL)yy[i] * power[n - 1 - i] % P);
        }
        for (int i = 0; i < n; ++i) {
            updata(ans, P - (LL)xx[i] * res % P);
            updata(res, P - (LL)yy[i] * power[n - 1] % P);
            updata(res, res);
            updata(res, yy[i]);
        }
        printf("%d\n", ans);
    }
    return 0;
}
