#include <iostream>
#include <cstdio>
#include <cstring>
#include <vector>
#include <algorithm>
#include <queue>
using namespace std;
 
int f[3000];
queue<int> que;
 
class ShufflingCardsDiv1 {
public:
    int shuffle(vector <int> p) {
  int n = p.size(), i, m = n / 2;
  for (i = 0; i < n; ++i)
      if (i + 1 != p[i]) break;
  if (i >= n) return 0;
  memset(f, 63, sizeof(f));
  int c = 0;
  for (int i = 0; i < n; i += 2)
      if (p[i] <= m) ++c;
  f[c] = 1;
  que.push(c);
  int numa = m + 1 >> 1, numb = m - numa;
  while (!que.empty()) {
      int x = que.front();  que.pop();
     // printf("%d %d\n", x, f[x]);
      int y = m - x;
      int l1 = n + 1, r1 = -1;
      for (int i = 0; i <= x; ++i)
    if (i <= numa && m - x >= numa - i) {
        l1 = min(l1, i);
        r1 = max(r1, i);
    }
      int l2 = n + 1, r2 = -1;
      for (int i = 0; i <= y; ++i)
    if (i <= numb && m - y >= numb - i) {
        l2 = min(l2, i);
        r2 = max(r2, i);
    }
      for (int i = 0; i <= n; ++i)
    if (i >= l1 + l2 && i <= r1 + r2) {
        if (f[i] > f[x] + 1) {
      f[i] = f[x] + 1;
      que.push(i);
        }
    }
  }
  if (f[m] >= 100000) f[m] = -1;
  return f[m];
    }
};
