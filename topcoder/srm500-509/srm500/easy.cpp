#include <iostream>
#include <cstdio>
#include <cstring>
#include <algorithm>
#include <vector>
#include <set>
using namespace std;

int sum[505];

class MafiaGame {
public:
    double probabilityToLose(int n, vector <int> decisions) {
        int m = decisions.size();
        sort(decisions.begin(), decisions.end());
        int flag = 0;
        for (int i = 1; i < m; ++i)
            if (decisions[i] == decisions[i - 1]) {
                flag = 1;
            }
        if (flag == 0) {
            return 0;
        }
        else {
            for (int i = 0; i < m; ++i)
                sum[decisions[i]]++;
            int mx = 0;
            for (int i = 0; i < n; ++i)
                mx = max(mx, sum[i]);
            int tot = 0;
            for (int i = 0; i < n; ++i)
                if (mx == sum[i]) ++tot;
            int cur = tot;
            while (n % cur != 0) {
                cur = n % cur;
            }
       
            if (cur == 1) 
                return 1.0 / tot;
            else return 0;
        }
    }
};
