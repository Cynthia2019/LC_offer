#include <unordered_set>>;
#include <string>;
#include <vector>;
//思路：要快速判断一个元素是否出现集合里的时候，就要考虑哈希法
//242. 有效的字母异位词
bool isAnagram(std::string s, string t) {
    int record[26] = {0};
    for(int i = 0; i < s.length(); i++){
        record[s[i] - 'a']++;
    }
    for(int j = 0; j < t.length(); j++){
        record[t[j] - 'a']--;
    }
    for(int i = 0; i < 26; i++){
        if(record[i] != 0){
            return false;
        }
    }
    return true;
}

//349. 两个数组的交集
//给定两个数组，编写一个函数来计算它们的交集。
//这题主要是认识并运用unordered_set; 他查找和增删的时间都是O(1)，比数组快。
//unordered_set查找的方式是.find(), 如果当前key没有找到，就会return .end() (pointer to the following of the last element)
//所以判定key在set里面的方式就是set1.find(j) != set1.end()
//将vector放入set或者set放入vector的方式是一样的：unordered_set<int> set1(nums1.begin(), nums1.end()); 
//return an empty vector：vector<int>();
vector<int> intersection(vector<int>& nums1, vector<int>& nums2) {
    unordered_set<int> set1(nums1.begin(), nums1.end()); 
    unordered_set<int> res;
    for(int j : nums2){
        if(set1.find(j) != set1.end()){
            res.insert(j);
        }
    }
    return vector<int>(res.begin(), res.end());
}

//202. 快乐数
//思路：若sum出现重复，则一定会出现无限循环--维护一个set，来判定是否见过当前的sum。
//unordered_set 很大的用处之一就是判定元素是否出现过 （虽然Array也能判断，但是unordered_set efficient许多）
//经典的拆分数字位数的方法，可以记一下，O(log n)
int getSum(int n){
    int sum = 0;
    while(n){
        sum += (n % 10) * (n % 10);
        n /= 10;
    }
    return sum;
}
bool isHappy(int n) {
    unordered_set<int> set;
    while(1){ 
        int sum = getSum(n);
        if(sum == 1){
            return true;
        }
        else{
            if(set.find(sum) != set.end()){
                return false;
            }
            else {
                set.insert(sum);
            }
        }
        n = sum;
    }
    return false;
}

//unordered_map
//用法：unordered_map<int, int> map, 
//map.find() returns an iterator to the key-value pair or map.end()
//iter->second is the mapped value. 
vector<int> twoSum(vector<int>& nums, int target) {
    unordered_map<int, int> map; 
    for(int i = 0; i < nums.size(); i++){
        auto iter = map.find(target - nums[i]);
        if(iter != map.end()){
            return {iter->second, i};
        }
        map.insert(pair<int, int>(nums[i], i));
    }
    return vector<int>();
}
//50. 第一个只出现一次的字符
char firstUniqChar(string s) {
    unordered_map<char, int> map; 
    for(int i = 0; i < s.size(); i++){
        auto iter = map.find(s[i]);
        if(iter != map.end()){
            iter->second += 1;
        } else {
            map.insert(pair<char, int>(s[i], 1));
        }
    }
    for(int i = 0; i < s.size(); i++){
        auto iter = map.find(s[i]);
        if(iter->second == 1){
            return s[i];
        }
    }
    return ' ';
}
// an array is faster and more space-efficient than a hashmap
char firstUniqChar(string s) {
    int record[26] = {0};
    for(int i = 0; i < s.size(); i++){
        record[s[i] - 'a']++;
    }
    for(int i = 0; i < s.size(); i++){
        if(record[s[i] - 'a'] == 1){
            return s[i];
        }
    }
    return ' ';
}

//454. fourSumCountII
// 给定四个包含整数的数组列表 A , B , C , D ,计算有多少个元组 (i, j, k, l) ，使得 A[i] + B[j] + C[k] + D[l] = 0。

// 为了使问题简单化，所有的 A, B, C, D 具有相同的长度 N，且 0 ≤ N ≤ 500 。所有整数的范围在 -228 到 228 - 1 之间，最终结果不会超过 231 - 1 。

//思路：跟两数之和差不多的思路。讲前两个数组和后两个数组分成两组。使用一个map来记录前两个数组中的和以及每个和出现的次数。再遍历后两个数组，
//如果在map中能找到加起来为0的数，则ans 加上这个和出现的次数。
int fourSumCount(vector<int>& nums1, vector<int>& nums2, vector<int>& nums3, vector<int>& nums4) {
    unordered_map<int, int> map; 
    int ans = 0;
    for(int i : nums1){
        for(int j : nums2){
            ++map[i + j];
        }
    }
    for (int i : nums3){
        for(int j : nums4){
            if(map.find(-(i+j)) != map.end()){
                ans += map.find(-(i+j))->second;
            }
        }
    }
    return ans;
}