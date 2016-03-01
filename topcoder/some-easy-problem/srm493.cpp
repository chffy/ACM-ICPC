#include <iostream>
#include <cstdio>
#include <cstring>
#include <vector>
#include <queue>
#include <algorithm>
using namespace std;

int check(int N, int M, int K, int L) {
    if (abs(M - L) + 1 > K) return 0;
    if (abs(M - L) % 2 == K % 2) return 0;
    if (M > L) swap(M, L);
    K -= L - M + 1;
    K /= 2;
    if (M - K <= 0) return 0;
    if (L + K > N) return 0;
    return 1;
}

class StonesGame {
public:
    string winner(int N, int M, int K, int L) {
        if (check(N, M, K, L)) return "Romeo";
        int flag = 0;
        for (int i = 1; i + K - 1 <= N; ++i) {
            if (i > M) continue;
            if (i + K - 1 < M) continue;
            int t = i + K - 1 - (M - i);
            if (check(N, t, K, L) == 0) flag = 1;
        }
        if (flag == 0) return "Strangelet";
        return "Draw";
    }
};
