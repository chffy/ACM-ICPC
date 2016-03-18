#include <iostream>
#include <cstdio>
#include <cstring>
#include <vector>
#include <algorithm>
#include <set>
#include <cmath>
#include <stack>
#include <deque>
using namespace std;

int lcp1[100][100], lcp2[100][100], mx1[100][100][100], mx2[100][100][100];

void init(string J, string B, int lcp[100][100], int mx[100][100][100]) {
    int n = J.size(), m = B.size();
    for (int i = 0; i < n; ++i)
        for (int j = i; j < n; ++j) {
            for (int k = 0; k < n; ++k) {
                int len = 0;
                while (i + len <= j && k + len < n && J[i + len] == J[k + len] &&
                       !(k + len >= i && k + len <= j))
                    ++len;
                lcp[i][j] = max(len, lcp[i][j]); 
                if (len == j - i + 1) {
                    int p = k + len;
                    for (int l = 0; l < m; ++l) {
                        int len = 0;
                        while (p + len < n && l + len < m && J[p + len] == B[l + len] &&
                               !(p + len >= i && p + len <= j)) 
                        	++len;
                        mx[i][j][l] = max(mx[i][j][l], len);
                    }
                }
            }
        }
}

int T[100][100], T1[100][100][100];

class TheBoringStoreDivOne {
public:
    string find(string J, string B) {
        int n = J.size(), m = B.size();
        init(J, B, lcp1, mx1);
        reverse(J.begin(), J.end());
        reverse(B.begin(), B.end());
        init(B, J, lcp2, mx2);
        reverse(J.begin(), J.end());
        reverse(B.begin(), B.end());

        memcpy(T1, mx2, sizeof(T1));
        for (int i = 0; i < m; ++i)
            for (int j = 0; j < m; ++j)
                for (int k = 0; k < n; ++k)
                mx2[i][j][k] = T1[m - i - 1][m - j - 1][n - k - 1];
        memcpy(T, lcp2, sizeof(T));
        for (int i = 0; i < m; ++i)
            for (int j = 0; j < m; ++j)
                lcp2[i][j] = T[m - i - 1][m - j - 1];
        string ans = "";
        for (int i = 0; i < n; ++i)
            for (int j = i; j < n; ++j) {
                if (lcp1[i][j] == 0) continue;
                for (int k = 0; k < m; ++k)
                    for (int l = k; l < m; ++l) {
                        if (lcp2[l][k] == 0) continue;
                        int flag = 0;
                        if (lcp1[i][j] == j - i + 1 && mx1[i][j][k] + lcp2[l][k] >= l - k + 1)
                            flag = 1;
                        if (lcp2[l][k] == l - k + 1 && mx2[l][k][j] + lcp1[i][j] >= j - i + 1)
                            flag = 1;
                        if (flag == 1) {
                            string S = "";
                            for (int p = i; p <= j; ++p)
                                S += J[p];
                            for (int p = k; p <= l; ++p)
                                S += B[p];
                            if (S.size() > ans.size() || (S < ans && S.size() == ans.size()))
                                ans = S;
                        }
                    }
            }
        return ans;
    }
};
