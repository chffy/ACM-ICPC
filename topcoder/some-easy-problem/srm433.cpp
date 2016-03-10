#include <iostream>
#include <cstdio>
#include <cstring>
#include <vector>
#include <algorithm>
#include <cmath>
using namespace std;

int b[100];

class MagicWords {
public:
    int count(vector <string> S, int K) {
        int n = S.size();
        for (int i = 0; i < n; ++i)
            b[i] = i;
        int ans = 0;
        do {
            string ss;
            for (int i = 0; i < n; ++i)
                ss += S[b[i]];
            int ret = 1;
            for (int i = 1; i <= ss.size(); ++i)
                if (ss.size() % i == 0) {
                    int flag = 1;
                    for (int j = 0; j + i < ss.size(); ++j)
                        if (ss[j] != ss[j + i]) flag = 0;
                    if (flag == 1) {
                        ret = i;
                        break;
                    }
                }
                //cout << ret << endl;
            if (ss.size() / ret == K) ++ans;
        } while (next_permutation(b, b + n));
        return ans;
    }
};

