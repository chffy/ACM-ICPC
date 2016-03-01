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

int check(string a, char b[]) {
    for (int i = 0; i < a.size(); ++i)
        if (a[i] != '?' && a[i] != b[i]) return 0;
    return 1;
}

class TheTriangleBothDivs {
public:
    string fix(string time) {
        string ans = "hhhhhhhhhhh";
        for (int h = 0; h < 24; ++h)
            for (int m = 0; m < 60; ++m) 
                for (int k = -9; k <= +9; ++k) {
                    char str[20];
                    sprintf(str, "%02d:%02d GMT%c%d", h, m, "+-"[k < 0], abs(k));
                    if (check(time, str)) {
                        sprintf(str, "%02d:%02d", (h - k + 24) % 24, m);
                        string tmp = str;
                        if (tmp < ans) ans = tmp;
                    }
                }
        return ans;
    }
};
