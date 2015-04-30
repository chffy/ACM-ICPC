#include <iostream>
#include <cstdio>
#include <cstring>
#include <algorithm>
#include <vector>
using namespace std;

class Rumor {
public:

    int check(int mask, const string &knowledge, vector <string> graph) {
        int n = knowledge.size();
        static int bo[20][2], dis[20][2], p[20][2];
        for (int i = 0; i < n; ++i)
            for (int j = 0; j < 2; ++j) {
                bo[i][j] = 0, dis[i][j] = 1 << 28;
                p[i][0] = p[i][1]  = 0;
            }
        for (int i = 0; i < n; ++i)
            if (knowledge[i] == 'Y') {
                dis[i][0] = dis[i][1] = 0;
            }
        while (1) {
            int k = -1, l = -1;
            for (int i = 0; i < n; ++i)
                for (int j = 0; j < 2; ++j)
                    if (!bo[i][j] && (k == -1 || dis[i][j] + p[i][j] < dis[k][l] + p[k][l])) {
                        k = i, l = j;
                    }
            if (k == -1) break;
            if (dis[k][l] + p[k][l] == dis[k][l ^ 1] + p[k][l ^ 1] && !bo[k][l] && (mask >> k & 1) != l) {
                p[k][l]++;
                l ^= 1;
            }
            bo[k][l] = 1;
            for (int i = 0; i < n; ++i)
                if (graph[k][i] == 'Y')
                    dis[i][l] = min(dis[i][l], dis[k][l] + p[k][l] + 1);
        }
        int ans = 0;
        for (int i = 0; i < n; ++i)
            for (int j = 0; j < 2; ++j)
                ans = max(ans, dis[i][j]);
        return ans;
    }
    
    int getMinimum(string knowledge, vector <string> graph) {
        int n = knowledge.size();
        int ans = 1 << 30;
        for (int mask = 0; mask < 1 << n; ++mask)
            ans = min(ans, check(mask, knowledge, graph));
        if (ans > (1 << 20)) return -1;
        return ans;
    }
};
