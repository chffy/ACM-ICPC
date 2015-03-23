#include <iostream>
#include <cstdio>
#include <cstring>
#include <algorithm>
#include <vector>
#include <cmath>
using namespace std;

double sqr(double x) {
    return x * x;
}

double dis(double x, double y) {
    return sqrt(sqr(x) + sqr(y));
}

double len[500], event[500000];
int ll[500], rr[500];

const double esp = 1e-11;
int n, m;

int parent[30];

int find(int x) {
    if (parent[x] != x) parent[x] = find(parent[x]);
    return parent[x];
}

pair<double, int> edge[500];

double calc(double A, double B, double C, double X) {
    return A * sqr(X) + B * X + C;
}

double mst(double l, double r) {
    for (int i = 0; i < m; ++i)
	edge[i] = make_pair(sqr((r + l) / 2 - len[i]), i);
    sort(edge, edge + m);
    double A = n - 1, B = 0, C = 0;
    for (int i = 0; i < n; ++i) parent[i] = i;
    for (int i = 0; i < m; ++i) {
	int id = edge[i].second;
	int x = ll[id], y = rr[id];
	if (find(x) == find(y)) continue;
	parent[find(x)] = find(y);
	B -= 2.0 * len[id];
	C += len[id] * len[id];
    }
    double t = - B / (A * 2.0);
    if (t >= l && t <= r) return calc(A, B, C, t);
    else return min(calc(A, B, C, l), calc(A, B, C, r));
}

class Egalitarianism2 {
public:
    double minStdev(vector <int> x, vector <int> y) {
	n = x.size();
	m = 0;
	double bmin = 1e60, bmax = 0;
	for (int i = 0; i < n; ++i)
	    for (int j = i + 1; j < n; ++j) {
		ll[m] = i; rr[m] = j;
		len[m++] = dis(x[i] - x[j], y[i] - y[j]);
		bmin = min(bmin, len[m - 1]);
		bmax = max(bmax, len[m - 1]);
	    }
	int num = 0;
	for (int i = 0; i < m; ++i)
	    for (int j = i + 1; j < m; ++j)
		event[num++] = (len[i] + len[j]) / 2.0;
	sort(event, event + num);
	double cur = bmin - esp, ans = 1e60; 
	for (int i = 0; i < num; ++i) {
	    if (fabs(event[i] - cur) < esp) continue;
	    ans = min(ans, mst(cur, event[i]));
	    cur = event[i];
	}
	ans = min(ans, mst(cur, bmax + esp));
	return sqrt(ans / (n - 1));
    }
};
