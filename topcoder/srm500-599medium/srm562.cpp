#include <iostream>
#include <cstdio>
#include <cstring>
#include <algorithm>
#include <vector>
using namespace std;

const int N = 233;
int n, m;
typedef long long LL;

struct Point {
    int x, y;

    Point operator - (const Point &a) const {
        return (Point) {x - a.x, y - a.y};
    }

    LL operator * (const Point &a) const {
        return (LL)x * a.y - (LL)y * a.x;
    }
}white[N], black[N];

int get_input(vector<string> sx, int a[]) {
    string S = "";
    int n = 0;
    for (int i = 0; i < sx.size(); ++i) S += sx[i];
    int p = 0;
    while (p < S.size()) {
        a[n] = 0;
        while (p < S.size() && isdigit(S[p])) {
            a[n] = a[n] * 10 + S[p] - '0';
            ++p;
        }
        ++n;
        while (p < S.size() && !isdigit(S[p])) ++p;
    }
    return n;
}

int gett(vector<string> X, vector<string> Y, Point P[]) {
    static int a[N];
    int n = get_input(X, a);
    for (int i = 0; i < n; ++i) P[i].x = a[i];
    get_input(Y, a);
    for (int i = 0; i < n; ++i) P[i].y = a[i];
    return n;
}

Point ZERO;

int cmp(Point a, Point b) {
    return (a - ZERO) * (b - ZERO) < 0;
}

class CheckerFreeness {
public:
    string isFree(vector <string> whiteX, vector <string> whiteY,
                  vector <string> blackX, vector <string> blackY) {
        n = gett(whiteX, whiteY, white);
        m = gett(blackX, blackY, black);
        for (int i = 0; i < n; ++i)
            for (int j = i + 1; j < n; ++j) {
                int p = 0, q = 0;
                static Point C[N], D[N];
                ZERO = white[j];
                for (int k = 0; k < m; ++k)
                    if ((white[i] - ZERO) * (black[k] - ZERO) > 0)
                        C[p++] = black[k];
                    else D[q++] = black[k];
                sort(C, C + p, cmp);
                sort(D, D + q, cmp);
                int L = 0;
                bool flag = 0;
                Point mark;
                for (int k = 0; k < p; ++k) {
                    while (L < q && (C[k] - ZERO) * (D[L] - ZERO) < 0) {
                        if (flag == 0) {
                            flag = 1;
                            mark = D[L];
                        }
                        else {
                            if ((mark - white[i]) * (D[L] - white[i]) < 0)
                                mark = D[L];
                        }
                        ++L;
                    }
                    if (flag && (C[k] - white[i]) * (mark - white[i]) > 0)
                        return "NO";
                }
            }
        return "YES";
    }
};
