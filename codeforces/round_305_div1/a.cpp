#include <iostream>
#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;

typedef long long LL;

int m;

const int N = 1e6 + 5;

pair<LL, LL> gett(int fir, int end, int x, int y) {
    static int bo[N];
    memset(bo, 0, sizeof(bo));
    pair<LL, LL> ans = make_pair(0, 0);
    while (1) {
        if (fir == end) {
            break;
        }
        ++ans.first;
        if (bo[fir])
            return make_pair(-1, -1);
        bo[fir] = 1;
        fir = ((LL)fir * x + y) % m;
    }
    memset(bo, 0, sizeof(bo));
    do {
        fir = ((LL)fir * x + y) % m;
        ++ans.second;
        if (fir == end) {
            break;
        }
        if (bo[fir]) {
            ans.second = 0;
            break;
        }
        bo[fir] = 1;
        
    } while (1);
    return ans;
}

int main() {
    pair<LL, LL> ans = make_pair(-2, 0);
    scanf("%d", &m);
    int flag = 0;
    for (int i = 0; i < 2; ++i) {
        if (flag) continue;
        int fir, end;
        scanf("%d%d", &fir, &end);
        int x, y;
        scanf("%d%d", &x, &y);
        pair<LL, LL> tmp = gett(fir, end, x, y);
        if (tmp.first == -1) {
            cout << -1 << endl;
            flag = 1;
            continue;
        }
        if (ans.first == -2) ans = tmp;
        else {
            for (int t = 1; t <= 1000000; ++t) {
                if (tmp.second != 0 && ans.first > tmp.first) {
                    tmp.first += (ans.first - tmp.first) / tmp.second * tmp.second;
                }
                if (ans.first == tmp.first) break;
                ans.first += ans.second;
            }
            if (ans.first != tmp.first) {
                ans.first = -1;
            }
        } 
        
    }
    if (flag) return 0;
    cout << ans.first << endl;
    return 0;
}
