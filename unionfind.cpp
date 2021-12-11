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