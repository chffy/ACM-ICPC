#include <iostream>
#include <cstdio>
#include <cstring>
#include <algorithm>
#include <vector>
using namespace std;

int f[51][51];
int num[51][51];
long long C[51][51];

class KingXMagicSpells {
public:
    double expectedNumber(vector <int> ducks, vector <int> spellOne, vector <int> spellTwo, int K) {
	int n = ducks.size();
	for (int i = 0; i < n; ++i)
	    f[i][0] = i, num[i][0] = ducks[i];
	for (int i = 1; i <= K; ++i)
	    for (int j = 0; j < n; ++j) {
		num[j][i] = num[j][i - 1] ^ spellOne[j];
		f[j][i] = spellTwo[f[j][i - 1]];
	    }
	double ans = 0;
	for (int i = 0; i <= 50; ++i)
	    for (int j = 0; j <= i; ++j)
		C[i][j] = j == 0 ? 1 : C[i - 1][j] + C[i - 1][j - 1];
	for (int j = 0; j <= K; ++j) {
	    for (int i = 0; i < n; ++i) 
		if (f[i][j] == 0) {
		    int p = num[i][K - j];
		    // K - j goods, j + 1 boxs;
		    // C(K, j)
		    double ans1 = C[K][j];
		    for (int k = 1; k <= K; ++k)
			ans1 = ans1 / 2;
		    ans += ans1 * p;
		    if (j == 1) cout << i << endl;
		}
		if(j == 1) cout << ans << endl;
	}
	return ans;
    }
};
