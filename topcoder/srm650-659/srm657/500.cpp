#include <iostream>
#include <cstdio>
#include <cstring>
#include <vector>
#include <algorithm>
using namespace std;

typedef long long LL;

const int P = 1e9 + 7;
const int N = 1e5 + 5;

int bo[N];

int power(int a, int n) {
    int ans = 1, z = a;
    while (n) {
        if (n & 1) ans = (LL)ans * z % P;
        n >>= 1, z = (LL)z * z % P;
    }
    return ans;
}

int dfs(const string &s, int n, int x) {
    if (s.size() < x) return 0;
    int ans = 1 << 30;
    for (int i = 1; i <= min(x, n); ++i) {
        string b = "";
        int tmp = 0;
        for (int j = i; j <= n; j += x) {
            tmp += s[j - 1] - '0';
            b += s[j - 1];
        }
        tmp += dfs(b, (int)b.size(), x);
        ans = min(tmp, ans);
    }
    return ans;
}

class PolynomialGCD {
public:
    int gcd(string s) {
        int n = s.size();
        reverse(s.begin(), s.end());
        LL ans = 1;
        for (int x = 2; x <= n; ++x)
            if (!bo[x]) {
                for (int j = x * 2; j <= n; j += x)
                    bo[j] = 1;
                int res = dfs(s, n, x);
                ans = (LL)ans * power(x, res) % P;
            }
        return ans;
    }
};
