#include <iostream>
#include <cstdio>
#include <cstring>
#include <vector>
#include <queue>
#include <algorithm>
using namespace std;

typedef long long LL;
int Limit;

int check(LL x) {
    if (x <= 0 || x > Limit) return 0;
    return 1;
}

class AfraidOfEven {
public:
    vector <int> restoreProgression(vector <int> seq) {
        int n = seq.size();
        Limit = (1LL << 31) - 1;
        for (int i = 0; i < 32; ++i)
            for (int j = 0; j < 32; ++j) {
                vector<int> ver;
                LL x = (1LL << i) * seq[0];
                LL y = (1LL << j) * seq[1];
                if (!check(x) || !check(y)) continue;
                ver.push_back(x);
                ver.push_back(y);
                for (int k = 2; k < n; ++k) {
                    LL z = ver.back() + y - x;
                    if (!check(z)) break;
                    LL q = seq[k];
                    while (q < z)
                        q *= 2;
                    if (q != z) break;
                    ver.push_back(z);
                }
                if (ver.size() == seq.size()) return ver; 
            }
    }
};
