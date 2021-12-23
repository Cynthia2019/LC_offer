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