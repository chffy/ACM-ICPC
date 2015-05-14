#include <iostream>
#include <cstdio>
#include <cstring>
#include <algorithm>
#include <vector>
#include <cmath>
#include <queue>
using namespace std;

const int N = 1e6 + 5;
int dis[N];

class LongestSequence {
public:
    int maxLength(vector <int> C) {
        sort(C.begin(), C.end());
        if (C[0] > 0 || C.back() < 0) return -1;
        dis[0] = 1;
        for (int i = 1; ; ++i) {
            int flag = 0;
            for (int j = 0; j < C.size(); ++j) {
                int x = i - C[j];
                if (x < 0 || x > i) continue;
                if (dis[x]) {
                    flag = 1;
                    break;
                }
            }
            if (flag) {
                dis[i] = 1; 
                queue<int> que;
                que.push(i);
                while (!que.empty()) {
                    int x = que.front(); que.pop();
                    for (int j = 0; j < C.size(); ++j) {
                        int y = x + C[j];
                        if (y == 0) return i - 1;
                        if (y < 0 || y > i || dis[y])
                            continue;
                        dis[y] = 1;
                        que.push(y);
                    }
                }
            }
        }
    }
};
