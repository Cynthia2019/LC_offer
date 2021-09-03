//455. Assign Cookies
class Solution {
public:
    int findContentChildren(vector<int>& g, vector<int>& s) {
        sort(g.begin(), g.end());
        sort(s.begin(), s.end()); 
        int ans = 0; 
        int child = 0;
        for(int i = g.size(); i >= 0; i--){
            if(child == g.size()) break;
            if(g[child] <= s[i]) {
                ans++;
                child++;
            }
        }
        return ans;
    }
};

//55. Jump Game
class Solution {
public:
    bool canJump(vector<int>& nums) {
        int left = 0;
        for(int i = 0; i < nums.size() - 1; i++){
            left = max(left - 1, nums[i]); 
            if(left <= 0) return false; 
        }
        return true;
    }
};