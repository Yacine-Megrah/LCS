#include <stdio.h>
#include <string.h>

int lcs_dynamic(char *X, int m, char *Y, int n) {
    int lcs[m+1][n+1];

    for (int i = 0; i <= m; i++) {
        for (int j = 0; j <= n; j++) {
            if (i == 0 || j == 0)
                lcs[i][j] = 0;
            else if (X[i-1] == Y[j-1])
                lcs[i][j] = lcs[i-1][j-1] + 1;
            else
                lcs[i][j] = (lcs[i-1][j] > lcs[i][j-1]) ? lcs[i-1][j] : lcs[i][j-1];
        }
    }

    return lcs[m][n];
}

int main() {
    char X[] = "AGGT AB";
    char Y[] = "GXT XAY B";
    int m = strlen(X);
    int n = strlen(Y);
    printf("Length of LCS is %d\n", lcs_dynamic(X, m, Y, n));
    return 0;
}
