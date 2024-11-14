#define _GNU_SOURCE
#include <stdio.h>
#include <string.h>
#include <time.h>

double get_time(char *X, int m, char *Y, int n, int (*func)(char*,int,char*,int)){
    clock_t end, start;
    double total_time = 0;
    for(int i = 0; i < 4 ; i++){
        start = clock();
        func(X, m, Y, n);
        end = clock();
        total_time += (double)(end-start)/CLOCKS_PER_SEC;
    }
    return total_time/4;
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

    char *strings[5][2] = {
/*4*/   {"ABFC","ABCF"},
/*10 */ {"JTDLFOEZVJ","ALZITNAKOQ"},
/*16 */ {"WTU XCNWLEWFHHDB","KEAJNHFUTQWTJGGOXI"},
/*22 */ {"VQIQGHLSYXUSISSKNM QAPZMEMLYHJ T","XCOJTVRKGHVO VMTFNMVEEGQLA EXQGJ"},
//*40 */ {"GVIQTOASIIIDUHPRZSBPCUFGVDLWYY QNCEKQBDFBQMM","PRMSBQNJIJHWGKUSGPIOSUFLHNYCFXEDYPKNVXUY"},
//*50 */ {"ABMVQBPGJTTYBOEQGCLAOBCMAWDPUJPQETTSJBJUBKXUACSWQFLFIYQOCNIT","RYXCVWSTDSJEJJ VAQMNKOSUOSTPLQRD YQFGPIY GUG FRPPVHNSBVOWLYXYMXP"}
    };

    double times[5][4];
    FILE *results_f = fopen("results.tsv", "w+");
    fprintf(results_f, "n,m\tlcs_recursive\tlcs_memoization\tlcs_dynamic_so\n");
    fflush(results_f);

    for(int i=0; i < 5; i++){
        times[i][0] = strlen(strings[i][0]);
        times[i][1] = get_time(strings[i][0], strlen(strings[i][0]), strings[i][1], strlen(strings[i][1]), lcs_recursive);
        times[i][2] = get_time(strings[i][0], strlen(strings[i][0]), strings[i][1], strlen(strings[i][1]), lcs_memo);
        times[i][3] = get_time(strings[i][0], strlen(strings[i][0]), strings[i][1], strlen(strings[i][1]), lcs_dynamic_space_optimized);
        fprintf(results_f, "%d\t%.3f\t%.3f\t%.3f\n", (int)times[i][0], times[i][1], times[i][2], times[i][3]);
    }
 
    fclose(results_f);

    return 0;
}
    // char X[] = "AGGT AB";
    // char Y[] = "GXT XAY B";
    // int m = strlen(X);
    // int n = strlen(Y);

    // printf("Length of LCS (recursive) is %d\n", lcs_recursive(X, m, Y, n));

    // printf("Length of LCS (memo) is %d\n", lcs_memo(X, m, Y, n));

    // printf("Length of LCS (so) is %d\n", lcs_dynamic_space_optimized(X, m, Y, n));
