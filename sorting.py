"""
Bubble Sort
Idea: 对每一个element进行loop，循环中element与其右边元素比较大小，比右边大则调换位置。直到循环完毕
Time: O(n^2)
Code: 
"""
elements = [3, 5, 4, 6, 1, 2]
for i in range(len(elements) - 1): 
    for j in range(0, len(elements)-i): 
        if elements[i] > elements[j]: 
            temp = elements[i]
            elements[i] = elements[j]
            elements[j] = temp


"""
Selection Sort
Idea: 设第一个没被sort的element为最小值和sorted，在剩下的unsorted elements中找出当前最小值，放入sorted中
Time
"""
sorted = []
for i in range(len(elements)): 
    min = elements[i]
    for j in range(i, len(elements)):
        if elements[j] < min: 
            min = elements[j]
            temp = elements[i]
            elements[i] = elements[j]
            elements[j] = temp 
    sorted.append(min)

print(sorted)