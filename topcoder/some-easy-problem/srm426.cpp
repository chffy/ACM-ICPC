#include <iostream>
#include <cstdio>
#include <cstring>
#include <vector>
#include <algorithm>
#include <set>
#include <cmath>
using namespace std;

int bo[100];

class ShufflingMachine {
public:
    double stackDeck(vector <int> p, int mx, vector <int> card, int K) {
        int n = p.size();
        vector<double> res;
        for (auto x : card)
            bo[x] = 1;
        for (int i = 0; i < n; ++i) {
            double tmp = 0;
            for (int j = 1, x = i; j <= mx; ++j) {
                x = p[x];
                if (bo[x]) tmp ++; 
            }
            tmp /= mx;
            res.push_back(tmp);
        }
        sort(res.begin(), res.end());
        reverse(res.begin(), res.end());
        double ans = 0;
        for (int i = 0; i < K; ++i)
            ans += res[i];
        return ans;
    }
};
