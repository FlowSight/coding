/// Severity: Sev0..sev0..sev0..sev0..
// Date: 23May26
// LC: 1411
// Where I failed: i thought dp[i][j] = topcnt*leftcnt. BUT top's color affect left's color
// hence    the state was wrong.
// Pattern:
//     The grid is narrow (small number of columns) but long (many rows)
//      Individual cell states explode but row patterns are limited and classifiable
//      Transitions depend only on which "type" the previous row was, not its exact coloring
// Notes: lee's optimization




class Solution {
public:
    int numOfWays(int n) {
        long mod = 1e9+7;
        long a = 6, b = 6;
        for(int i = 2; i <= n; i++){
            long na = (2*a + 2*b) % mod;
            long nb = (2*a + 3*b) % mod;
            a = na;
            b = nb;
        }
        return (a + b) % mod;
    }
};

// You have a grid of size n x 3 and you want to paint each cell of the grid with exactly one of the three colors: Red, Yellow, or Green while making sure that no two adjacent cells have the same color (i.e., no two cells that share vertical or horizontal sides have the same color).