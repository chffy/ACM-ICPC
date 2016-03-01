#include <iostream>
#include <cstdio>
#include <cstring>
#include <vector>
#include <queue>
#include <map>
#include <algorithm>
#include <set>
#include <cmath>
using namespace std;

int check(int x, string s) {
    int p = 0;
    while (s[p] == ' ' || s[p] == 'X') ++p;
    int op = 0;
    if (s[p] == '<') op = 2;
    else if (s[p] == '>') op = 4;
    else op = 1;
    ++p;
    while (s[p] == ' ') ++p;
    if (s[p] == '=') {
        op++;
        while (s[p] == ' ') ++p;
    }
    int y = 0;
    while (p < s.size()) {
        if (isdigit(s[p])) y = y * 10 + s[p] - '0';
        ++p;
    }

    if (op == 1) return x == y * 2;
    if (op == 2) return x < y * 2;
    if (op == 3) return x <= y * 2;
    if (op == 4) return x > y * 2;
    return x >= y * 2;
}

class Inequalities {
public:
    int maximumSubset(vector <string> in) {
        int ans = 0;
        for (int x = -2; x <= 2002; ++x) {
            int res = 0;
            for (int i = 0; i < in.size(); ++i) {
                res += check(x, in[i]);
            }
            ans = max(ans, res);
        }
        return ans;
    }
};
