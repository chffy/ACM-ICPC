#include <iostream>
#include <cstdio>
#include <cstring>
#include <algorithm>
#include <vector>
using namespace std;

typedef long long LL;

int check(LL E, LL EM, LL M, LL MH, LL H, LL x) {
    if (x > H) {
        if (MH + H < x) return 0;
        MH -= x - H;
    }
    M += MH;
    if (x > M) {
        if (EM + M < x) return 0;
        EM -= x - M;
    }
    E += EM;
    if (E < x) return 0;
    return 1;
}

class ProblemSets {
public:
    LL maxSets(LL E, LL EM, LL M, LL MH, LL H) {
        LL head = 0, tail = 2e18;
        while (head < tail - 1) {
            LL mid = (head + tail) >> 1;
            if (check(E, EM, M, MH, H, mid)) head = mid;
            else tail = mid;
        }
        return head;
    }
};
