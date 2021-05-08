#剑指 Offer 21. 调整数组顺序使奇数位于偶数前面
#双指针，头指针+尾指针
class Solution:
    def exchange(self, nums: List[int]) -> List[int]:
        if len(nums) == 0: 
            return nums
        head = 0 
        tail = len(nums) - 1
        while head != tail: 
            if nums[head] % 2 == 0: 
                temp = nums[tail]
                nums[tail] = nums[head]
                nums[head] = temp 
                tail -= 1
            else: 
                head += 1
        return nums
