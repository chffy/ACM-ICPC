#include <iostream>
#include <cstdio>
#include <cstring>
#include <algorithm>
#include <vector>
using namespace std;

const int N = 105;

int n;
bool graph[N][N], isvalid[N], vis[N];
int my[N];

class DancingForever {
public:

    bool find(int x) {
        for (int i = 0; i < n; ++i)
            if (!vis[i] && graph[x][i]) {
                vis[i] = true;
                if (my[i] == -1 || find(my[i])) {
                    my[i] = x;
                    return true;
                }
            }
        return false;
    }
    
    vector <int> getStablePairs(string x) {
        n = 0;
        while (n * n < x.size()) ++n;
        memset(graph, false, sizeof(graph));
        for (int i = 0; i < n; ++i)
            for (int j = 0; j < n; ++j)
                if (x[i * n + j] == 'Y')
                    graph[i][j] = 1;
        memset(isvalid, true, sizeof(isvalid));
        while (1) {
            bool flag = 0;
            for (int i = 0; i < n; ++i)
                if (isvalid[i]) {
                    flag = 1;
                    break;
                }
            if (!flag) {
                vector<int> ans;
                ans.push_back(-1);
                return ans;
            }
            memset(my, -1, sizeof(my));
            int ret = 0;
            static bool girl[N];
            memset(girl, false, sizeof(girl));
            for (int i = 0; i < n; ++i)
                if (isvalid[i]) {
                    memset(vis, false, sizeof(vis));
                    if (find(i)) {
                        ++ret;
                        for (int j = 0; j < n; ++j)
                            girl[j] |= graph[i][j];
                    }
                }
            int cnt = 0;
            for (int i = 0; i < n; ++i)
                if (girl[i]) ++cnt;
            if (ret == 0) {
                vector<int> ans;
                ans.push_back(-1);
                return ans;
            }
           //printf("%d %d\n", ret, cnt);
            if (cnt == ret) break;
            for (int i = 0; i < n; ++i)
                if (girl[i] && my[i] == -1) {
                    for (int j = 0; j < n; ++j)
                    	if (graph[j][i]) {
                        	isvalid[j] = false;
                        }
                }
        }
        vector<int> ans;
        for (int i = 0; i < n; ++i)
            if (my[i] != -1) {
                ans.push_back(my[i]);
                ans.push_back(i);
            }
        return ans;
    }
};
