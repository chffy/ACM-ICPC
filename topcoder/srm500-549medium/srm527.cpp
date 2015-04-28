#include <iostream>
#include <cstdio>
#include <cstring>
#include <algorithm>
#include <vector>
#include <cassert>
using namespace std;

bool graph[33][33];
bool f[33][33], vis[33];
int my[33], mt[33];

bool find(int x, int n) {
    for (int i = 0; i < n; ++i)
	if (!vis[i] && f[x][i]) {
	    vis[i] = true;
	    if (my[i] == -1 || find(my[i], n)) {
			my[i] = x;
			return true;
	    }
	}
    return false;
}

bool check(int n) {
    memset(my, -1, sizeof(my));
    int ans = 0;
    for (int i = 0; i < n; ++i) {
	memset(vis, false, sizeof(vis));
	if (find(i, n)) ++ans;
    }
    if (ans == n) return true;
    return false;
}

class P8XMatrixRecovery {
public:
    vector <string> solve(vector <string> rows, vector <string> columns) {
	int R = rows.size(), C = rows[0].size();
	memset(graph, false, sizeof(graph));
	for (int i = 0; i < C; ++i)
	    for (int j = 0; j < C; ++j) {
			int k;
			for (k = 0; k < R; ++k)
			    if (rows[k][i] != columns[j][k] && 
				rows[k][i] != '?' && columns[j][k] != '?')
					break;
			if (k >= R) graph[i][j] = true;
	    }
	for (int x = 0; x < R; ++x)
	    for (int y = 0; y < C; ++y) 
		if (rows[x][y] == '?') {
		    memcpy(f, graph, sizeof(f));
		    memset(f[y], false, sizeof(f[y]));
		    for (int i = 0; i < C; ++i)
			if (graph[y][i] && columns[i][x] != '1')
			    f[y][i] = true;
		    if (check(C)) 
			memcpy(graph, f, sizeof(graph));  
		}
	memcpy(f, graph, sizeof(f));
	assert(check(C));
	for (int i = 0; i < C; ++i)
		mt[my[i]] = i;
	for (int i = 0; i < R; ++i)
	    for (int j = 0; j < C; ++j) 
		if (rows[i][j] == '?') {
		    if (columns[mt[j]][i] == '?')
			rows[i][j] = '0';
		    else rows[i][j] = columns[mt[j]][i];
		}
	return rows;
    }
};
