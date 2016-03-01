#include <iostream>
#include <cstdio>
#include <cstring>
#include <vector>
#include <queue>
#include <algorithm>
using namespace std;

typedef long long LL;

int S, T;
string ans;

void dfs(int s, string res) {
    if (s == T) {
        if (ans == ":-(" || (ans.size() > res.size()) ||
            (ans.size() == res.size() && ans > res)) {
            ans = res;
        }
        return ;
    }
    if (s + s <= T) dfs(s + s, res + '+');
    if (s != 1 && (LL)s * s <= T)
        dfs(s * s, res + '*');
}

class OneRegister {
public:
    
    string getProgram(int s, int t) {
        S = s, T = t;
        ans = ":-(";
        dfs(s, "");
        dfs(1, "/");
        return ans;
    }
};
