#include <iostream>
#include <cstdio>
#include <cstring>
#include <vector>
#include <queue>
#include <map>
#include <algorithm>
#include <set>
using namespace std;

const int N = 1e7;

int prime[N];
bool bo[N];

class PrimeSequences {
public:
    int getLargestGenerator(int n, int D) {
        int m = 0;
        for (int i = 2; i < N; ++i) {
            if (bo[i] == false) {
                prime[m++] = i;
            }
            for (int j = 0; j < m && i * prime[j] < N; ++j) {
                bo[i * prime[j]] = true;
                if (i % prime[j] == 0) break;
            }
        }
        bo[1] = bo[0] = true;
        for (int i = n; i > 1; --i) {
            int num = 0, x = i;
            while (num < D && bo[x] == false) {
                ++num;
                x /= 2;
            }
            if (num >= D) return i;
        }
        return -1;
    }
};
