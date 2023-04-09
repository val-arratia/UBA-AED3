#include <stdio.h>
#include <vector>
#include <cstdlib>
using namespace std;

vector<vector<vector<int>>> todos;

int magic_squares(int m, vector<vector<int>> &s, int i, int j, vector<int> &c, vector<int> &p, int h) {
    int n = s.size();
    int r = 0; // Solutions counter.
    if (j == n) return magic_squares(m, s, i + 1, 0, c, p, h); // Continue on next row.
    if (i == n){
        todos.push_back(s);
        
        return 1; // Square is filled (and valid because of the branch and bound checks).

    }
    
    
    for (int k = 1; k <= n * n; k++) {
        
        // Check if number is available.
        if (c[k - 1] == 1) continue;

        // Check if row sum exceeds the magic number.
        if (p[i] + k > m) continue;

        // Check if row sum is exactly the magic number when row is complete.
        if (j == n - 1 && p[i] + k != m) continue;

        // Check if col sum exceeds the magic number.
        if (p[n + j] + k > m) continue;

        // Check if col sum is exactly the magic number when col is complete.
        if (i == n - 1 && p[n + j] + k != m) continue;

        bool is_diagonal1 = i == j;
        bool is_diagonal2 = i == n - j - 1;

        // Check if diagonal1 sum exceeds the magic number.
        if (is_diagonal1 && p[2 * n] + k > m) continue;

        // Check if diagonal1 sum is exactly the magic number when it's complete.
        if (is_diagonal1 && i == n - 1 && p[2 * n] + k != m) continue;

        // Check if diagonal2 sum exceeds the magic number.
        if (is_diagonal2 && p[2 * n + 1] + k > m) continue;

        // Check if diagonal2 sum is exactly the magic number when it's complete.
        if (is_diagonal2 && i == n - 1 && p[2 * n + 1] + k != m) continue;

        s[i][j] = k;
        c[k - 1] = 1;
        p[i] += k;
        p[n + j] += k;
        if (is_diagonal1) p[2 * n] += k;
        if (is_diagonal2) p[2 * n + 1] += k;

        r += magic_squares(m, s, i, j + 1, c, p,h);
        if(r==h){
            return r;  
            for(int w=0;w<s.size();w++){
                for(int e=0;e<s[w].size();e++){
                    printf(", %d",s[w][e]);
                }
            printf(";\n");
            }
        }
        

        // Backtrack.
        c[k - 1] = 0;
        p[i] -= k;
        p[n + j] -= k;
        if (is_diagonal1) p[2 * n] -= k;
        if (is_diagonal2) p[2 * n + 1] -= k;
    }
    return r;
}

int main(int argc, char *argv[]) {
    // Parse input.
    int n = 3;

    // Initialize arguments.
    int m = (n * n * n + n) / 2; // magic number
    vector<vector<int>> s(n, vector<int>(n)); // magic square
    vector<int> c(n * n); // candidates
    vector<int> p(2 * n + 2); // partial row, col and diagonal sums
    // row sums: p[0...n-1]
    // col sums: p[n...2n-1]
    // diagonal sums: p[2n], p[2n+1]

    int r = magic_squares(m, s, 0, 0, c, p,3);
    printf("%dx%d magic squares (optimized): %d\n", n, n, r);
    for(int k=0;k<todos.size();k++){
        for(int i=0;i<todos[k].size();i++){
            for(int j=0;j<todos[k][i].size();j++){
                printf(", %d",todos[k][i][j]);
            }
            printf(";\n");
        }
        printf(";;\n");
        printf(";\n");
    }
    return 0;
}