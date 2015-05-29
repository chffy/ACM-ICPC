#include <iostream>
#include <cstring>
#include <cstdio>
#include <vector>
#include <queue>
using namespace std;

typedef long long LL;

class ConvexSequence {
public:
    LL getMinimum(vector <int> a) {
        int n = a.size();
        if (n < 3) return 0;
        vector<LL> b;
        for (int i = 1; i < n; ++i)
            b.push_back(a[i] - a[i - 1]);
        --n;
        LL ans = 0;
        for (int i = n - 2; i >= 0; --i) {
            while (b[i] > b[i + 1]) {
                int j = i + 1; 
                while (j + 1 < n && b[j + 1] == b[j])
                    ++j;
                int l = j - i;
                if (b[i] - b[i + 1] < l + 1) {
                	ans += l;
                	--b[i];
                	++b[j];
                	continue;
                }
                LL x = (b[i] - b[i + 1]) / (l + 1);
                if (j + 1 < n)
                    x = min(x, (LL)b[j + 1] - b[j]);
                ans += x * l * (l + 1) / 2;
                b[i] -= x * l;
                for (int k = i + 1; k <= j; ++k)
                    b[k] += x;
            }
        }
        return ans;
    }
};
