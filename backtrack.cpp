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

//46. Permutations
//difference: 如果用数组记录使用过的element，则每次遍历从头开始判断
//也可以直接在数组上变化排列，可以省空间复杂度，每次把排列好的和没排列好的放到左右两边，处理完后再回溯回来。
class Solution {
private: 
    void backtrack(vector<int>& nums, int startIndex) {
        if(startIndex == nums.size()){
            ans.push_back(nums);
            return;
        }
        for(int i = startIndex; i < nums.size(); i++){
            swap(nums[startIndex], nums[i]);
            backtrack(nums, startIndex + 1); 
            swap(nums[startIndex], nums[i]);
        }
    }
public:
    vector<vector<int>> ans; 
    vector<vector<int>> permute(vector<int>& nums) {
        backtrack(nums, 0);
        return ans; 
    }
};

//332. Reconstruct Itinerary
//难点：1. 反应映射关系(unordered_map + map)
//2. 找出终止条件
//3. 处理潜在的死循环
class Solution {
private: 
    bool backtrack(int ticketNum, vector<string>& result){
        if(result.size() == ticketNum + 1){
            return true; 
        }
        for(pair<const string, int>& target : targets[result[result.size()-1]]){
            if(target.second > 0){
                target.second--;
                result.push_back(target.first);
                if(backtrack(ticketNum, result)) return true; 
                result.pop_back(); 
                target.second++;
            } 
        }
        return false;
    }
public:
    unordered_map<string, map<string, int>> targets;
    vector<string> findItinerary(vector<vector<string>>& tickets) {
        for(const vector<string>& v : tickets){
            targets[v[0]][v[1]]++;
        } 
        vector<string> result;
        result.push_back("JFK");
        backtrack(tickets.size(), result);
        return result;
    }
};

//37. Sudoku Solver
class Solution {
private: 
    bool isValid(int row, int col, int num, const vector<vector<char>>& board){
        //same row
        for(int i = 0; i < 9; i++){
            if(board[row][i] == num) return false;
        }
        //same col
        for(int i = 0; i < 9; i++){
            if(board[i][col] == num) return false;
        }
        //same grid
        int row_start = (row / 3) * 3;
        int col_start = (col / 3) * 3; 
        for(int i = row_start; i < row_start+3; i++){
            for(int j = col_start; j < col_start+3; j++){
                if(board[i][j] == num) return false;
            }
        }
        return true;
    }
    bool backtrack(vector<vector<char>>& board){
        for(int row = 0; row < 9; row++){
            for(int col = 0; col < 9; col++){
                if(board[row][col] != '.') continue;
                for(int i = '1'; i <= '9'; i++){
                    if(isValid(row, col, i, board)){
                        board[row][col] = i;
                        if(backtrack(board)) return true;
                        board[row][col] = '.';
                    }
                }
                return false;
            }
        }
        return true; 
    }
public:
    void solveSudoku(vector<vector<char>>& board) {
        backtrack(board);
    }
};