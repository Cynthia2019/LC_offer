"""
思路；
1. 先设left = right = 0，slideWindow = [left, right]
2. 先扩大right的值，使得slideWindow内的元素满足要求
3. 扩大left的值，直到slideWindow内的元素不满足要求；每一次扩大left前，要更新一边当前最优解
4. repeat 2 和 3，直到right == len(s) - 1s
***2找到当前最优解，3优化最优解，最后得到全局最优解
"""
def lengthOfLongestSubstring(self, s: str) -> int:
    #滑动窗口
    left = 0 
    right = 0
    window = []
    max_len = 0
    while right != len(s): 
        if s[right] not in window: 
            window.append(s[right]) #把当前元素加入窗口中
            right += 1
        else: 
            left += 1
            window = []
            right = left
        max_len = max(max_len, len(window))
    return max_len
            