//472. Concatenated Words
class Trie {
public: 
    vector<Trie*> children;
    bool isEnd;  
    Trie(): children(26), isEnd(false) {};
    void insert(string& word){
        Trie* node = this; 
        for(char c : word){
            c -= 'a'; 
            if(node->children[c] == nullptr){
                node->children[c] = new Trie(); 
            }
            node = node->children[c]; 
        }
        node->isEnd = true; 
    }
};
class Solution {
private: 
    static bool cmp(string& a, string& b){
        return a.size() < b.size(); 
    }
public:
    Trie* t = new Trie(); 
    vector<string> findAllConcatenatedWordsInADict(vector<string>& words) {
        vector<string> ans; 
        sort(words.begin(), words.end(), cmp); 
        for(string word : words){
            if(word.size() == 0) continue; 
            if(dfs(word, 0)){
                ans.push_back(word); 
            }
            else t->insert(word);
        }
        return ans; 
    }
    bool dfs(string& word, int index){
        if(index == word.size()) return true; 
        Trie* node = t; 
        for(int i = index; i < word.size(); i++){
            int c = word[i] - 'a'; 
            node = node->children[c];
            //当前char没被找到 return false
            if(node == nullptr) return false; 
            //当前char是某单词的结尾 -- 回到Trie的头部对于下一个char搜索新单词
            if(node->isEnd){
                // cout << "i: " << i << " " << word[i] << endl;
                if(dfs(word, i+1)) return true; 
            }
            //当前char被找到，但不是单词结尾 -- 对于当前单词继续搜索，更新trie指针
        }
        return false; 
    }
};