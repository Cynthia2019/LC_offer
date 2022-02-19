//215. Kth Largest Element in an Array
//implemetation of max heap without priority queue
class Solution {
private: 
    void buildMaxHeap(vector<int>& a, int heapSize){
        for(int i = heapSize / 2; i >= 0; --i){
            maxHeapify(a, i, heapSize);
        }
    }
    void maxHeapify(vector<int>& a, int i, int heapSize){
        int l = i * 2 + 1; 
        int r = i * 2 + 2; 
        int largest = i; 
        if(l < heapSize && a[l] > a[largest]){
            largest = l;
        }
        if(r < heapSize && a[r] > a[largest]){
            largest = r; 
        }
        if(largest != i){
            swap(a[largest], a[i]); 
            maxHeapify(a, largest, heapSize);
        }
    }
public:
    int findKthLargest(vector<int>& nums, int k) {
        int heapSize = nums.size();
        buildMaxHeap(nums, nums.size()); 
        for(int i = nums.size() - 1; i > nums.size() - k; i--){
            swap(nums[i], nums[0]);
            heapSize--;
            maxHeapify(nums, 0, heapSize);
        }
        return nums[0];
    }
};

//347. Top K Frequent Elements
//priority_queue takes an data type, a container type, and a compare function with decltype
//emplace = construct and insert

class Solution {
private: 
    static bool cmp(pair<int, int>& a, pair<int, int>& b){
        return a.second > b.second;
    }
public:
    vector<int> topKFrequent(vector<int>& nums, int k) {
        unordered_map<int, int> count; 
        for(int i : nums){
            count[i]++;
        }
        priority_queue<pair<int, int>, vector<pair<int, int>>, decltype(&cmp)>q(cmp); 
        for(auto& [num, c] : count){
            if(q.size() == k){
                if(q.top().second < c){
                    q.pop();
                    q.emplace(num, c);
                }
            }
            else {
                q.emplace(num, c);
            }
        }
        vector<int> ans;
        while(!q.empty()){
            ans.push_back(q.top().first);
            q.pop();
        }
        return ans; 
    }
};

//373. Find K Pairs with Smallest Sums
//nested comparator 
class Solution {
public:
    vector<vector<int>> kSmallestPairs(vector<int>& nums1, vector<int>& nums2, int k) {
        auto cmp = [&nums1, &nums2](pair<int, int>& a, pair<int, int>& b){
            return nums1[a.first] + nums2[a.second] > nums1[b.first] + nums2[b.second];
        };
        vector<vector<int>> ans; 
        priority_queue<pair<int, int>, vector<pair<int, int>>, decltype(cmp)> q(cmp);  
        q.emplace(0, 0); 
        while(k-- > 0 && q.size() != 0){
            auto indexPair = q.top(); q.pop();
            //the first element of the nums is always the smallest one
            //so at least one of them should be included in the final answer
            ans.push_back({nums1[indexPair.first], nums2[indexPair.second]}); 
            if(indexPair.first + 1 < nums1.size()){
                q.emplace(indexPair.first + 1, indexPair.second);
            }
            if(indexPair.first == 0 && indexPair.second + 1 < nums2.size()){
                q.emplace(indexPair.first, indexPair.second+1); 
            }
        }
        return ans; 
    }
};

//44. Wildcard Matching
//重点： 整理p的三种状态以及每种状态下的公式
class Solution {
public:
    bool isMatch(string s, string p) {
        int m = s.size(); 
        int n = p.size(); 
        vector<vector<bool>> dp(m+1, vector<bool>(n+1, false)); 
        dp[0][0] = true; 
        for(int j = 0; j < n; j++){
            if(p[j] == '*'){
                dp[0][j+1] = true; 
            }
            else break; 
        }
        for(int i = 1; i <= m; i++){
            for(int j = 1; j <= n; j++){
                if(s[i-1] == p[j-1] || p[j-1] == '?'){
                    dp[i][j] = dp[i-1][j-1]; 
                }
                else if (p[j-1] == '*'){
                    dp[i][j] = dp[i-1][j] || dp[i][j-1]; 
                }
                else {
                    dp[i][j] = false; 
                }
            }
        }
        return dp[m][n];
    }
};

//1705 Maximum Number of Eaten Apples
//greedy + prioirty queue
//use a queue to maintain the smallest valid finished time 
//greedy 思路: finish the apple with the smallest finished time first
class Solution {
private:
    static bool cmp(vector<int>& a, vector<int>& b){
        if(a[1] == b[1]) return a[0] > b[0];
        return a[1] > b[1]; 
    }
public:
    int eatenApples(vector<int>& apples, vector<int>& days) {
        int ans = 0; 
        priority_queue<vector<int>, vector<vector<int>>, decltype(&cmp)> q(cmp); 
        for(int i = 0; i < apples.size(); i++){
            if(apples[i]) q.push({apples[i], i+days[i]}); 
            while(!q.empty() && (q.top()[1] <= i || q.top()[0] == 0)){
                q.pop();
            }
            if(q.empty()) continue;
            vector<int> choice = q.top(); 
            q.pop(); 
            choice[0]--; 
            ans++; 
            q.push(choice); 
        }
        int count = apples.size();
        while(!q.empty()){
            while(!q.empty() && (q.top()[1] <= count || q.top()[0] == 0)){
                q.pop();
            }
            if(q.empty()) return ans; 
            vector<int> choice = q.top(); q.pop(); 
            ans++; 
            choice[0]--;
            q.push(choice); 
            count++;
        }
        return ans;
    }
};