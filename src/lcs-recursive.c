#include <stdio.h>
#include <string.h>

int lcs_recursive(char *X, int m, char *Y, int n) {
    if (m == 0 || n == 0)
        return 0;
    if (X[m-1] == Y[n-1])
        return 1 + lcs_recursive(X, m-1, Y, n-1);
    else
        return (lcs_recursive(X, m, Y, n-1) > lcs_recursive(X, m-1, Y, n)) ? lcs_recursive(X, m, Y, n-1) : lcs_recursive(X, m-1, Y, n);
}

int main() {
    char X[] = "AGGT AB";
    char Y[] = "GXT XAY B";
    int m = strlen(X);
    int n = strlen(Y);
    printf("Length of LCS is %d\n", lcs_recursive(X, m, Y, n));
    return 0;
}
