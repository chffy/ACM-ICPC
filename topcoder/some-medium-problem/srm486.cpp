#include <iostream>
#include <cstdio>
#include <cstring>
#include <vector>
#include <algorithm>
#include <set>
#include <cmath>
#include <stack>
#include <deque>
using namespace std;

int a[55], n;
int bo[55][55];
double f[55][55];

double solve(int l, int r) {
    if (bo[l][r]) return f[l][r];
    bo[l][r] = 1;
    vector<int> ver;
    for (int i = 0; i < n; ++i)
        if (a[i] >= l && a[i] <= r) ver.push_back(a[i]);
    if (ver.size() < 2) return f[l][r] = 0;
    for (int i = 0; i < ver.size(); ++i) {
        double res = 0;
        for (int j = 0; j < ver.size(); ++j) {
            if (ver[j] > ver[i] && j < i) ++res;
            if (ver[j] < ver[i] && j > i) ++res;
        }
        res += solve(l, ver[i] - 1) + solve(ver[i] + 1, r);
        f[l][r] += res;
    }
    return f[l][r] /=  ver.size();
}

class QuickSort {
public:
    double getEval(vector <int> L) {
        n = L.size();
        for (int i = 0; i < n; ++i) a[i] = L[i];
        return solve(1, 50);
    }
};
