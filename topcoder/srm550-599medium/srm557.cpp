#include <iostream>
#include <cstdio>
#include <vector>
#include <cstring>
using namespace std;

int map1[100][100];
int mark[100];
int map2[100][100];
int bo[100], my[100];
int n;

int find(int x) {
    for (int i = 1; i <= n; ++i)
	if (map2[x][i] && !bo[i]) {
	    bo[i] = 1;
	    if (!my[i] || find(my[i])) {
		my[i] = x;
		return 1;
	    }
	}
    return 0;
}

class Incubator {
public:
    int maxMagicalGirls(vector <string> love) {
	n = love.size();
	for (int i = 0; i < n; ++i)
	    for (int j = 0; j < n; ++j)
		map1[i + 1][j + 1] = (love[i][j] == 'Y');
	for (int k = 1; k <= n; ++k)
	    for (int i = 1; i <= n; ++i)
		for (int j = 1; j <= n; ++j)
		    map1[i][j] |= map1[i][k] & map1[k][j];
	int ans = 0;
	memset(map2, 0, sizeof(map2));
	for (int i = 1; i <= n; ++i)
	    if (!map1[i][i]) {
		++ans;
		for (int j = 1; j <= n; ++j)
		    if (i != j && !map1[j][j])
			map2[i][j] = map1[i][j];
	    }
	memset(my, 0, sizeof(my));
	for (int i = 1; i <= n; ++i) {
	    memset(bo, 0, sizeof(bo));
	    if (find(i)) --ans;
	}
	return ans;
    }
};
