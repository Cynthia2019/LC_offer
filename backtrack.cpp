//77. Combinations
class Solution {
private: 
    void backtrack(int n, int k, int stackIndex){
        if(path.size() == k) {
            ans.push_back(path);
            return; 
        }
        for(int i = stackIndex; i <= n-(k-path.size())+1; i++){ //加上了剪枝
            path.push_back(i); 
            backtrack(n, k, i + 1); 
            path.pop_back();
        }
    }
public:
    vector<int> path; 
    vector<vector<int>> ans; 
    vector<vector<int>> combine(int n, int k) {
        backtrack(n, k, 1); 
        return ans;
    }
};

//131. Palindrome Partitioning
class Solution {
private: 
    bool isPalindrome(string s, int start, int end) {
        if(start > end) return false;
        while(start <= end){
            if(s[start] != s[end]) return false; 
            start++;
            end--;
        }
        return true; 
    }
    void backtrack(string s, int startIndex) {
        if(startIndex == s.size()){
            ans.push_back(path);
            return; 
        }
        for(int i = startIndex; i < s.size(); i++){
            if(isPalindrome(s, startIndex, i)) {
                string str(s.begin()+startIndex, s.begin() + i + 1);
                path.push_back(str); 
            } 
            else continue; 
            backtrack(s, i + 1); 
            path.pop_back();
        }
    }
public:
    vector<vector<string>> ans; 
    vector<string> path; 
    vector<vector<string>> partition(string s) {
        backtrack(s, 0);
        return ans; 
    }
};


class Solution {
private: 
    bool isValid(const string& s, int start, int end){
        if(start > end) return false;
        if(s[start] == '0' && start != end) return false; 
        int num = 0; 
        for(int i = start; i <= end; i++){
            if(s[i] > '9' || s[i] < '0') return false; 
            num = num * 10 + (s[i] - '0'); 
            if(num > 255) return false;
        }
        return true;
    }
    void backtrack(string s, int startIndex, int pointNum) {
        if(pointNum == 3) {
            if(isValid(s, startIndex, s.size() - 1)){
                ans.push_back(s);
            }
            return; 
        }
        for(int i = startIndex; i < s.size(); i++){
            if(isValid(s, startIndex, i)){
                s.insert(s.begin() + i + 1, '.');
                pointNum++;
                backtrack(s, i + 2, pointNum);
                pointNum--;
                s.erase(s.begin() + i + 1);
            }
        }

    }
public:
    vector<string> ans;
    vector<string> restoreIpAddresses(string s) {
        backtrack(s, 0, 0);
        return ans; 
    }
};

//78. Subsets 子集问题
class Solution {
private: 
    void backtrack(vector<int>& nums, int startIndex){
        ans.push_back(subset);
        if(startIndex == nums.size()){
            return; 
        }
        for(int i = startIndex; i < nums.size(); i++){
            subset.push_back(nums[i]); 
            backtrack(nums, i + 1); 
            subset.pop_back();
        }
    }
public:
    vector<int> subset; 
    vector<vector<int>> ans; 
    vector<vector<int>> subsets(vector<int>& nums) {
        backtrack(nums, 0); 
        return ans; 
    }
};