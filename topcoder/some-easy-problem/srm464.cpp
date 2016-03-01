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

string ans;
char str[15];
int bo[10];

int check() {
    int n = strlen(str);
    set<int> ext;
    for (int i = 0; i < n; ++i) {
        int proc = 1;
        for (int j = i; j < n; ++j) {
            proc *= str[j] - '0';
            if (ext.count(proc)) return 0;
            ext.insert(proc);
        }
    }
    return 1;
}

void dfs(int n, int &m) {
    if (n == 0) {
        if (check()) {
            if (--m == 0) ans = str;
        }
        return ;
    }
    for (int i = 2; i < 10; ++i)
        if (!bo[i]) {
            str[n - 1] = i + '0';
            bo[i] = 1;
            dfs(n - 1, m);
            bo[i] = 0;
        }
}

class ColorfulStrings {
public:
    string getKth(int n, int k) {
        if (n == 1) {
            if (k <= 10) 
                ans = ans + (char)(k - 1 + '0');
        }
        else if (n <= 8) {
            dfs(n, k);
        }
        reverse(ans.begin(), ans.end());
        return ans;
    }
};
