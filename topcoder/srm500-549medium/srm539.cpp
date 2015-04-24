#include <iostream>
#include <cstdio>
#include <cstring>
#include <algorithm>
#include <vector>
using namespace std;

const int N = 60;
int floyed[N][N], my[N];
bool f[N][N], vis[N];

bool find(int x, int n) {
    for (int i = 1; i <= n; ++i)
	if (f[x][i] && !vis[i]) {
	    vis[i] = true;
	    if (!my[i] || find(my[i], n)) {
		my[i] = x;  
		return true;
	    }
	}
    return false;
}

class SafeReturn {
public:
    int minRisk(int n, vector <string> streets) {
	int T = streets.size();
	memset(floyed, 63, sizeof(floyed));
	memset(f, false, sizeof(f));
	for (int i = 0; i < T; ++i)
	    for (int j = 0; j < T; ++j) 
		if (streets[i][j] != '-') 
		    floyed[i][j] = streets[i][j] - '0';
	for (int i = 0; i < T; ++i)
	    floyed[i][i] = 0;
	for (int k = 0; k < T; ++k)
	    for (int i = 0; i < T; ++i)
		for (int j = 0; j < T; ++j)
		    floyed[i][j] = min(floyed[i][j], floyed[i][k] + floyed[j][k]);
	for (int i = 1; i <= n; ++i)
	    for (int j = 1; j <= n; ++j)
		if (i != j && floyed[0][j] + floyed[j][i] == floyed[0][i]) f[i][j] = true;
	memset(my, 0, sizeof(my));
	int ans = n;
	for (int i = 1; i <= n; ++i) {
	    memset(vis, false, sizeof(vis));
	    if (find(i, n)) -- ans;
	}
	return ans;
    }
};
