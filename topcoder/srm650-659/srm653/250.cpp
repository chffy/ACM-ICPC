#include <iostream>
#include <cstdio>
#include <cstring>
#include <algorithm>
#include <vector>
#include <cassert>
using namespace std;
 
int f[105];
 
class CountryGroupHard {
public:
    string solve(vector <int> a) {
        int n = a.size(), j = 0;
        f[0] = 1;
        for (int j = 0; j <= n; ++j) {
            for (int k = j + 1, L = 0; k <= n; ++k) {
                if (a[k - 1] != 0 ) {
                    if (L == 0) L = a[k - 1];
                    else if (L != a[k - 1]) L = -1;
                }
                if (L == -1) break;
                if (k - j == L || L == 0 ) {
                    f[k] += f[j];
                    if (f[k] > 1) f[k] = 2;
                }
            }
        }
        if (f[n] != 1) return "Insufficient";
        else return "Sufficient";
    }
};
