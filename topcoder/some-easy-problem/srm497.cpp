#include <iostream>
#include <cstdio>
#include <cstring>
#include <vector>
#include <queue>
#include <algorithm>
using namespace std;

class PermutationSignature {
public:
    vector <int> reconstruct(string sig) {
        vector<int> ans;
        ans.push_back(1);
        for (int i = (int)sig.size() - 1; i >= 0; --i) {
            int t;
            if (sig[i] == 'D') {
                t = ans.back() + 1;
            }
            else t = 1;
            for (int j = 0; j < ans.size(); ++j)
                if (ans[j] >= t) ans[j]++;
            ans.push_back(t);
        }
        reverse(ans.begin(), ans.end());
        return ans;
    }
};
