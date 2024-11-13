#include <stdio.h>
#include <string.h>

int max(int x, int y){
    return (x > y) ? x : y;
}

int lcs_recursive(char *X, int m, char *Y, int n) {
    if (m == 0 || n == 0)
        return 0;
    if (X[m-1] == Y[n-1])
        return 1 + lcs_recursive(X, m-1, Y, n-1);
    else
        return max(lcs_recursive(X, m, Y, n-1), lcs_recursive(X, m-1, Y, n));
}

int lcs_memo(char *X, int m, char *Y, int n, int memo[m+1][n+1]) {
    if (memo[m][n] != -1)
        return memo[m][n];
    if (m == 0 || n == 0)
        return memo[m][n] = 0;
    if (X[m-1] == Y[n-1])
        return memo[m][n] = 1 + lcs_memo(X, m-1, Y, n-1, memo);
    else
        return memo[m][n] = max(lcs_memo(X, m, Y, n-1, memo), lcs_memo(X, m-1, Y, n, memo));
}

int lcs_dynamic_space_optimized(char *X, int m, char *Y, int n) {
    int prev[n+1], curr[n+1];
    memset(prev, 0, sizeof(prev));

    for (int i = 1; i <= m; i++) {
        for (int j = 1; j <= n; j++) {
            if (X[i-1] == Y[j-1])
                curr[j] = prev[j-1] + 1;
            else
                curr[j] = max(prev[j], curr[j-1]);
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

    printf("Length of LCS is %d\n", lcs_recursive(X, m, Y, n));

    int memo[m+1][n+1];
    memset(memo, -1, sizeof(memo));
    printf("Length of LCS is %d\n", lcs_memo(X, m, Y, n, memo));

    printf("Length of LCS is %d\n", lcs_dynamic_space_optimized(X, m, Y, n));

    return 0;
}
