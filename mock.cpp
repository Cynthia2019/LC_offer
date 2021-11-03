int Fibonacci(int n){
    if(n == 1) return 1; 
    if(n == 2) return 1; 
    return Fibonacci(n-1) + Fibonacci(n-2); 
}

int dp(int n){
    vector<int> nums; 
    nums[0] = 1; 
    nums[1] = 1; 
    for(int i = 2; i < n; i++){
        nums[i] = nums[i-1] + nums[i-2]; 
    }
    return nums[n];
}

vector<int> twoSum(vector<int>& nums, int target){
    unordered_map<int, int> map; 
    for(int i = 0; i < nums.size(); i++){
        map[target - nums[i]] = nums[i];
    }
    for(int i = 0; i < nums.size(); i++){
        if(map.find(nums[i]) != map.end()){
            return vector<int>(i, find(nums.begin(), nums.end(), map[nums[i]]))
        }
    }
    return vector<int>();
}

