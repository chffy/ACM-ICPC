#include <iostream>
#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;

double f[50][50][50];
double g[50][50][50], h[50][50][50];
int t[50][50][50];

int gett(int i, int d2, int maxR) {
    if (d2 < 0) return 0;
    return  (i > d2 ? d2 : i) + ((maxR - i - 1) > d2 ? d2 : (maxR - i - 1)) + 1;
}

class RandomColoring {
public:
    double getProbability(int n, int maxR, int maxG, int maxB, int startR, int startG, int startB, int d1, int d2) {
        for (int i = 0; i < maxR; ++i)
            for (int j = 0; j < maxG; ++j)
                for (int k = 0; k < maxB; ++k) {
                    int l1 = abs(i - startR), l2 = abs(j - startG), l3 = abs(k - startB);
                    if (l1 > d2 || l2 > d2 || l3 > d2 ||
                        (l1 < d1 && l2 < d1 && l3 < d1))
                        f[i][j][k] = 1;
                    int p0 = gett(i, d2, maxR);
                    int q0 = gett(i, d1 - 1, maxR);
                    int p1 = gett(j, d2, maxG);
                    int q1 = gett(j, d1 - 1, maxG);
                    int p2 = gett(k, d2, maxB);
                    int q2 = gett(k, d1 - 1, maxB);
                    t[i][j][k] = p0 * p1 * p2 - q0 * q1 * q2;
                }
        for (int p = 1; p < n; ++p) {
        	memset(g, 0, sizeof(g));
        	memset(h, 0, sizeof(h));
            for (int i = 0; i < maxR; ++i)
                for (int j = 0; j < maxG; ++j)
                    for (int k = 0; k < maxB; ++k)
                        g[i][j][k] = h[i][j][k] = f[i][j][k];
            int len[3];
            len[0] = maxR, len[1] = maxG, len[2] = maxB;
            for (int l = 0; l < 3; ++l) {
                for (int i = 0; i < len[0]; ++i)
                    for (int j = 0; j < len[1]; ++j) {
                        int head0 = 0, tail0 = -1, head1 = 0, tail1 = -1;
                        static double a[50], b[50];
                        double tmp0 = 0, tmp1 = 0, tmp2 = 0;
                        for (int k = 0; k < len[2]; ++k) {
                            a[k] = (l == 0) ? g[i][j][k] : ((l == 1) ? g[j][k][i] : g[k][i][j]);
                            b[k] = (l == 0) ? h[i][j][k] : ((l == 1) ? h[j][k][i] : h[k][i][j]);
                        }
                        for (int k = 0; k < len[2]; ++k) {
                            while (abs(tail0 + 1 - k) <= d2 && tail0 + 1 < len[2])
                                tmp0 += a[++tail0], tmp2 += b[tail0];
                            while (abs(head0 - k) > d2 && head0 <= tail0)
                                tmp0 -= a[head0], tmp2 -= b[head0++];
                            while (abs(tail1 + 1 - k) <= d1 - 1 && tail1 + 1 < len[2])
                                tmp1 += b[++tail1];
                            while (abs(head1 - k) > d1 - 1 && head1 <= tail1)
                                tmp1 -= b[head1++];
                            if (l == 0) {
                                g[i][j][k] = tmp0;
                                h[i][j][k] = tmp1;
                            }
                            else if (l == 1) {
                                g[j][k][i] = tmp0;
                                h[j][k][i] = tmp1;
                            }
                            else if (l == 2) {
                                g[k][i][j] = tmp0;
                                h[k][i][j] = tmp1;
                            }
                        }
                        
                }
                swap(len[1], len[2]);
                swap(len[0], len[1]);
            }
            for (int i = 0; i < maxR; ++i)
                for (int j = 0; j < maxG; ++j)
                    for (int k = 0; k < maxB; ++k) {
                        f[i][j][k] = (t[i][j][k] == 0) ? 0 : ((g[i][j][k] - h[i][j][k]) / t[i][j][k]);
                    }
        }
        return f[startR][startG][startB];
    }
};
