#include <iostream>
#include <cstdio>
#include <cstring>
#include <string>
#include <vector>
using namespace std;

int f[51][51];

class ColorfulWolves {
public:
    int getmin(vector <string> colormap) {
        int n = colormap.size();
        memset(f, 63, sizeof(f));
        for (int i = 1; i <= n; ++i)
            for (int j = 1, num = 0; j <= n; ++j)
                if (colormap[i - 1][j - 1] == 'Y')
                    f[i][j] = num++;
        for (int k = 1; k <= n; ++k)
            for (int i = 1; i <= n; ++i)
                for (int j = 1; j <= n; ++j)
                    f[i][j] = min(f[i][k] + f[k][j], f[i][j]);
        if (f[1][n] > 10000000) f[1][n] = -1;
        return f[1][n];
    }
};
