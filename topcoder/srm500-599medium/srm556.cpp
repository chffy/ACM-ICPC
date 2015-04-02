#include <iostream>
#include <cstdio>
#include <cstring>
using namespace std;

string f[51][51][3];

void solve(string &s1, string s2) {
    if (s1 == "" || s1 > s2) s1 = s2;
}

class LeftRightDigitsGame2 {
public:
    string minNumber(string di, string lo) {
	int n = di.size();
	for (int i = 0; i < n; ++i) {
	    int t1 = di[0] - '0', t2 = lo[i] - '0';
	    int t3;
	    if (t1 < t2) t3 = 0;
	    if (t1 == t2) t3 = 1;
	    if (t1 > t2) t3 = 2;
	    f[1][i + 1][t3] += di[0];
	}
	for (int i = 1; i < n; ++i)
	    for (int j = 1; j <= n; ++j) 
		for (int k = 0; k < 3; ++k){
		    if (f[i][j][k] == "") continue;
		    int l = j + i - 1, k1 = 0;
		    if (l < n) {
			if (k != 1) 
			    solve(f[i + 1][j][k], f[i][j][k] + di[i]);
			else {
			    if (di[i] < lo[l]) k1 = 0;
			    if (di[i] > lo[l]) k1 = 2;
			    if (di[i] == lo[l]) k1 = 1;
			    solve(f[i + 1][j][k1], f[i][j][k] + di[i]);
			}
		    }
		    if (j != 1) {
			if (di[i] > lo[j - 2]) 
			    solve(f[i + 1][j - 1][2], di[i] + f[i][j][k]);
			if (di[i] < lo[j - 2])
			    solve(f[i + 1][j - 1][0], di[i] + f[i][j][k]);
			if(di[i] == lo[j - 2])
			    solve(f[i + 1][j - 1][k], di[i] + f[i][j][k]);
		    }
                }
	if (f[n][1][1] != "") return f[n][1][1];
	return f[n][1][2];
    }
};
