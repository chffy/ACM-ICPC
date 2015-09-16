#include <iostream>
#include <cstdio>
#include <algorithm>
#include <cmath>
#include <cstring>
#include <string>
#include <queue>
#include <vector>
#include <bitset>
#include <cctype>
#include <map>
using namespace std;
typedef long long LL;
const int N = 80005;
char str[N];
int n;

struct SAM {
    int parent[N], f[N][26], rmax[N], mark[N];
    int tot, last, root;

    int newnode(int len) {
        int x = ++tot;
        memset(f[x], -1, sizeof(f[x]));
        rmax[x] = len;
        parent[x] = -1;
        mark[x] = 1 << 30;
        return x;
    }
    
    void clear() {
        tot = 0;
        root = last = 1;
        newnode(0);
    }

    SAM() {clear(); }

    void insert(int ch, int i) {
        int np = newnode(rmax[last] + 1);
        mark[np] = i;
        int vp = last;
        last = np;
        while (vp != -1 && f[vp][ch] == -1) {
            f[vp][ch] = np;
            vp = parent[vp];
        }
        if (vp == -1) {
            parent[np] = root;
            return ;
        }
        int q = f[vp][ch];
        if (rmax[vp] + 1 == rmax[q]) {
            parent[np] = q;
            return ;
        }
        int nq = newnode(rmax[vp] + 1);
        memcpy(f[nq], f[q], sizeof(f[nq]));
        parent[nq] = parent[q];
        parent[q] = parent[np] = nq;
        while (vp != -1 && f[vp][ch] == q) {
            f[vp][ch] = nq;
            vp = parent[vp];
        }
    }
}sa;

void topsort() {
    static int sum[80005], top[80005];
    for (int i = 0; i <= sa.tot; ++i) sum[i] = 0;
    for (int i = 1; i <= sa.tot; ++i)
        sum[sa.rmax[i]]++;
    for (int i = 1; i <= sa.tot; ++i)
        sum[i] += sum[i - 1];
    for (int i = 1; i <= sa.tot; ++i)
        top[sum[sa.rmax[i]]--] = i;
    for (int i = sa.tot; i > 0; --i) {
        int x = top[i];
        if (x != sa.root)
            sa.mark[sa.parent[i]] = min(sa.mark[i], sa.mark[sa.parent[i]]);
    }
}

int MinR(char *str, int flag) {
    int n = strlen(str);
    sa.clear();
    for (int i = 0; i < n; ++i)
        sa.insert(str[i] - 'a', i * flag);
    for (int i = 0; i + 1 < n; ++i) {
        int s = (i + n);
        sa.insert(str[i] - 'a', s * flag);
    }
    topsort();
    int x = sa.root;
    for (int i = 1; i <= n; ++i) {
        for (int j = 25; j >= 0; --j)
            if (sa.f[x][j] != -1) {
                x = sa.f[x][j];
                break;
            }
    }
    //puts("!!!");
    //puts(str);
    //cout << sa.mark[x] * flag << endl;
    return sa.mark[x] * flag - n + 1;
}
char t[N];

void work() {
    scanf("%d%s" , &n , str);
    n = strlen(str);
    int x = MinR(str, 1);
    strcpy(t , str);
    rotate(t , t + x , t + n);
    reverse(str , str + n);
    int y = MinR(str, -1);
    rotate(str , str + y , str + n);
    int z = strcmp(t , str);
    //puts(t);
    y = n - y - 1;
    if (z != 0) {
        if (z > 0)
            printf("%d 0\n" , x + 1);
        else
            printf("%d 1\n" , y + 1);
    } else {
        if (x != y) {
            if (x < y)
                printf("%d 0\n" , x + 1);
            else printf("%d 1\n", y + 1);
        }
        else printf("%d 0\n", x + 1);
    }
}

int main() {
    int T;
    scanf("%d" , &T);
    while (T --)
        work();
    return 0;
}
