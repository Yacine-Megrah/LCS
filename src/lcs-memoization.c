#include <stdio.h>
#include <string.h>

int lcs_memo(char *X, int m, char *Y, int n, int memo[m+1][n+1]) {
    if (memo[m][n] != -1)
        return memo[m][n];
    if (m == 0 || n == 0)
        return memo[m][n] = 0;
    if (X[m-1] == Y[n-1])
        return memo[m][n] = 1 + lcs_memo(X, m-1, Y, n-1, memo);
    else
        return memo[m][n] = (lcs_memo(X, m, Y, n-1, memo) > lcs_memo(X, m-1, Y, n, memo)) ? lcs_memo(X, m, Y, n-1, memo) : lcs_memo(X, m-1, Y, n, memo);
}

int main() {
    char X[] = "AGGT AB";
    char Y[] = "GXT XAY B";
    int m = strlen(X);
    int n = strlen(Y);
    int memo[m+1][n+1];
    memset(memo, -1, sizeof(memo));
    printf("Length of LCS is %d\n", lcs_memo(X, m, Y, n, memo));
    return 0;
}
