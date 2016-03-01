#include <iostream>
#include <cstdio>
#include <cstring>
#include <vector>
#include <queue>
#include <map>
#include <algorithm>
using namespace std;

int C[4] = {0, -1, 0, 1};
int D[4] = {1, 0, -1, 0};

class SequenceOfCommands {
public:
    string whatHappens(vector <string> cd) {
        string S;
        for (int i = 0; i < cd.size(); ++i)
            S += cd[i];
        S = S + S + S + S;
        int x = 0, y = 0, d = 0;
        for (int i = 0; i < S.size(); ++i) {
            if (S[i] == 'S') {
                x += C[d];
                y += D[d];
            }
            else if (S[i] == 'L') {
                d = (d + 3) % 4;
            }
            else if (S[i] == 'R') {
                d = (d + 1) % 4;
            }
        }
        if (x != 0 || y != 0) return "unbounded";
        else return "bounded";
    }
};
