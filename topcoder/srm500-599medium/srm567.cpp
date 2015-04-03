#include <iostream>
#include <cstdio>
#include <cstring>
#include <vector>
#include <cassert>
using namespace std;

int num[51][51];
int bo1[51], bo2[50];

class StringGame {
public:
    vector <int> getWinningStrings(vector <string> S) {
	vector <int> ans;
	int n = S.size(), m = S[0].size();
	for (int i = 0; i < n; ++i) {
	    for (int j = 0; j < m; ++j)
		num[i][S[i][j] - 'a']++;
	}
	for (int i = 0; i < n; ++i) {
	    memset(bo1, 0, sizeof(bo1));
	    memset(bo2, 0, sizeof(bo2));
	    bo1[i] = 1;
	    for (int j = 0; j < 26; ++j) {
		int k = 0;
		for (k = 0; k < 26; ++k) {
		    if (bo2[k]) continue;
		    int flag = 0;
		    for (int l = 0; l < n; ++l) { 
			if (bo1[l]) continue;
			if (num[l][k] > num[i][k]) {
			    flag = 0;
			    break;
			}
			if (num[l][k] == num[i][k]) continue;
			flag = 1;
		    }
		    if (flag) break;
		}
		if (k < 26) {
		    bo2[k] = 1;
		    for (int l = 0; l < n; ++l) {
			if (num[l][k] < num[i][k]) bo1[l] = 1;
			if (!bo1[l]) assert(num[l][k] <= num[i][k]);
		    }
		    continue;
		}
	    }
	    int j;
	    for (j = 0; j < n; ++j)
		if (!bo1[j]) break;
	    if (j < n) continue;
	    ans.push_back(i);
	}
	return ans;
    }
};
