'''
03. 数组中重复的数字

在一个长度为 n 的数组 nums 里的所有数字都在 0～n-1 的范围内。数组中某些数字是重复的，但不知道有几个数字重复了，也不知道每个数字重复了几次。请找出数组中任意一个重复的数字。
'''
#Solution 1: list 
class Solution:
    def findRepeatNumber(self, nums: List[int]) -> int:
        visited = []
        for i in nums: 
            if i not in visited:
                visited.append(i)
            else: 
                return i 
        return -1
#time: O(n) very slow

#Solution 2: using set
#set中不能含有相同项
class Solution:
    def findRepeatNumber(self, nums: List[int]) -> int:
        a = set()
        for i in nums: 
            if len(a) == len(a.add(i)):
                return i
        return -1
