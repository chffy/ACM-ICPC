#include <iostream>
#include <cstdio>
#include <cstring>
#include <vector>
#include <queue>
#include <map>
#include <algorithm>
#include <set>
#include <cmath>
using namespace std;

double sqr(double x) {
    return x * x;
}

class IncredibleMachine {
public:
    double gravitationalAcceleration(vector <int> x, vector <int> y, int T) {
        int n = x.size();
        double head = 0, tail = 1e9;
        for (int t = 1; t <= 100; ++t) {
            double mid = (head + tail) / 2;
            double ti = 0, v0 = 0;
            for (int i = 0; i + 1 < n; ++i) {
                double angle = atan2(abs(y[i] - y[i + 1]), abs(x[i + 1] - x[i]));
                double a = sin(angle) * mid;
                double S = sqrt(sqr(y[i] - y[i + 1]) + sqr(x[i] - x[i + 1]));
                double A = a / 2, B = v0, C = -S;
                //cout << A << " " << B << " " << C << endl;
                double tmp = (-B + sqrt(B * B - 4 * A * C)) / (2 * A);
                ti += tmp;
                v0 += tmp * a;
                if (ti > T) break;
            }
            if (ti > T) head = mid;
            else tail = mid;
        }
        return head;
    }
};
