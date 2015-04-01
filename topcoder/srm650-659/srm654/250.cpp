#include <iostream>
#include <cstdio>
#include <cstring>
#include <vector>
#include <algorithm>
using namespace std;

class SquareScores {
public:
    double calcexpectation(vector <int> p, string s) {
        p.resize(26);
        int n = s.size();
        double ans = 0;
        for (int k = 0; k < 26; ++k)
            for (int i = 0; i < n; ++i) {
                double pi = 1;
                for (int j = i; j < n; ++j) {
                    if (s[j] == '?') pi = pi * p[k] / 100;
                    else if (s[j] != k + 'a') break;
                    ans += pi;
                }
            }
        return ans;
    }
};
