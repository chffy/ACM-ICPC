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

map<vector<int>, double> f;
int limit[11];

double dp(vector<int> &ver) {
    if (f.count(ver)) return f[ver];
    int res = 0, cnt = 0;
    for (int i = 0; i < 11; ++i) {
        res += ver[i] * (i + 1);
        cnt += limit[i] - ver[i];
    }
    if (res >= 21) return f[ver] = 0.0;
    double tmp = 0;
    vector<int> ver1 = ver;
    for (int i = 0; i < 11; ++i)
        if (ver[i] != limit[i]) {
            ver1[i] ++;
            tmp += dp(ver1) * (limit[i] - ver[i]);
            ver1[i] --;
        }
    f[ver] = tmp / cnt + 1;
    return f[ver];
}

class TheBlackJackDivOne {
public:
    double expected(vector <string> cards) {
        vector<int> ver;
        for (int i = 0; i < 11; ++i)
            ver.push_back(0);
        for (auto str : cards) {
            if (isdigit(str[0])) ver[str[0] - '0' - 1] ++;
            else if (str[0] == 'A') ver[10] ++;
            else ver[9] ++;
        }
        for (int i = 1; i <= 13; ++i)
            if (i == 1) limit[10] += 4;
            else if (i >= 10) limit[9] += 4;
            else limit[i - 1] += 4;
        return dp(ver);
    }
};
