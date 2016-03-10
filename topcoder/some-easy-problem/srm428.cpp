#include <iostream>
#include <cstdio>
#include <cstring>
#include <vector>
#include <algorithm>
#include <set>
#include <cmath>
using namespace std;

int b[20];
typedef unsigned long long ULL;
const int P = 40007;
ULL a[4000000];

class TheLuckyString {
public:
    int count(string s) {
        int n = s.size();
        for (int i = 0; i < n; ++i)
            b[i] = i;
        int m = 0;
        do {
            string tmp = "";
            ULL hash = 0;
            for (int i = 0; i < n; ++i) {
                tmp += s[b[i]];
                hash = hash * P + tmp[i];
            }
            int flag = 1;
            for (int i = 0; i + 1 < n; ++i)
                if (tmp[i] == tmp[i + 1]) {
                    flag = 0;
                    break;
                }
            if (flag) a[m++] = hash; 
        } while (next_permutation(b, b + n));
        sort(a, a + m);
        m = unique(a, a + m) - a;
        return m;
    }
};
