#include<iostream>
#include<string>
#include<vector>
using namespace std; 
// 1. Random number generator 
class Random {
private: 
    int min; 
    int max; 
    vector<int> nums; 
    void shuffle(){
        for(int i = 0; i < nums.size(); i++){
            int j = i + rand() % (nums.size() - i); 
            swap(nums[i], nums[j]); 
        }
    }
public: 
    Random(int min, int max){
        this->min = min; 
        this->max = max; 
        vector<int> range; 
        for(int i = 0; i <= max - min; i++){
            range.push_back(i); 
        }
        this->nums = range; 
    }
    vector<int> nextRandom(int n){
        shuffle(); 
        vector<int> ans; 
        for(int i = 0; i < n; i++){
            ans.push_back(this->nums[i]); 
        }
        return ans; 
    }
};

class Random2 {
private: 
    int min; 
    int max; 
    vector<int> picked; 

    vector<int> shuffle(){
        vector<int> ans; 
        for(int i = min; i <= max; i++){
            int j = i + rand() % (max - min); 
            while(find(picked.begin(), picked.end(), j) != picked.end()){
                j = i + rand() % (max - min); 
            }
            picked.push_back(j); 
            ans.push_back(j); 
        }
        return ans; 
    }
public: 
    Random2(int min, int max){
        this->min = min; 
        this->max = max; 
    }
    vector<int> nextRandom(int n){ 
        vector<int> ans = shuffle();
        return vector<int>(ans.begin(), ans.begin() + n); 
    }
};
int main() {
    Random2* R = new Random2(0, 100); 
    int n = 7; 
    for(int k = 0; k < 2; k++){
        vector<int> random = R->nextRandom(n);
        cout << random[0];
        for(int i = 0; i < n; i++){
            cout << random[i] << " "; 
        } 
    }
    return 0; 
}
//Random Number Generator Follow up: call nextRandom with a new [min, max] range
//discuss by case: 
// 1. no overlap, then just return a new shuffled array 
// 2. overlap. treat the overlapped part as a blacklist
//710
class Solution {
private: 
    int white_len; 
    unordered_map<int, int> m; 
public:
    Solution(int n, vector<int>& blacklist) {
        int white_len = n - blacklist.size(); 
        this->white_len = white_len; 
        unordered_set<int> white; 
        for(int i = white_len; i < n; i++){
            white.insert(i); 
        }
        for(int i : blacklist){
            white.erase(i); 
        }
        auto p = white.begin(); 
        for(int i : blacklist){
            if(i < white_len){
                m[i] = *p++; 
            }
        }
    }
    
    int pick() {
        int random = rand() % white_len; 
        if(m.find(random) != m.end()) return m[random];
        return random; 
    }
};


//146 LRU cache
struct DoubleLinkedNode {
    int key; 
    int value; 
    DoubleLinkedNode* prev; 
    DoubleLinkedNode* next; 
    DoubleLinkedNode(): key(0), value(0), prev(nullptr), next(nullptr) {}; 
    DoubleLinkedNode(int k, int v): key(k), value(v), prev(nullptr), next(nullptr) {};  
};
class LRUCache {
private: 
    unordered_map<int, DoubleLinkedNode*> cache; 
    int capacity;
    int size; 
    DoubleLinkedNode* head; 
    DoubleLinkedNode* tail;  

    void removeNode(DoubleLinkedNode* node){
        node->next->prev = node->prev; 
        node->prev->next = node->next; 
    }
    void addToHead(DoubleLinkedNode* node){
        head->next->prev = node; 
        node->next = head->next; 
        head->next = node; 
        node->prev = head; 
    }
public:
    LRUCache(int capacity) {
        this->capacity = capacity; 
        this->head = new DoubleLinkedNode(); 
        this->tail = new DoubleLinkedNode(); 
        head->next = tail; 
        tail->prev = head; 
        this->size = 0; 
    }
    
    int get(int key) {
        if(cache.find(key) == cache.end()) return -1; 
        DoubleLinkedNode* node = cache[key]; 
        removeNode(node); 
        addToHead(node); 
        return node->value; 
    }
    
    void put(int key, int value) {
        if(cache.find(key) != cache.end()) {
            DoubleLinkedNode* node = cache[key]; 
            node->value = value; 
            removeNode(node); 
            addToHead(node); 
        }
        else {
            DoubleLinkedNode* node = new DoubleLinkedNode(key, value);
            addToHead(node);  
            cache[key] = node; 
            if(size == capacity){
                //remove node before tail 
                DoubleLinkedNode* remove = tail->prev; 
                tail->prev = remove->prev; 
                remove->prev->next = tail; 
                cache.erase(remove->key); 
                delete(remove); 
            }
            else {
                size++; 
            }
        }
    }

};

//210. Course Schedule II 
class Solution {
private: 
    vector<vector<int>> edges; 
    vector<int> visited; 
    bool valid = true; 
    vector<int> ans; 

    void dfs(int u){
        visited[u] = 1; 
        //iterate all of u's connected parts
        for(int v : edges[u]){
            if(visited[v] == 0){
                dfs(v); 
            } 
            else if(visited[v] == 1){
                valid = false; 
                return ; 
            }
        }
        visited[u] = 2; 
        ans.push_back(u); 
    }
public:
    vector<int> findOrder(int numCourses, vector<vector<int>>& prerequisites) {
        edges.resize(numCourses); 
        visited.resize(numCourses); 
        //not visited: 0, processing: 1, done: 2
        for(int i = 0; i < prerequisites.size(); i++){
            vector<int> pre = prerequisites[i]; 
            edges[pre[0]].push_back(pre[1]);  
        }
        for(int i = 0; i < numCourses; i++){
            visited[i] = 0; 
        }
        for(int i = 0; i < visited.size() && valid; i++){
            if(visited[i] == 0){
                dfs(i); 
            }
        }
        if(!valid) return {}; 
        return ans; 
    }
};

//380. Insert Delete GetRandom O(1)
class RandomizedSet {
private: 
    unordered_map<int, int> m; 
    vector<int> nums; 
public:
    RandomizedSet() {

    }
    
    bool insert(int val) {
        if(m.find(val) != m.end()) return false; 
        else {
            m[val] = nums.size(); 
            nums.push_back(val); 
            return true; 
        }
    }
    
    bool remove(int val) {
        if(m.find(val) != m.end()) {
            m[nums.back()] = m[val]; 
            swap(nums[m[val]], nums.back()); 
            nums.pop_back(); 
            m.erase(val); 
            return true; 
        }
        return false; 
    }
    
    int getRandom() {
        int x = rand() % nums.size(); 
        return nums[x]; 
    }
};