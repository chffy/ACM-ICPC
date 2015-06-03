#include <iostream>
#include <cstdio>
#include <cstring>
#include <vector>
using namespace std;

const double esp = 1e-9;

class NewItemShop {
public:
    
    int mark[30], mul[30], m, cost[30];
    double pp[30];
    double f[25][5000][25];

    int nextInt(string S, int &p) {
        int x;
        while (!isdigit(S[p])) ++p;
        x = S[p] - '0';
        ++p;
        while (isdigit(S[p])) {
            x = x * 10 + S[p] - '0';
            ++p;
        }
        return x;
    }
    
    double dp(int t, int mask, int num) {
        if (f[t][mask][num] > -esp) return f[t][mask][num];
        if (t == 24 || num == 0) return f[t][mask][num] = 0;
        if (mark[t] == -1)
            return f[t][mask][num] = dp(t + 1, mask, num);
        double &tmp = f[t][mask][num];
        tmp = dp(t + 1, mask, num);
        if (mul[mark[t]] == -1 || (mask >> mul[mark[t]] & 1) == 0) {
            int opt = 0;
            if (mul[mark[t]] != -1) opt = 1 << mul[mark[t]];
            tmp = dp(t + 1, mask | opt, num) * pp[t] + dp(t + 1, mask, num) * (1 - pp[t]);
            tmp = max(tmp, (dp(t + 1, mask | opt, num - 1) + cost[t]) * pp[t] +
                      dp(t + 1, mask, num) * (1 - pp[t]));
        }
        else tmp = dp(t + 1, mask, num);
       // printf("%d %.10f\n", t, tmp);
        return tmp;
    }
    
    double getMaximum(int swords, vector <string> customers) {
        int n = customers.size();
        memset(mark, -1, sizeof(mark));
        m = 0;
        for (int i = 0; i < n; ++i) {
            int p = 0;
            string S = customers[i];
            int sum = 0;
            int pro = 0;
            while (p < S.size()) {
                int ti, ci, pi;
                ti = nextInt(S, p);
                ci = nextInt(S, p);
                pi = nextInt(S, p);
                mark[ti] = i;
                cost[ti] = ci;
                pp[ti] = (double)pi / (100 - pro);
                pro += pi;
                ++sum;
            }
            if (sum > 1) mul[i] = m++;
            else mul[i] = -1;
        }
        for (int i = 0; i < 25; ++i)
            for (int j = 0; j < 1 << m; ++j)
                for (int k = 0; k <= swords; ++k)
                    f[i][j][k] = -1;
        return dp(0, 0, swords);
    }
};
