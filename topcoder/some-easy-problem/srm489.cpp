#include <iostream>
#include <cstdio>
#include <cstring>
#include <vector>
#include <queue>
#include <algorithm>
using namespace std;

int f[100][100];

class BallsConverter {
public:
    string theGood(vector <string> tr) {
        int n = tr.size();
        for (int i = 0; i < n; ++i)
            for (int j = 0; j < n; ++j)
                if (isupper(tr[i][j])) {
                    f[i][j] = tr[i][j] - 'A';
                }
                else {
                    f[i][j] = tr[i][j] - 'a' + 26;
                }
        for (int i = 0; i < n; ++i)
            for (int j = 0; j < n; ++j)
                for (int k = 0; k < n; ++k)
                    if (f[f[i][j]][k] != f[i][f[j][k]]) return "Bad";
        return "Good";
    }
};
