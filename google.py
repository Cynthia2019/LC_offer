
def solution(data, n): 
    # Your code here
    counter = {}
    for i in range(len(data)): 
        if not data[i] in counter: 
            counter[data[i]] = 1
        else: 
            counter[data[i]] += 1
            
    index = 0 
    while index < len(data):
        if counter[data[index]] >= n:
            data.pop(index) 
        else: 
            index += 1
    return data

def solution2(xs): 
    dp_min = [0] * len(xs)
    dp_max = [0] * len(xs)
    dp_min[0] = xs[0] 
    dp_max[0] = xs[0]
    for i in range(1, len(xs)): 
        dp_min[i] = min(xs[i] ,dp_min[i-1], xs[i] * dp_max[i-1], xs[i] * dp_min[i-1])
        dp_max[i] = max(xs[i], dp_max[i-1], xs[i] * dp_max[i-1], xs[i] * dp_min[i-1])
        print(dp_min[i], dp_max[i], i)
    ans = max(dp_min[-1], dp_max[-1])
    return str(ans)

if __name__ == "__main__":
    test = [-2, -3, 4, -5]
    ans = solution2(test)
    print(ans)