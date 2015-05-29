#include <iostream>
#include <cstring>
#include <cstdio>
#include <vector>
#include <queue>
#include <algorithm>
using namespace std;

const int P = 1e9 + 7;
typedef long long LL;

int num[200];

int cmp(int a, int b) {
	return a > b;
}

class RowsOrdering {
public:

    int gett(char ch) {
        if (islower(ch)) return ch - 'a';
        return ch - 'A' + 26;
    }
    
    int order(vector <string> rows) {
        int n = rows.size(), m = rows[0].size();
        int ans = 0;
        vector<int> arr;
        for (int i = m - 1; i >= 0; --i) {
            memset(num, 0, sizeof(num));
            for (int j = 0; j < n; ++j)
                num[gett(rows[j][i])]++;
            sort(num, num + 100, cmp);
            int res = 0;
            for (int j = 0; j < 100; ++j) 
                res += num[j] * j;
            arr.push_back(res);
        }
        sort(arr.begin(), arr.end());
        reverse(arr.begin(), arr.end());
        for (int i = 0, base = 1; i < arr.size(); ++i, base = (LL)base * 50 % P) {
            ans = (ans + (LL)base * arr[i]) % P;
        }
        return (ans + n) % P;
    }
};
