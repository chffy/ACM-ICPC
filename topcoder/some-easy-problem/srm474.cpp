#include <iostream>
#include <cstdio>
#include <cstring>
#include <vector>
#include <queue>
#include <map>
#include <algorithm>
using namespace std;

int b[10000];

class RouteIntersection {
public:
    string isValid(int n, vector <int> coords, string moves) {
        int m = 0;
        for (int i = 0; i < coords.size(); ++i)
            b[m++] = coords[i];
        sort(b, b + m);
        m = unique(b, b + m) - b;
        for (int i = 0; i < coords.size(); ++i)
            coords[i] = lower_bound(b, b + m, coords[i]) - b;
        vector<int> fr;
        for (int i = 0; i < m; ++i)
            fr.push_back(0);
        map<vector<int>, int> ext;
        ext[fr] = 1;
        for (int i = 0; i < coords.size(); ++i) {
            int s = 1;
            if (moves[i] == '-') s = -1;
            fr[coords[i]] += s;
            if (ext.count(fr)) return "NOT VALID";
            ext[fr] = 1;
        }
        return "VALID";
    }
};
