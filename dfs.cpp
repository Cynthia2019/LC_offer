//250. Count Univalue Subtrees
//post order traversal 
//verify left and right child first, then process the middle node
//left represents if the left subtree has the same value with the current node
//increment ans if both left and right return true (both left subtree and right subtree has the same node val with the current node)
//return true if the both left and right has the same node value with the current node and the current node has the same value with its parent node
class Solution {
private: 
    int ans = 0; 
    bool dfs(TreeNode* node, int val){
        if(node == nullptr) return true; 
        bool left = dfs(node->left, node->val); 
        bool right = dfs(node->right, node->val); 
        if(left && right) ans++; 
        return node->val == val && left && right;
    }
public:
    int countUnivalSubtrees(TreeNode* root) {
        if(root == nullptr) return 0;
        dfs(root, root->val); 
        return ans;
    }
};