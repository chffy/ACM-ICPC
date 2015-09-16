#include <iostream>
#include <cstdio>
#include <cstring>
#include <vector>
#include <queue>
#include <algorithm>
using namespace std;

typedef long long LL;

class SubFibonacci {
public:

    int solve(vector<int> A) {
        if (A.size() < 3) return A.size();
        sort(A.begin(), A.end());
        int n = A.size();
        int ans = 2;
        for (int i = 0; i < n; ++i)
            for (int j = i + 1; j < n; ++j) {
                pair<LL, LL> a = make_pair(0, A[i]), b = make_pair(1, A[i]);
                vector<LL> tmp;
                while ((A[j] - b.second) / b.first + A[i] > 0) {
                    if ((A[j] - b.second) % b.first == 0)
                        tmp.push_back((A[j] - b.second) / b.first);
                    pair<LL, LL> c = make_pair(a.first + b.first, a.second + b.second);
                    a = b; b = c;
                }
                for (int k = 0; k < tmp.size(); ++k) {
                    LL a = tmp[k], b = A[i];
                    int ans1 = 2;
                    while (b <= A.back()) {
                        if (b > A[j] && *lower_bound(A.begin(), A.end(), (int)b) == b)
                            ++ans1;
                        LL c = a + b;
                        a = b;  b = c;
                    }
                    ans = max(ans, ans1);
                }
            }
        return ans;
    }
    
    int maxElements(vector <int> S) {
        sort(S.begin(), S.end());
        vector<int> A = S, B;
        int ans = 0;
        while (!A.empty()) {
            ans = max(ans, solve(A) + solve(B));
            int x = A.back();
            A.pop_back();
            B.push_back(x);
        }
        return ans;
    }
};
