void getfail(char *str, int n) {
    memset(fail, -1, sizeof(int) * n);
    for (int i = 1; i < n; ++i) {
        int j = fail[i - 1];
        while (j != -1 && str[j + 1] != str[i]) j = fail[j];
        if (str[j + 1] == str[i]) fail[i] = j + 1;
    }
}

void kmp(char *str, char *S, int a[]) {
    int n = strlen(str), m = strlen(S);
    getfail(str, n);
    for (int i = 0, j = -1; i < m; ++i) {
        while (j != -1 && str[j + 1] != S[i]) j = fail[j];
        if (str[j + 1] == S[i]) ++j;
        a[i] = j + 1;
        if (j == n - 1) j = fail[j];
    }
}
