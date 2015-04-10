#include <iostream>
#include <cstdio>
#include <cstring>
#include <algorithm>
#include <vector>
using namespace std;

typedef long long LL;

const int N = 2e5 + 5, zero = 1e5;

struct Point {
    int x, y;
    
    LL operator * (const Point &a) const {
        return (LL)x * a.y - (LL)a.x * y;
    }

    int operator < (const Point &a) const {
        return make_pair(x, y) < make_pair(a.x, a.y);
    }

    int operator == (const Point &a) const {
        return make_pair(x, y) == make_pair(a.x, a.y);
    }
    
    Point operator - (const Point &a) const {
        return (Point) {x - a.x, y - a.y};
    }
}p[55];


int low[N], high[N];

Point p0, p1;
int n, flag0, flag1;

int check(int x, int y) {
	//printf("%d %d\n", x, y);
    Point pp = (Point) {x, y};
    for (int i = 0; i < n; ++i)
        if ((p[i + 1] - p[i]) * (pp - p[i]) < 0 || p[i] == pp)
            return 0;
    if (!flag0) {
        p0 = pp;
        flag0 = 1;
        return 0;
    }
    else if (p0 == pp) return 0;
    if (!flag1) {
        p1 = pp;
        flag1 = 1;
        return 0;
    }
    else if (p1 == pp) return 0;
    if ((pp - p0) * (p1 - p0) == 0) return 0;
    return 1;
}

class ConvexPolygonGame {
public:
    string winner(vector <int> X, vector <int> Y) {
        n = X.size();
        int mx = -N, mn = N;
        for (int i = 0; i < n; ++i)
            low[i] = N, high[i] = -N;
        for (int i = 0; i < n; ++i) {
            p[i] = (Point) {X[i], Y[i]};
            mx = max(mx, X[i]);
            mn = min(mn, X[i]);
        }
        p[n] = p[0];
        int ans = 0;
        for (int i = 0; i < n; ++i)
            if (p[i].x == p[i + 1].x) {
                int t1 = min(p[i].y, p[i + 1].y);
                int t2 = max(p[i].y, p[i + 1].y);
                if (check(p[i].x, t1 + 1)) ans = 1;
                if (check(p[i].x, t2 - 1)) ans = 1;
            }
            else {
                int L = min(p[i].x, p[i + 1].x), R = max(p[i].x, p[i + 1].x);
                for (int j = L; j <= R; ++j) {
                    Point C = p[i + 1] - p[i];
                    LL yy = (LL)(j - p[i].x) * C.y / C.x + p[i].y;
                    for (int k = -2; k <= 2; ++k) {
                        if (check(j, yy + k)) ans = 1;
                    }
                }
            }
        if (ans) return "Masha";
        else return "Petya";
    };
};