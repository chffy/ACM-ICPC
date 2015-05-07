#include <iostream>
#include <cstdio>
#include <cstring>
#include <algorithm>
#include <vector>
using namespace std;

int mark[55];

class OddEvenTree {
public:
    vector <int> getTree(vector <string> x) {
        int n = x.size();
        vector<int> ans;
        int flag = 0;
        for (int i = 0; i < n; ++i) {
            if (x[0][i] == 'E') {
                mark[i] = 0;
                flag |= 1;
            }
            else {
                flag |= 2;
                mark[i] = 1;
            }
        }
        if (flag != 3) {
            ans.push_back(-1);
            return ans;
        }
        for (int i = 0; i < n; ++i)
            for (int j = 0; j < n; ++j) {
                if (x[i][j] == 'E') {
                    if (mark[i] != mark[j]) {
                        ans.push_back(-1);
                        return ans;
                    }
                }
                else {
                    if (mark[i] == mark[j]) {
                        ans.push_back(-1);
                        return ans;
                    }
                }
            }
        for (int i = 1; i < n; ++i)
            if (mark[i] != mark[0]) {
                ans.push_back(0);
                ans.push_back(i);
            }
        for (int i = 1; i < n; ++i)
            if (mark[i] != mark[0]) {
                for (int j = 1; j < n; ++j)
                    if (mark[j] != mark[i]) {
                        ans.push_back(i);
                        ans.push_back(j);
                    }
                return ans;
            }
        return ans;
    }
};
