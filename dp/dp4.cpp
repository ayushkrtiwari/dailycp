// https://leetcode.com/problems/dungeon-game/description/

// Recursive DP

// Just that you need to cover all the paths, hence use DP for repeating recursion. 
// While going through path, you just have 2 directions, right and down 
// thus for each cell store the min of both recursions. 
// While returning a cell value invert its value since for each -ve you want your health +ve, 
// and for each +ve you want your cell max(1, -ve). 
// The +ve and -ve here aren't dungeon values but dp values, 
// which are evaluated as min(minHP(rightcell), minHP(downcell)) for each cell.
// Returning for each cell is done as : -1 * dungeon(cell) + minHP(right, down)
// Just the tricky part is the last destination cell, 
// where the return value isn't the same but max(1, -1 * dungeon(cell)) 
// obviously 1 if dungeon(cell) > 0 and max(1, 1 - dungeon(cell)) if dungeon(cell) < 0

class Solution {
public:
    int minHP(vector<vector<int>> &dp, vector<vector<int>> &dungeon, int r, int c, int n, int m)
    {
        if(r == n or c == m) return inf;
        if(r == n - 1 and c == m - 1) return dp[r][c] = max(1, dungeon[n - 1][m - 1] > 0 ? -1 * dungeon[n - 1][m - 1] : 1 - dungeon[n - 1][m - 1]);
        if(r == n - 1) return dp[r][c] = max(1, min(dp[r][c], -1 * dungeon[r][c] + minHP(dp, dungeon, r, c + 1, n, m)));
        if(c == m - 1) return dp[r][c] = max(1, min(dp[r][c], -1 * dungeon[r][c] + minHP(dp, dungeon, r + 1, c, n, m)));
        if(dp[r][c] != inf) return dp[r][c];
        int down = (r < n - 1) ? minHP(dp, dungeon, r + 1, c, n, m) : 0;
        int right = (c < m - 1) ? minHP(dp, dungeon, r, c + 1, n, m) : 0;
        return dp[r][c] = max(1, -1 * dungeon[r][c] + min(down, right));
    }
    int calculateMinimumHP(vector<vector<int>>& dungeon) {
        int row = dungeon.size();
        int col = dungeon[0].size();
        vector<vector<int>> dp(row, vector<int>(col, inf));
        return minHP(dp, dungeon, 0, 0, row, col);
    }
};