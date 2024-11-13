#include <stdio.h>
#include <string.h>

int lcs_dynamic_space_optimized(char *X, int m, char *Y, int n) {
    int prev[n+1], curr[n+1];
    memset(prev, 0, sizeof(prev));

    for (int i = 1; i <= m; i++) {
        for (int j = 1; j <= n; j++) {
            if (X[i-1] == Y[j-1])
                curr[j] = prev[j-1] + 1;
            else
                curr[j] = (prev[j] > curr[j-1]) ? prev[j] : curr[j-1];
        }
        memcpy(prev, curr, sizeof(curr));
    }

    return prev[n];
}

int main() {
    char X[] = "AGGT AB";
    char Y[] = "GXT XAY B";
    int m = strlen(X);
    int n = strlen(Y);
    printf("Length of LCS is %d\n", lcs_dynamic_space_optimized(X, m, Y, n));
    return 0;
}
