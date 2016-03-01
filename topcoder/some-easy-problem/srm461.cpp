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

int calc(int w, int h, vector<int> red, vector<int> blue) {
    int num = 0;
    double ans = w;
    while (ans > 1e-8) {
        if (red.empty()) return 1 << 30; 
        double len = (double)red.back() / 2;
        len = sqrt(sqr(len) - sqr(h / 2.0)) * 2;
        ans -= len;
        red.pop_back();
        swap(red, blue);
        ++num;
    }
    return num;
}

class ColoringRectangle {
public:
    int chooseDisks(int w, int h, vector <int> red, vector <int> blue) {
        sort(red.begin(), red.end());
        sort(blue.begin(), blue.end());
        reverse(red.begin(), red.end());
        reverse(blue.begin(), blue.end());
        while (!red.empty() && red.back() < h) red.pop_back();
        while (!blue.empty() && blue.back() < h) blue.pop_back();
        reverse(red.begin(), red.end());
        reverse(blue.begin(), blue.end());
        int ans = calc(w, h, red, blue);
        swap(red, blue);
        ans = min(ans, calc(w, h, red, blue));
        if (ans > 10000) ans = -1;
        return ans;
    }
};
