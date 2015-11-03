#include <iostream>
#include <cstdio>
#include <cstring>
#include <algorithm>
#include <vector>
#include <set>
using namespace std;

const double eps = 1e-9;
double LEN[505];

class FractalPicture {
public:

    double getLength(double x1, double y1, double x2, double y2, int g, double len) {
        if (g > 500) return 0;
        if (x1 <= -len / 3 && x2 >= len / 3 &&
            y1 <= 0 && y2 >= len) {
            return LEN[g] * len;
        }
        if (x1 > len / 3 || x2 < -len / 3 ||
            y1 > len || y2 < 0) return 0;
        double ans = getLength(x1, y1 - len / 3 * 2, x2, y2 - len / 3 * 2, g + 1, len / 3);
        ans += getLength(len / 3 * 2 - y2, x1, len / 3 * 2 - y1, x2, g + 1, len / 3);
        ans += getLength(y1 - len / 3 * 2, -x2, y2 - len / 3 * 2, -x1, g + 1, len / 3);
        if (x1 <= 0 && x2 >= 0)
            ans += max(0.0, min(y2, len / 3 * 2) - max(y1, 0.0));
        return ans;
    }
    
    double getLength(int x1, int y1, int x2, int y2) {
        LEN[500] = 1;
        for (int i = 499; i >= 1; --i)
            LEN[i] = 2.0 / 3 + LEN[i + 1];
        return getLength(x1, y1, x2, y2, 1, 81);
    }
};
