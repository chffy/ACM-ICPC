#include <iostream>
#include <cstdio>
#include <cstring>
#include <vector>
#include <queue>
#include <algorithm>
using namespace std;

int nexR[10000];
int nexB[10000];
int a[10000];

int isprime(int x) {
    if (x == 1) return 0;
    for (int i = 2; i * i <= x; ++i)
        if (x % i == 0) return 0;
    return 1;
}

int L[1000], R[1000];

class ColorfulCards {
public:
    vector <int> theCards(int n, string colors) {
        int m = colors.size();
        for (int i = n, pR = n + 1, pB = n + 1; i >= 0; --i) {
            nexR[i] = pR;
            nexB[i] = pB;
            if (i > 0 && isprime(i)) pR = i;
            else pB = i;
        }
        for (int i = 0, j = 0; i < m; ++i) {
            if (colors[i] == 'R') j = nexR[j];
            else j = nexB[j];
            L[i] = j;
        }
        for (int i = 1, pR = 0, pB = 0; i <= n + 1; ++i) {
            nexR[i] = pR;
            nexB[i] = pB;
            if (i <= n && isprime(i)) pR = i;
            else pB = i;
        }
        for (int i = m - 1, j = n + 1; i >= 0; --i) {
            if (colors[i] == 'R') j = nexR[j];
            else j = nexB[j];
            R[i] = j;
        }
        vector<int> ans;
        for (int i = 0; i < m; ++i)
            if (L[i] == R[i]) ans.push_back(L[i]);
            else ans.push_back(-1);
        return ans;
    }
};
