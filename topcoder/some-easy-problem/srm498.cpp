#include <iostream>
#include <cstdio>
#include <cstring>
#include <vector>
#include <queue>
#include <algorithm>
using namespace std;

int f[5][55];

class FoxSequence {
public:
    string isValid(vector <int> seq) {
        int n = seq.size();
        for (int i = 1; i < n; ++i)
            if (seq[i] - seq[i - 1] == seq[1] - seq[0] &&
                seq[i] - seq[i - 1] > 0) {
                f[0][i] = 1;
            }
            else break;
        for (int i = 1; i < n; ++i)
            if (f[0][i]) {
                for (int j = i + 1; j < n; ++j)
                    if (seq[j] - seq[j - 1] == seq[i + 1] - seq[i] &&
                        seq[j] - seq[j - 1] < 0) {
                        f[1][j] = 1;
                    }
                    else break;
            }
        for (int i = 1; i < n; ++i)
            if (f[1][i]) {
                f[2][i] = 1;
                for (int j = i + 1; j < n; ++j)
                    if (seq[j] == seq[i]) {
                        f[2][j] = 1;
                    }
                    else break;
            }
        for (int i = 1; i < n; ++i)
            if (f[2][i]) {
                for (int j = i + 1; j < n; ++j)
                    if (seq[j] - seq[j - 1] == seq[i + 1] - seq[i] &&
                        seq[j] - seq[j - 1] > 0) {
                        f[3][j] = 1;
                    }
                    else break;
            }
        for (int i = 1; i < n; ++i)
            if (f[3][i]) {
                for (int j = i + 1; j < n; ++j)
                    if (seq[j] - seq[j - 1] == seq[i + 1] - seq[i] &&
                        seq[j] - seq[j - 1] < 0) {
                        if (j == n - 1) return "YES";
                    }
                    else break;
            }
        return "NO";
    }
};

