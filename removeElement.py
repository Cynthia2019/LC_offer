#27. 移除元素
"""
双指针解法

重点在于明确每个指针的定位和作用，一般来说快指针会一阵被更新，而慢指针则是在一定条件下才会更新。

思路：快慢指针，快指针标记当前处理的元素，慢指针标记下一个将要被赋值的元素

***Array特性：内存地址是连续的，所以元素不能被移除，只能被覆盖
"""
def removeElement(self, nums: List[int], val: int) -> int:
    fastPointer = 0 
    slowPointer = 0 
    while fastPointer < len(nums):
        nums[slowPointer] = nums[fastPointer]
        if nums[fastPointer] != val: 
            slowPointer += 1
        fastPointer += 1
    return slowPointer

#26. 删除有序数组中的重复项
"""
给你一个有序数组 nums ，请你 原地 删除重复出现的元素，使每个元素 只出现一次 ，返回删除后数组的新长度。

思路：快指针表示当前要处理的元素，慢指针表示下一个第一次出现的元素的坑位。
如果 nums[fastPointer] != nums[fastPointer - 1]， 则说明这个元素是第一次出现，把它放到slowPointer的坑位上
并slowPointer += 1. 
"""
def removeDuplicates(self, nums: List[int]) -> int:
    if len(nums) <= 1: 
        return len(nums)
    fastPointer = 1
    slowPointer = 1
    while fastPointer < len(nums): 
        if nums[fastPointer] != nums[fastPointer - 1]: 
            nums[slowPointer] = nums[fastPointer]
            slowPointer += 1
        fastPointer += 1
    return slowPointer

#283. 移动零
"""
给定一个数组 nums，编写一个函数将所有 0 移动到数组的末尾，同时保持非零元素的相对顺序。
思路：fast指向当前处理的元素，slow指向下一个与非0元素交换位置的坑位；目的是fast以左都要是非0，fast以右都是0.
每当nums[fast] != 0的时候，该元素应该放到fast左边。我们把fast和slow的元素交换位置。
"""
def moveZeroes(self, nums: List[int]) -> None:
    fast = 0
    slow = 0
    while fast < len(nums): 
        if nums[fast] != 0: 
            temp = nums[slow]
            nums[slow] = nums[fast]
            nums[fast] = temp
            slow += 1
        fast += 1

#844. 比较含退格的字符串 (在做一遍)
"""
给定 S 和 T 两个字符串，当它们分别被输入到空白的文本编辑器后，判断二者是否相等，并返回结果。 # 代表退格字符。

注意：如果对空文本输入退格字符，文本继续为空。

思路：由于‘#’影响前一个元素，不影响后一个元素，所以我们可以反向遍历字符串。
用两个指针来指向两个字符串，每次遍历指针递减，当当前元素不一样时，return False。
用skipS与skipT来表示当前遇到的‘#’次数：每遇到一次，skip+=1， 进入小循环.
当skip不为0时，当前遇到的字符是要被删除的，所以指针向前移一位， skip-=1。当skip==0时，跳出小循环
当两个字符的小循环都结束之后，进入大循环，如果当前指针都大于等于0（一次遍历还没完成）且元素不一样时，return False。
如果有一方已经完成一次遍历，而另一方没有，则两条字符串不相等。

"""
def backspaceCompare(s: str, t: str) -> bool:
    skipS, skipT = 0, 0
    i, j = len(s) - 1, len(t) - 1
    while i >= 0 or j >= 0:
        while i >=0:
            if i == '#':
                skipS += 1
            else: 
                if skipS > 0:
                    i -= 1
                    skipS -= 1
                else: 
                    break
        while j >= 0:
            if j == '#':
                skipT += 1
            else: 
                if skipT > 0:
                    j -= 1
                    skipT -= 1
                else: 
                    break
        if i >= 0 and j >= 0:
            if s[i] != t[j]:
                return False
        else: 
            if i >=0 or j >= 0:
                return False 
        i -= 1
        j -= 1
    return True

#977. 有序数组的平方
"""
给你一个按 非递减顺序 排序的整数数组 nums，返回 每个数字的平方 组成的新数组，要求也按 非递减顺序 排序。

思路：
1. 暴力算出平方并排序需要O(nlogn)时间，O(logn)空间去存储排序用的空间栈
2. 双指针：时间O(n), 空间O(1)，不包括存储答案的数组所占空间
主要思想：因为是排序数组，所以可以分成负数和非负数两边。负数的平方递减，非负数的平方递增（非递减）
先遍历一遍找到负数的分界线，然后给两个指针，neg和pos=neg+1。分别对这两段进行判定，依次放入答案数组中。
"""
def sortedSquares(self, nums: List[int]) -> List[int]:
    last_neg = -1 
    for index, value in enumerate(nums):
        if value < 0: 
            last_neg = index
        else: 
            break 
    neg = last_neg
    pos = last_neg + 1
    ans = []
    while neg >= 0 or pos < len(nums):
        if neg < 0:
            ans.append(nums[pos] * nums[pos])
            pos += 1
        elif pos == len(nums):
            ans.append(nums[neg] * nums[neg])
            neg -= 1
        elif nums[pos] * nums[pos] > nums[neg] * nums[neg]:
            ans.append(nums[neg] * nums[neg])
            neg -= 1
        else: 
            ans.append(nums[pos] * nums[pos])
            pos += 1
    return ans
