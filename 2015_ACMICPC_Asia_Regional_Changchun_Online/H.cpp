#include <iostream>
#include <cstdio>
#include <cstring>
#include <vector>
#include <algorithm>
using namespace std;

const int N = 1e3 + 5;

char str[1005][1005];
int a[N];

void work(int l, int r) {
    if (l == r) return ;
    int mid = l + 1;
    while (mid <= r && a[mid] < a[l]) ++mid;
    if (mid > l + 1) {
        memcpy(str[a[l + 1]], str[a[l]], sizeof(str[0]));
        int len = strlen(str[a[l]]);
        str[a[l + 1]][len] = 'E';
        str[a[l + 1]][++len] = 0;
        work(l + 1, mid - 1);
    }
    if (mid <= r) {
        memcpy(str[a[mid]], str[a[l]], sizeof(str[0]));
        int len = strlen(str[a[l]]);
        str[a[mid]][len] = 'W';
        str[a[mid]][++len] = 0;
        work(mid, r);
    }
}

int main() {
    int T;
    scanf("%d", &T);
    while (T--) {
        int n;
        scanf("%d", &n);
        for (int i = 1; i <= n; ++i)
            scanf("%d", &a[i]);
        str[a[1]][0] = 0;
        work(1, n);
        int q;
        scanf("%d", &q);
        while (q--) {
            int x;
            scanf("%d", &x);
            puts(str[x]);
        }
        
    }
    return 0;
}
