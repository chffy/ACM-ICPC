#include <iostream>
#include <cstdio>
#include <cstring>
#include <vector>
#include <algorithm>
#include <stack>
using namespace std;

vector<pair<int, int> > num[201];
vector<int> P;
int m1[201], m2[201], m3[201], m4[201];
int first[401], Next[10000], End[10000], tot;
int max1[401], min1[401], bo[401];
int color[401], cnt, sum, dfn[401], mark[401];

void addedge(int x, int y) {
    Next[++tot] = first[x];
    first[x] = tot;
    End[tot] = y;
}

stack<int> sta;

void dfs(int x) {
    mark[x] = dfn[x] = ++sum;
    bo[x] = 1;
    sta.push(x);
    for (int k = first[x]; k; k = Next[k]) {
	if (!bo[End[k]]) dfs(End[k]);
	mark[x] = min(mark[x], mark[End[k]]);
    }
    if (mark[x] == dfn[x]) {
	++cnt;
	int y;
	do {
	    y = sta.top();  sta.pop();
	    mark[y] = 1e9;
	    color[y] = cnt;
	} while (y != x); 
    }
}

int check(int n, int m) {
    memset(first, 0, sizeof(first));
    memset(max1, 63, sizeof(max1));
    memset(min1, 130, sizeof(min1));
    tot = 0;
    for (int i = 0; i < m; ++i) 
	if (m4[i] == 0) {
	    min1[m1[i]] = max(min1[m1[i]], m3[i]);
	    min1[m2[i]] = max(min1[m2[i]], m3[i]);
	}
	else {
	    max1[m1[i]] = min(max1[m1[i]], m3[i]);
	    max1[m2[i]] = min(max1[m2[i]], m3[i]);
	}	 
    for (int i = 0; i < n; ++i)
	if (min1[i] > max1[i]) return 0;
    for (int i = 0; i < m; ++i) {
	if (m4[i] == 0) {
	    if (min(min1[m1[i]], min1[m2[i]]) != m3[i]) return 0;
	}
	else {
	    if (max(max1[m1[i]], max1[m2[i]]) != m3[i]) return 0;
	}
	if (min1[m1[i]] != m3[i] && min1[m2[i]] != m3[i]) {
	    addedge(m1[i], m2[i] + n);
	    addedge(m2[i], m1[i] + n);
	}
	if (min1[m1[i]] != m3[i] && max1[m2[i]] != m3[i]) {
	    addedge(m1[i], m2[i]);
	    addedge(m2[i] + n, m1[i] + n);
	}
	if (max1[m1[i]] != m3[i] && min1[m2[i]] != m3[i]) {
	    addedge(m1[i] + n, m2[i] + n);
	    addedge(m2[i], m1[i]);
	}
	if (max1[m1[i]] != m3[i] && max1[m2[i]] != m3[i]) {
	    addedge(m1[i] + n, m2[i]);
	    addedge(m2[i] + n, m1[i]);
	}
    }
    sum = cnt = 0;
    memset(mark, 0, sizeof(mark));
    memset(bo, 0, sizeof(bo));
    for (int i = 0; i < n * 2; ++i)
	if (!bo[i]) dfs(i);
    for (int i = 0; i < n; ++i)
	if (color[i] == color[i + n]) return 0;
    return 1;
}

class GCDLCM {
public:
    string possible(int n, string type, vector <int> A, vector <int> B, vector <int> C) {
	int m = A.size();
	for (int i = 0; i < m; ++i) {
	    for (int j = 2; j * j <= C[i]; ++j)
		if (C[i] % j == 0) {
		    int sum = 0;
		    while (C[i] % j == 0) {
			C[i] /= j;
			++sum;
		    }
		    P.push_back(j);
		    num[i].push_back(make_pair(j, sum));
		}
	    if (C[i] != 1) {
		P.push_back(C[i]);
		num[i].push_back(make_pair(C[i], 1));
	    }
	    sort(num[i].begin(), num[i].end());
	}
	sort(P.begin(), P.end());
	P.erase(unique(P.begin(), P.end()), P.end());
	for (int i = 0; i < P.size(); ++i) {
		//printf("!%d %d\n", i, P[i]);
	    for (int j = 0; j < m; ++j) {
		int t;
		for (t = 0; t < num[j].size(); ++t)
		    if (num[j][t].first == P[i]) break;
		if (t >= num[j].size()) m3[j] = 0;
		else m3[j] = num[j][t].second;
		m1[j] = A[j], m2[j] = B[j];
		if (type[j] == 'G') m4[j] = 0;
		else m4[j] = 1;
		//printf("%d %d %d %d\n", m1[j], m2[j], m3[j], m4[j]);
	    }
	    if (!check(n, m)) return "Solution does not exist";
	}
	return "Solution exists";
    }
};
