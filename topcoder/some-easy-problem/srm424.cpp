#include <iostream>
#include <cstdio>
#include <cstring>
#include <vector>
#include <algorithm>
#include <set>
#include <cmath>
using namespace std;

class ProductOfDigits {
public:
    int smallestNumber(int N) {
        int num = 0;
        for (int i = 9; i > 1; --i)
            while (N % i == 0) {
                ++num;
                N /= i;
            }
        if (N != 1) num = -1;
        if (num == 0) num = 1;
        return num;
    }
};
