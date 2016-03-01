#include <iostream>
#include <cstdio>
#include <cstring>
#include <vector>
#include <queue>
#include <algorithm>
using namespace std;

string getString(int A, int B) {
    string res = "0.";
    A *= 10;
    for (int i = 1; i <= 6; ++i) {
        res = res +(char)('0' + A / B);
        A %= B;
        A *= 10;
    }
    return res;
}

int lcp(string A, string B) {
    for (int i = 0; i < 8; ++i)
        if (A[i] != B[i]) return i;
    return 8;
}



class BestApproximationDiv1 {
public:
    string findFraction(int maxDen, string number) {
        string ans = "";
        int res = -1;
        for (int B = 1; B <= maxDen; ++B)
            for (int A = 0; A < B; ++A) {
                string tmp = getString(A, B);
                string ans0 = "";
                char T[10];
                sprintf(T, "%d/%d", A, B);
                ans0 = T;
                int res0 = lcp(number, tmp);
                if (res0 > res) {
                    res = res0;
                    ans = ans0;
                }
            }
        return ans + " has " + (char)(res + '0' - 1) + " exact digits"; 
    }
};
