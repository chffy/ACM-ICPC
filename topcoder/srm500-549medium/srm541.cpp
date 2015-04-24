#include <iostream>
#include <cstdio>
#include <cstring>
#include <vector>
#include <algorithm>
using namespace std;

typedef long long LL;
string suf, pre;
const int P = 1e9 + 7;

int calc(string T, string F, int mark) {
    int n = T.size(), m = F.size();
    int ans = 0;
    for (int i = 0; i + m <= n; ++i) {
        int flag = 1;
        for (int j = 0; j < m; ++j)
            if (T[i + j] != F[j]) flag = 0;
        ans += flag;
    }
    if (mark || n < m) return ans;
    suf = pre = "";
    for (int i = 0; i < m; ++i) {
        pre += T[i];
        suf += T[n - m + i];
    }
    return ans;
}

int solve(string W, string A, string D, string F) {
    int p0 = calc(pre, F, 1), p1 = calc(suf, F, 1);
    int ans = (calc(W + pre, F, 1) - p0);
    ans += calc(suf + A + pre, F, 1) - p0 - p1;
    ans += calc(suf + D, F, 1) - p1;
    return ans;
}

class AkariDaisukiDiv1 {
public:
    int countF(string W, string A, string D, string S, string F, int m) {
        int K = 0;
        string T = S;
        while (K < m && T.size() < F.size()) {
            T = W + T + A + T + D;
            ++K;
        }
        int ans = calc(T, F, 0);
        if (K == m) return ans;
        while (K < F.size() && K < m) {
            calc(T, F, 0);
            T = pre + suf;
            ans = ((LL)ans * 2 + solve(W, A, D, F)) % P;
            T = W + pre + suf + D;
            ++K;
        }
        calc(T, F, 0);
        T = pre + suf;
        int b = solve(W, A, D, F);
        while (K < m) {
            ans = ((LL)ans * 2 + b) % P;
            ++K;
        }
        return ans;
    }
};
