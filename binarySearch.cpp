//540. Single Element in a Sorted Array
//主要注意边界处理，以及定义从哪开始查找
//还有xor的trick
class Solution {
public:
    int singleNonDuplicate(vector<int>& nums) {
        if(nums.size() == 1) return nums[0];  
        int left = 0; 
        int right = nums.size() - 1; 
        while(left < right){
            int mid = left + (right - left) / 2; 
            if(nums[mid] == nums[mid ^ 1]){
                left = mid + 1; 
            } 
            else {
                right = mid; 
            }
        }
        return nums[left]; 
    }
};