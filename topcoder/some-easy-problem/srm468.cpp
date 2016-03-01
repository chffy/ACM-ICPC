#include <iostream>
#include <cstdio>
#include <cstring>
#include <vector>
#include <queue>
#include <map>
#include <algorithm>
#include <set>
using namespace std;

vector<string> part;
vector<string> dict;
int bo[55];

string change(string S, int num) {
	//cout << S << " " << num << endl;
    memset(bo, 0, sizeof(bo));
    for (int i = 0; i < dict.size(); ++i) {
        if (dict[i].size() != S.size()) continue;
        int flag = 1;
        for (int j = 0; j < S.size(); ++j) {
            int mark = -1, d = S[j] - '0' - 1;
            for (int k = 0; k < part[d].size(); ++k)
                if (part[d][k] == dict[i][j]) mark = 1;
            if (mark == -1) {
            	//printf("%d %d %d %c %c\n", i, j, d, part[d][1], dict[i][1]);
                flag = 0;
                break;
            }
        }
        bo[i] = flag;
    }
    for (int i = 0; i < dict.size(); ++i)
        if (bo[i] && (--num == 0)) return dict[i];
    return "error";
}

class T9 {
public:
    string message(vector <string> _part, vector <string> _dict, vector <string> keystr) {
        part = _part;
        dict = _dict;
        sort(dict.begin(), dict.end());
        string S = "";
        for (int i = 0; i < keystr.size(); ++i)
            S += keystr[i];
        string ans = "";
        for (int i = 0; i < S.size(); ++i) {
            if (S[i] == '0') {
                ans = ans + " ";
                continue;
            }
            int j = i;
            while (j + 1 < S.size() && S[j + 1] != '0')
                ++j;
            string dig = "";
            int num = 1;
            for (int k = i; k <= j; ++k)
                if (isdigit(S[k])) {
                    dig = dig + S[k];
                }
                else if (S[k] == '#') ++num;
                else num += 5;
            //if (num == 0) num = 1;
            ans += change(dig, num);
            i = j;
        }
        return ans;
    }
};

