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

//406. Queue Reconstruction by Height
//greedy: first arrange by height, then each person is guaranteed to have k people taller to be in front of. 
//trick: use linked list (list) to reduce insertion time 
class Solution {
private: 
    static bool cmp(vector<int>& a, vector<int>& b){
        if(a[0] == b[0]) return a[1] < b[1];
        return a[0] > b[0]; 
    }
public:
    vector<vector<int>> reconstructQueue(vector<vector<int>>& people) {
        sort(people.begin(), people.end(), cmp); 
        list<vector<int>> ans; //list底层实现是linkedlist
        for(int i = 0; i < people.size(); i++){
            auto it = ans.begin(); 
            int k = people[i][1];
            while(k--){
                it++; 
            }
            ans.insert(it, people[i]);
        }
        return vector<vector<int>>(ans.begin(), ans.end());
    }
};