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

const int P = 1e9 + 7;

class RabbitNumbering {
public:
    int theCount(vector <int> mx) {
        int n = mx.size();
        int ans = 1;
        sort(mx.begin(), mx.end());
        for (int i = 0; i < n; ++i)
            ans = (long long)ans * (mx[i] - i) % P;
        return ans;
    }
};
