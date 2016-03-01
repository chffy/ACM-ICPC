#include <iostream>
#include <cstdio>
#include <cstring>
#include <vector>
#include <queue>
#include <algorithm>
using namespace std;

int w[100][100];
int sum[100][100];

int check(vector<string> pic, int S) {
    memset(w, 0, sizeof(w));
    int n = pic.size(), m = pic[0].size();
    for (int i = 0; i + S <= n; ++i)
        for (int j = 0; j + S <= m; ++j) {
            int flag = 1;
            for (int k = 0; k < S; ++k)
                for (int l = 0; l < S; ++l)
                    if (pic[i + k][j + l] == 'W') flag = 0;
 //           if (S == 4) printf("%");
            if (flag == 1) {
                for (int k = 0; k < S; ++k)
                    for (int l = 0; l < S; ++l)
                        w[i + k][j + l] = 1;
            }
        }
    for (int i = 0; i < n; ++i)
        for (int j = 0; j < m; ++j)
            if (w[i][j] != (pic[i][j] == 'B')) {
            	return 0;
            }
    return 1;
}

class Painting {
public:
    int largestBrush(vector <string> pic) {
        int head = 1, tail = 100;
        while (head < tail - 1) {
            int mid = (head + tail) >> 1;
            if (check(pic, mid)) head = mid;
            else tail = mid;
        }
        //cout << check(pic, 4) << endl;
        return head;
    }
};
