#include <iostream>
#include <cstdio>
#include <cstring>
#include <vector>
#include <algorithm>
#include <set>
#include <cmath>
using namespace std;

int d[100];
int bo[100];
int floyed[55][55];
int f[55];

int find(int x) {
    if (f[x] != x) f[x] = find(f[x]);
    return f[x];
}

double check(vector<string> &infor) {
    memset(d, 0, sizeof(d));
    memset(floyed, 0, sizeof(floyed));
    int n = infor.size();
    for (int i = 0; i < n; ++i)
        for (int j = 0; j < n; ++j)
            if (bo[i] == 0 && bo[j] == 0 && infor[i][j] == 'Y') { 
                floyed[i][j] = 1;
            }
    for (int k = 0; k < n; ++k)
    	for (int i = 0; i < n; ++i)
    		for (int j = 0; j < n; ++j)
    			floyed[i][j] |= floyed[i][k] & floyed[k][j];
    for (int i = 0; i < n; ++i) f[i] = i;
    for (int i = 0; i < n; ++i)
        for (int j = i + 1; j < n; ++j)
            if (floyed[i][j] && floyed[j][i])
                f[find(i)] = find(j);
    for (int i = 0; i < n; ++i)
        for (int j = 0; j < n; ++j)
            if (bo[i] == 0 && bo[j] == 0 && infor[i][j] == 'Y') { 
                if (find(i) == find(j)) continue;
                ++d[find(j)];
            }
    int k = 0;
    for (int i = 0; i < n; ++i)
        if (!bo[i] && find(i) == i && d[i] == 0) ++k; 
    if (k == 0) return 1;
    return (double) (n - k) / n;
}

class CarrotBoxes {
public:
    double theProbability(vector <string> infor) {
        memset(bo, 0, sizeof(bo));
        double ans = check(infor);
        for (int i = 0; i < infor.size(); ++i) {
            bo[i] = 1;
            ans = max(ans, check(infor));
            bo[i] = 0;
        }
        return ans;
    }
};
