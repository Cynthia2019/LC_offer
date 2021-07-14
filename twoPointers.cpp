//15. 三数之和
// 给你一个包含 n 个整数的数组 nums，判断 nums 中是否存在三个元素 a，b，c ，使得 a + b + c = 0 ？请你找出所有和为 0 且不重复的三元组。

// 注意：答案中不可以包含重复的三元组。

//思路：暴力解要三次循环O(n^3)，双指针可以在两次循环内完成O(n^2)。
//先sort O(nlogn)
//遍历每一个element，其中设element最左为left，数组最后一位为right，根据有序数组的特性去找满足条件的三个数
//注意：需要去重，方法是因为数组是有序的，所以在每一次大循环前，判断当前的元素和是否与前一个元素相同，如果是，则跳过小循环（continue）
//在每一次找到三元数组之后，仍然要判定当前的left和right前后有没有相同的元素。
vector<vector<int>> threeSum(vector<int>& nums) {
    if(nums.size() < 3){
        return vector<vector<int>>{};
    }
    sort(nums.begin(), nums.end());
    vector<vector<int>> ans;
    for(int i = 0; i < nums.size() - 1; i++){
        if(nums[i] > 0){break;} //如果三元组最小的数就大于0，则不可能等于0，break
        if (i > 0 && nums[i] == nums[i - 1]) {
            continue;
        }//去重
        int left = i + 1; 
        int right = nums.size() - 1;
        while(left < right){
            if(nums[left] + nums[right] + nums[i] == 0){
                ans.push_back({nums[i], nums[left], nums[right]});
                while(left < right && nums[left] == nums[left+1]){
                    left++;}
                while(left < right && nums[right] == nums[right-1]){right--;}
                left++;
                right--;
            }
            else if(nums[i] + nums[left] + nums[right] < 0){
                left += 1;
            } else {
                right -= 1;
            }
        }
    } 
    return ans;
}

//18. 四数之和
// 给定一个包含 n 个整数的数组 nums 和一个目标值 target，判断 nums 中是否存在四个元素 a，b，c 和 d ，使得 a + b + c + d 的值与 target 相等？找出所有满足条件且不重复的四元组。

// 注意：答案中不可以包含重复的四元组。

vector<vector<int>> fourSum(vector<int>& nums, int target) {
    vector<vector<int>> ans;
    if(nums.size() < 4)return ans;
    sort(nums.begin(), nums.end());
    for(int i = 0; i < nums.size() - 3; i++){
        if(i > 0 && nums[i] == nums[i - 1])continue;
        
        for(int j = i + 1; j < nums.size() - 2; j++){
            if(j > i + 1 && nums[j] == nums[j - 1])continue;
            int left = j + 1; 
            int right = nums.size() - 1;
            while(left < right){
                int sum = nums[i] + nums[j] + nums[left] + nums[right]; 
                if(sum < target){
                    left++;
                }
                else if (sum > target){
                    right--; 
                }
                else {
                    ans.push_back(vector<int>{nums[i], nums[j], nums[left], nums[right]});
                    while(left < right && nums[left] == nums[left+1])left++;
                    while(left < right && nums[right] == nums[right-1])right--;
                    left++;
                    right--;
                }
            }
        }
    }
    return ans;
}
//数组作为HashTable: 场景：可能出现的字符是有限的，并且范围不是太广
//set作为HashTable：场景：可能出现的字符不受限，或范围太广导致数组空间的极大浪费；一般用来判断元素是否出现过。
//map作为HashTable：场景：用来处理set和数组解决不了的更加复杂的场景。