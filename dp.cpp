//309 Best Time to Buy and Sell Stock with Cooldown
class Solution {
public:
    int maxProfit(vector<int>& prices) {
        vector<vector<int>> dp(prices.size(), vector<int>(4)); 
        dp[0][0] = -prices[0]; 
        dp[0][1] = 0; 
        dp[0][2] = 0; 
        dp[0][3] = 0; 
        for(int i = 1; i < prices.size(); i++){
            dp[i][0] = max(dp[i-1][0], max(dp[i-1][1], dp[i-1][3]) - prices[i]); 
            dp[i][1] = max(dp[i-1][1], dp[i-1][3]); 
            dp[i][2] = dp[i-1][0] + prices[i]; 
            dp[i][3] = dp[i-1][2]; 
        }
        return max(dp[prices.size() - 1][1], max(dp[prices.size() - 1][2], dp[prices.size() - 1][3])); 
    }
};

//188 Best Time to Buy and Sell Stock IV
class Solution {
public:
    int maxProfit(int k, vector<int>& prices) {
        if(!prices.size()) return 0; 
        vector<vector<int>> dp(prices.size(), vector<int>(2*k+1));
        for(int j = 0; j < 2*k+1; j++){
            if(j % 2 != 0){
                dp[0][j] = -prices[0]; 
            }
            else {
                dp[0][j] = 0; 
            }
        }
        for(int i = 1; i < prices.size(); i++){
            for(int j = 0; j < 2*k+1; j++){
                if(j == 0){
                    dp[i][j] = dp[i-1][j];
                }
                else if (j % 2 != 0){
                    dp[i][j] = max(dp[i-1][j], dp[i-1][j-1] - prices[i]); 
                }
                else {
                    dp[i][j] = max(dp[i-1][j], dp[i-1][j-1] + prices[i]); 
                }
            }
        }
        return dp[prices.size() - 1][2*k];
    }
};


//416. Partition Equal Subset Sum
//01背包问题转换
class Solution {
public:
    bool canPartition(vector<int>& nums) {
        int sum = 0; 
        for(int i : nums) sum += i; 
        if(sum % 2 != 0) return false; 
        int weight = sum / 2; 
        vector<int> dp(weight+1, 0);
        for(int i = 0; i < nums.size(); i++){
            for(int j = weight; j >= nums[i]; j--){
                dp[j] = max(dp[j], dp[j - nums[i]] + nums[i]); 
            }
        }
        return dp[weight] == weight;  
    }
};


//5. Longest Palindromic Substring
//use dp to check for palindromic substring
class Solution {
public:
    string longestPalindrome(string s) {
        vector<vector<bool>> dp(s.size(), vector<bool>(s.size(), true)); 
        string ans; 
        for(int i = s.size() - 1; i >= 0; i--){
            for(int j = i; j < s.size(); j++){
                if(i != j) {
                    dp[i][j] = dp[i+1][j-1] && s[i] == s[j]; 
                }
                if(dp[i][j] && j - i + 1 > ans.size()){
                    ans = s.substr(i, j - i + 1); 
                }
            }
        }
        return ans; 
    }
};

//152. Maximum Product Subarray
//需要分正负情况讨论，用dpMin记录负product的情况
class Solution {
public:
    int maxProduct(vector<int>& nums) {
        vector<int> dpMax(nums.size(), 0); 
        vector<int> dpMin(nums.size(), 0); 
        dpMax[0] = nums[0]; 
        dpMin[0] = nums[0]; 
        for(int i = 1; i < nums.size(); i++){
            dpMax[i] = max(max(dpMax[i-1] * nums[i], dpMin[i-1] * nums[i]),nums[i]);
            dpMin[i] = min(min(dpMax[i-1] * nums[i], dpMin[i-1] * nums[i]),nums[i]); 
        }
        int ans = INT_MIN; 
        for(int i : dpMax) ans = max(ans, i); 
        return ans;
    }
};
//64. min path sum 
class Solution {

public:
    int minPathSum(vector<vector<int>>& grid) {
        int m = grid.size(); 
        int n = grid[0].size(); 
        vector<vector<int>> dp(m, vector<int>(n, 0)); 
        //dp[i][j] = min(dp[i-1][j], dp[i+1][j]) + grid[i][j], 
        dp[0][0] = grid[0][0]; 
        for(int i = 1; i < m; i++){
            dp[i][0] = dp[i-1][0] + grid[i][0];
        }
        for(int j = 1; j < n; j++){
            dp[0][j] = dp[0][j-1] + grid[0][j];
        }
        for(int i = 1; i < m; i++){
            for(int j = 1; j < n; j++) {
                dp[i][j] = min(dp[i-1][j], dp[i][j-1]) + grid[i][j]; 
            }
        }
        return dp[m-1][n-1];
    }
};