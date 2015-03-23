#include <iostream>
#include <cstdio>
#include <cstring>
#include <vector>
#include <algorithm>
using namespace std;

typedef long long LL;

int xc(int x1, int y1, int x2, int y2) {
    return x1 * y2 - x2 * y1;
}

class TrianglesContainOrigin {
public:
    LL count(vector <int> x, vector <int> y) {
  int n = x.size();
  LL ans = 0;
  for (int i = 0; i < n; ++i) {
    int k = -1;
    if (x[i] > 0) k = 1;
      int sum1 = 0, sum2 = 0;
      for (int j = 0; j < n; ++j) {
      int l = 1;
      if (x[j] <= 0) l = -1;
    if (k * l > 0) continue;
    if (xc( - x[i],  - y[i], x[j] - x[i], y[j] - y[i]) > 0) ++sum1;
    else ++sum2;

      }
      ans += (LL)sum1 * sum2;
  }

  return ans;
    }
};
