//547 Number of Provinces
class Solution {
private: 
    int Find(vector<int>& parents, int i){
        if(parents[i] != i){
            parents[i] = Find(parents, parents[i]); 
        }
        return parents[i]; 
    }
    void Union(vector<int>& parents, int i, int j){
        parents[Find(parents, i)] = Find(parents, j); 
    }
public:
    int findCircleNum(vector<vector<int>>& isConnected) {
        int provinces = isConnected.size(); 
        vector<int> parents(provinces); 
        for(int i = 0; i < provinces; i++){
            parents[i] = i; 
        }
        for(int i = 0; i < provinces; i++){
            for(int j = i+1; j < provinces; j++){
                if(isConnected[i][j]){
                    Union(parents, i, j); 
                }
            }
        }
        int ans = 0; 
        for(int i = 0; i < parents.size(); i++){
            if(parents[i] == i){
                ans++; 
            }
        }
        return ans; 
    }
};

//323. Number of Connected Components in an Undirected Graph
class Solution {
private: 
    int Find(vector<int>& parents, int i){
        if(parents[i] != i){
            parents[i] = Find(parents, parents[i]);
        }
        return parents[i]; 
    }
    void Union(vector<int>& parents, int i, int j){
        parents[Find(parents, i)] = Find(parents, j); 
    }
public:
    int countComponents(int n, vector<vector<int>>& edges) {
        int ans = 0; 
        vector<int> parents(n);
        for(int i = 0; i < n; i++){
            parents[i] = i; 
        } 
        for(int i = 0; i < edges.size(); i++){
            vector<int> edge = edges[i]; 
            Union(parents, edge[0], edge[1]); 
        }
        for(int i = 0; i < parents.size(); i++){
            if(parents[i] == i) ans++; 
        }
        return ans; 
    }
};


class UnionFind {
private: 
    vector<int> parents; 
    vector<int> rank; 
    int count; 
public: 
    UnionFind(vector<vector<char>>& grid) {
        int m = grid.size(); 
        int n = grid[0].size(); 
        for(int i = 0; i < m; i++){
            for(int j = 0; j < n; j++){
                if(grid[i][j] == '1'){
                    parents.push_back(i * n + j); 
                    count++; 
                }
                else {
                    parents.push_back(-1); 
                }
                rank.push_back(0); 
            }
        }
    }
    int Find(int i){
        if(parents[i] != i){
            parents[i] = find(parents[i]);
        }
        return parents[i]; 
    }
    void Union(int i, int j){
        int parenti = Find(i); 
        int parentj = Find(j); 
        if(parenti != parentj){
            if(rank[parenti] < rank[parentj]){
                swap(parenti, parentj); 
            }
            parents[parentj] = parenti; 
            count--; 
        }
    }
    int getCount() {
        return count; 
    }
}