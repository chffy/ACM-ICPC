#include <iostream>
#include <cstdio>
#include <cstring>
#include <vector>
#include <queue>
#include <algorithm>
using namespace std;

class ColoredStrokes {
public:
    int getLeast(vector <string> pic) {
        int n = pic.size();
        int m = pic[0].size();
        int ans = 0;
        for (int i = 0; i < n; ++i)
            for (int j = 0; j < m; ++j)
                if (pic[i][j] == 'B' || pic[i][j] == 'G') {
                    if (i == 0 || (pic[i - 1][j] != 'B' && pic[i - 1][j] != 'G'))
                        ++ans;
                }
        for (int i = 0; i < n; ++i)
            for (int j = 0; j < m; ++j)
                if (pic[i][j] == 'R' || pic[i][j] == 'G') {
                    if (j == 0 || (pic[i][j - 1] != 'R' && pic[i][j - 1] != 'G'))
                        ++ans;
                }
        return ans;
    }
};
