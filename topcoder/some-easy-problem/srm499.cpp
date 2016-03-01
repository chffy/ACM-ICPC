#include <iostream>
#include <cstdio>
#include <cstring>
#include <vector>
#include <queue>
#include <algorithm>
using namespace std;

class ColorfulRabbits {
public:
    int getMinimum(vector <int> rep) {
        sort(rep.begin(), rep.end());
        int n = rep.size();
        int ans = 0;
        for (int i = 0; i < n; ++i) {
            int j = i;
            while (j + 1 < n && rep[i] == rep[j + 1]) {
                ++j;
            }
            int num = (j - i + 1 + rep[i]) / (rep[i] + 1);
            ans += num * (rep[i] + 1);
            i = j;
        }
        return ans;
    }  
};
