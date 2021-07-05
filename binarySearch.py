#Binary Search
"""
一般适用于在有序的数组中找到目标值
二分查找的难点在于确定边界条件。
一般来说：
mid = (left + right) // 2 or (left + right >> 1)
有两种写法： 
[left, right] 左闭右闭: left = 0, right = len(nums) - 1
[left, right) 左闭右开: left= 0, right = len(nums) 
根据这个条件来得出下面的写法
对于while left <= right 左闭右闭: 
    1. left = right是有意义的 (3 + 3) // 2 = 3; nums[3] 可以等于target
    2. left = mid + 1, right = mid - 1; 因为如果nums[mid] > target, 则当前mid及mid以右都没有意义，所以right = mid -1
对于while left < right 左闭右开
    1. left = right是没有意义的 (right out of index) 
    2. left = mid + 1, right = mid; 因为如果nums[mid] > target, 则当前mid及mid以右都没有意义， 由于right为开，所以right = mid
"""
#左闭右闭
def search(self, nums: List[int], target: int) -> int:
    left = 0
    right = len(nums) - 1
    while left <= right: 
        mid = (right + left) // 2
        if nums[mid] == target: 
            return mid
        if nums[mid] > target: 
            right = mid - 1
        else: 
            left = mid + 1
    return -1

#左闭右开
def search(nums, target): 
    left = 0
    right = len(nums)
    while left < right:
        mid = (left + right) // 2
        if nums[mid] == target: 
            return mid
        if nums[mid] > target: 
            right = mid
        else: 
            left = mid + 1
    return -1

#34. 在排序数组中查找元素的第一个和最后一个位置
"""
给定一个按照升序排列的整数数组 nums，和一个目标值 target。找出给定目标值在数组中的开始位置和结束位置。

如果数组中不存在目标值 target，返回 [-1, -1]。

二分法思路： 
我们要找的是[start, end] start是第一个大于等于target的数，end是第一个大于target的数-1。
这两个数都可以通过binary search来找。
要找第一个大于等于target的数我们可以写：
left, right, ans = 0, len(nums) -1, len(nums)
while left <= right: 
    mid = (left + right) >> 1
    if nums[mid] >= target: #如果当前值大于或等于target，则right变成mid前一位去找还有没有等于target的数
        right = mid - 1
        ans = mid #先记录当前的index
    else: 
        left = mid + 1
要找第一个大于target的数我们可以写：
left, right, ans = 0, len(nums) -1, len(nums)
while left <= right: 
    mid = (left + right) >> 1
    if nums[mid] > target: 
        right = mid - 1
        ans = mid 
    else: 
        left = mid + 1
"""
def searchRange(self, nums: List[int], target: int) -> List[int]:
    def binarySearch(nums, target, lower): 
        left = 0 
        right = len(nums) - 1
        ans = len(nums)
        while left <= right: 
            mid = (left + right) // 2
            if nums[mid] > target or (lower and nums[mid] >= target):
                right = mid - 1
                ans = mid
            else: 
                left = mid + 1
        return ans
    firstEqual = binarySearch(nums, target, True)
    firstLarger = binarySearch(nums, target, False) - 1
    if (firstEqual <= firstLarger) and (nums[firstEqual] == target) and (nums[firstLarger] == target) and (firstLarger < len(nums)):
        return [firstEqual, firstLarger]
    else: 
        return [-1, -1]

#69. x 的平方根
"""
实现 int sqrt(int x) 函数。

计算并返回 x 的平方根，其中 x 是非负整数。

由于返回类型是整数，结果只保留整数的部分，小数部分将被舍去。

思路：跟上题一样，找出第一个mid*mid小于等于x的数
"""
def mySqrt(self, x: int) -> int:
    left = 0 
    right = x 
    ans = x
    while left <= right: 
        mid = (left + right) >> 1 
        if mid * mid <= x: 
            left = mid + 1 
            ans = mid 
        else: 
            right = mid - 1
    return ans

#367. 有效的完全平方数
"""
给定一个 正整数 num ，编写一个函数，如果 num 是一个完全平方数，则返回 true ，否则返回 false 。

进阶：不要 使用任何内置的库函数，如  sqrt 。s
"""
def isPerfectSquare(self, num: int) -> bool:
    left = 0 
    right = num 
    while left <= right: 
        mid = (left + right) // 2
        if mid * mid == num: 
            return True
        if mid * mid < num: 
            left = mid + 1
        if mid * mid > num: 
            right = mid - 1
    return False