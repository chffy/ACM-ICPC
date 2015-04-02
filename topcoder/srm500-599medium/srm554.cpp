#include <iostream>
#include <cstdio>
#include <cstring>
#include <vector>
#include <algorithm>
using namespace std;

const int inf = 1e9;

pair<int, int> a[1000];

class TheBrickTowerMediumDivOne {
public:
    vector <int> find(vector <int> heights) {
	vector<int> ansp;
	int n = heights.size();
	ansp.push_back(0);
	int sum = 0;
	for (int i = 1; i < n; ++i) {
	    int p = heights[ansp[ansp.size() - 1]];
	    if (p >= heights[i]) ansp.push_back(i);
	    else a[++sum] = make_pair(heights[i], i);
	}
	if (sum == 0) return ansp;
	sort(a + 1, a + 1 + sum);
	for (int i = 1; i <= sum; ++i) 
	    ansp.push_back(a[i].second);
	return ansp;
    }
};
