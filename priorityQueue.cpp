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