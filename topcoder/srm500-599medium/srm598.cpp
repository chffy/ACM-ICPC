#include <iostream>
#include <cstdio>
#include <cstring>
#include <algorithm>
#include <vector>
using namespace std;

typedef long long LL;

int check(int mov1, int rng1, int mov2, int rng2, int d) {
    if (mov1 + rng1 >= d) return 1;
    int p = mov2 + rng2 + 1;
    if (mov1 + rng1 >= (LL)p + mov2 && mov2 < mov1) return 1;
    return 0;
}

class FoxAndFencing {
public:
    string WhoCanWin(int mov1, int mov2, int rng1, int rng2, int d) {
	if (check(mov1, rng1, mov2, rng2, d)) return "Ciel";
	else if (check(mov2, rng2, mov1, rng1, d + mov1)) return "Liss";
	else return "Draw";
    }
};
