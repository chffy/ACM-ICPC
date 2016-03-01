#include <iostream>
#include <cstdio>
#include <cstring>
#include <vector>
#include <queue>
#include <map>
#include <algorithm>
#include <set>
using namespace std;

int gett(int P, int i) {
    if (i % P == 0) return P;
    return i % P;
}

int check(int A, int B, int C, int i) {
    int L = gett(A + B, i), R = gett(A + B, i + C);
   // if (i == 75) printf("%d %d\n", L, R);
    if (L >= A && R >= L) return 1;
    return 0;
}

class LateProfessor {
public:
    double getProbability(int A, int B, int C, int L, int R) {
        int num = 0;
        if (C >= B) return 0.0;
        if (L == R) {
            if (gett(A + B, L) > A && gett(A + B, L + C) > gett(A + B, L)) return 1.0;
            return 0.0;
        }
        for (int i = L; i <= R; ++i) {
            if (!check(A, B, C, i)) continue;
            int j = i;
            while (j + 1 <= R && check(A, B, C, j + 1))
                ++j;
            num += j - i;
           // if (i != j) --num;
            i = j;
        }
        int tot = R - L;
        return (double)num / tot;
    }
};
