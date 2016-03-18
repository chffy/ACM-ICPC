#include <iostream>
#include <cstdio>
#include <cstring>
#include <vector>
#include <algorithm>
#include <set>
#include <cmath>
#include <stack>
#include <deque>
using namespace std;

int solve(int A, int B, int goalx, int goaly) {
    if (A == 0) return solve(B, A, goaly, goalx);
    if (A == 1) {
        if (goalx < 2 || goaly < 2) return 0;
        return 1;
    }
    if (goalx != 4) return 0;
    return goaly + 1;
}

class DiceRotation {
public:
    int theCount(int goalx, int goaly) {
        return solve(2, 0, goalx, goaly) + solve(1, 1, goalx, goaly) * 2 + solve(0, 2, goalx, goaly);
    }
};

