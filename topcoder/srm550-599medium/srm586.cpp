#include <iostream>
#include <cstdio>
#include <cstring>
#include <algorithm>
#include <vector>
using namespace std;

vector<pair<int, int> > years[200];

void get_years(string S, vector<pair<int, int> > &years) {
    int p = 0;
    int first = -1, y;
    while (p < S.size()) {
        int x = 0;
        while (p < S.size() && isdigit(S[p])) {
            x = x * 10 + S[p] - '0';
            ++p;
        }
        if (first == -1) {
            first = x;
        }
        else years.push_back(make_pair(y - first, x - 1 - first));
        y = x;
        ++p;
    }
}

pair<int, int> f[200][200];

void up1(int i, int j, int L, int R) {
    f[i][j].first = max(f[i][j].first, L);
    f[i][j].second = min(f[i][j].second, R);
}

void updata(int x, int n, int y, int m) {
    int L = years[x][n].first - years[y][m].second;
    int R = years[x][n].second - years[y][m].first;
    up1(x, y, L, R);
}

class History {
public:
    string verifyClaims(vector <string> dynasties, vector <string> battles, vector <string> queries) {
        int n = dynasties.size();
        for (int i = 0; i < n; ++i)
            for (int j = 0; j < n; ++j)
                if (i == j) f[i][j] = make_pair(0, 0);
                else f[i][j] = make_pair(-200000, 200000);
        
        for (int i = 0; i < n; ++i) {
            years[i].clear();
            get_years(dynasties[i], years[i]);
        }
        {
            string S = "";
            for (int i = 0; i < battles.size(); ++i) S += battles[i];
            int p = 0;
            while (p < S.size()) {
                int X = S[p++] - 'A';
                int N = 0;
                while (isdigit(S[p])) {
                    N = N * 10 + S[p] - '0';
                    ++p;
                }
                ++p;
                int Y = S[p++] - 'A';
                int M = 0;
                while (p < S.size() && isdigit(S[p])) {
                    M = M * 10 + S[p] - '0';
                    ++p;
                }
                updata(X, N, Y, M);
                updata(Y, M, X, N);
                ++p;
            }
        }
        string ans = "";
        for (int k = 0; k < n; ++k)
            for (int i = 0; i < n; ++i)
                for (int j = 0; j < n; ++j)
                    up1(i, j, f[i][k].first + f[k][j].first, f[i][k].second + f[k][j].second);
        for (int i = 0; i < queries.size(); ++i) {
            int p = 0;
            string S = queries[i];
            int X = S[p++] - 'A';
            int N = 0;
            while (isdigit(S[p])) {
                N = N * 10 + S[p] - '0';
                ++p;
            }
            ++p;
            int Y = S[p++] - 'A';
            int M = 0;
            while (p < S.size()) {
                M = M * 10 + S[p] - '0';
                ++p;
            }
            if (max(years[X][N].first, years[Y][M].first + f[X][Y].first) <=
                min(years[X][N].second, years[Y][M].second + f[X][Y].second))
                ans += 'Y';
            else ans += 'N';
        }
        return ans;
    }
};
