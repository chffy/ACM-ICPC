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

double check(string str, double x) {
    double ans = 0;
    for (int i = 0; i < str.size(); ++i)
        if (str[i] == '1') {
            ans += pow(x, i);
            if (ans > 200) return ans;
        }
    return ans;
}

class AgeEncoding {
public:
    
    double getRadix(int age, string str) {
        reverse(str.begin(), str.end());
        int flag = 0;
        for (int i = 1; i < str.size(); ++i)
            flag += str[i] - '0';
        if (flag == 0) {
            if (age == (int)str[0] - '0') return -2.0;
            return -1.0;
        }
        double head = 0, tail = 100;
        for (int i = 1; i <= 100; ++i) {
            double mid = (head + tail) / 2;
            if (check(str, mid) > age) tail = mid;
            else head = mid;
        }
       // cout << pow(100, 1) << endl;
       if ((int)str[0] - '0' >= age) head = -1;
        return head;
    }
};
