#define _GNU_SOURCE
#include <stdio.h>
#include <string.h>
#include <time.h>

double get_time(clock_t start, clock_t end){
    return (double)(end - start)/CLOCKS_PER_SEC;
}

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

int lcs_memo(char *X, int m, char *Y, int n) {
    int matrix[m+1][n+1];
    
    // Initialize first row and column with 0
    for(int i = 0; i <= m; i++) {
        matrix[i][0] = 0;
    }
    for(int j = 0; j <= n; j++) {
        matrix[0][j] = 0;
    }
    
    // Fill the matrix
    for(int i = 1; i <= m; i++) {
        for(int j = 1; j <= n; j++) {
            if(X[i-1] == Y[j-1]) {
                matrix[i][j] = matrix[i-1][j-1] + 1;
            } else {
                matrix[i][j] = (matrix[i-1][j] > matrix[i][j-1]) ? 
                               matrix[i-1][j] : matrix[i][j-1];
            }
        }
    }
    
    return matrix[m][n];
}

int lcs_dynamic_space_optimized(char *X, int m, char *Y, int n){
    // Determine the smaller dimension size
    if (m < n) {
        // If X is smaller, we swap X and Y, and m and n
        char *tempStr = X; X = Y; Y = tempStr;
        int temp = m; m = n; n = temp;
    }

    // Initialize a single array of size min(m, n) + 1
    int dp[n+1];
    for (int j = 0; j <= n; j++) {
        dp[j] = 0;
    }

    // Fill the array with only the essential information
    for (int i = 1; i <= m; i++) {
        int prev = 0;  // This keeps track of dp[j-1] from the previous row
        for (int j = 1; j <= n; j++) {
            int temp = dp[j];
            if (X[i - 1] == Y[j - 1]) {
                dp[j] = prev + 1;
            } else {
                dp[j] = (dp[j] > dp[j - 1]) ? dp[j] : dp[j - 1];
            }
            prev = temp;
        }
    }

    // The last element in dp contains the LCS length
    return dp[n];
}

int main() {

    const char * strings[] = {
/*10 */ {"WWVBUJOFST","BUMJAZGBVD"},
/*20 */ {"ZOYMFAPTUURZ ASOKEGDHF","HZDGEQHDPKXPQKQOFTBD"},
/*40 */ {"LJMYKYLXICGLBD GOZGYQSDZLG XOMRRZASUWYGZAINY","DJIKDEZYDNWNJIB FRPGJEVJWIBJGWVCQ VMVTQQ"},
/*80 */ {"PMOOFU  FQPKLXETDOVTXVMVVXSJYDKFWAPKDDQBFTXTVSXZLMTZDCKIOAZPIQNGWJG IBVGKPZAI FO","ZWCJUGABHTPBEUJMDLSBKBTGIQSRMBJUERWDDIMVJQVKNJQ FNBQEJRSIDNYCPRZSNKEAMZZFNFHNSVMWD"},
/*160*/ {"LI ZCQPLYGILTJJQMVWQERVMHEOKJWBKDSJKCMDGJDLUAMZILAKOR NABMNNMNGJOH GQSRXULOATMNOLNZOLEQTWYTPPLXMKKNYMXCHHHAPYAWILWDCYCNMTW BCWXURVCJOTMRLFNGRXFDXEEMGFROKCERYL","QRDDZWUVZSITMRXQDDMONDLGBDXPTFRHYTH GFGLHDWS AGWGAFFVTDPOYIOHTVNRHRWFGLGSOWPLHVVA ACCAYGRSWOWYBDUBVAU SPYTKWSFDS HMWVMSFHSUJHEULYTPEUQ XFCLQJDTIDKVLJDBW RZYTGZ"}
    };

    clock_t start_time, end_time;
    double elapsed_time;
    FILE *results_f;

    results_f = fopen("results.tsv", "w+");
    fprintf(results_f, "n,m\tlcs_recursive\tlcs_memoization\tlcs_dynamic_so\n");
    fflush(results_f);

    char X[] = "AGGT AB";
    char Y[] = "GXT XAY B";
    int m = strlen(X);
    int n = strlen(Y);


    printf("Length of LCS (recursive) is %d\n", lcs_recursive(X, m, Y, n));

    printf("Length of LCS (memo) is %d\n", lcs_memo(X, m, Y, n));

    printf("Length of LCS (so) is %d\n", lcs_dynamic_space_optimized(X, m, Y, n));

    return 0;
}
