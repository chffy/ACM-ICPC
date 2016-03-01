#include <iostream>
#include <cstdio>
#include <cstring>
#include <vector>
#include <queue>
#include <map>
#include <algorithm>
using namespace std;

map<string, int> keymap;
vector<string> key[100];
int bo[100];

vector<string> splite_string(string S) {
    vector<string> res;
    for (int i = 0; i < S.size(); ++i) {
        if (S[i] == ' ') continue;
        int j = i;
        while (j + 1 < S.size() && isalpha(S[j + 1]))
            ++j;
        res.push_back(S.substr(i, j - i + 1));
        i = j;
    }
    return res;
}

class InternetSecurity {
public:
    vector <string> determineWebsite(vector <string> address,
                                     vector <string> keyword,
                                     vector <string> dangerous,
                                     int threshold) {
        for (int i = 0; i < dangerous.size(); ++i) {
            keymap[dangerous[i]] = 1;
        }
        for (int i = 0; i < address.size(); ++i)
            key[i] = splite_string(keyword[i]);
        vector<int> ver;
        while (1) {
            int flag = 0;
            for (int i = 0; i < address.size(); ++i) {
                int num = 0;
                if (bo[i]) continue;
                for (int j = 0; j < key[i].size(); ++j)
                    if (keymap[key[i][j]]) ++num;
                if (num >= threshold) {
                    flag = 1;
                    bo[i] = 1;
                    ver.push_back(i);
                    for (int j = 0; j < key[i].size(); ++j)
                        keymap[key[i][j]] = 1;
                }
            }
            if (flag == 0) break;
        }
        sort(ver.begin(), ver.end());
        vector<string> ans;
        for (int i = 0; i < ver.size(); ++i)
            ans.push_back(address[ver[i]]);
        return ans;
    }
};
