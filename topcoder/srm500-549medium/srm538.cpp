#include <cstdio>
#include <cstring>
#include <iostream>
#include <vector>
#include <algorithm>
#include <cmath>
using namespace std;

int a[100];
int f[100][400];
const double pi = acos(-1.0);

double dis(double x, double y) {
    return sqrt(x * x + y * y);
}

double solve(int len1, int len2, int angle) {
    if (angle > 180) angle = 360 - angle;
    double aa = (double)angle / 180 * pi;
    double ans0 = dis(len1 + cos(pi - aa) * len2, sin(pi - aa) * len2);
    double ans1 = dis(-len2 + cos(aa) * len1, sin(aa) * len1);
    return max(ans0, ans1);
}

class TurtleSpy {
public:
    
    double maxDistance(vector <string> commands) {
        int n = 0, lena = 0, lenb = 0;
        for (int i = 0; i < commands.size(); ++i) {
            int x = 0;
            int j = 0;
            while (!isdigit(commands[i][j])) ++j;
            while (j < commands[i].size() && isdigit(commands[i][j]))
                x = x * 10 + commands[i][j++] - '0';
            int ch = commands[i][0];
            if (ch == 'f') lena += x;
            if (ch == 'b') lenb += x;
            if (ch == 'l') a[n++] = x;
            if (ch == 'r') a[n++] = (360 - x) % 360;
        }
        f[0][0] = 1;
        for (int i = 0; i < n; ++i)
            for (int j = 0; j < 360; ++j) {
                f[i + 1][j] |= f[i][j];
                f[i + 1][(j + a[i]) % 360] |= f[i][j];
            }
        double ans = 0;
        for (int i = 0; i < 360; ++i)
        	if (f[n][i])
            ans = max(ans, solve(lena, lenb, i));
       	return ans;
    }
};
