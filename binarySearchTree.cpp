//700. Search in a Binary Search Tree
//BST traversal with iteration 
TreeNode* searchBST(TreeNode* root, int val) {
    while (root != NULL) {
        if (root->val > val) root = root->left;
        else if (root->val < val) root = root->right;
        else return root;
    }
    return NULL;
}
//recursion
TreeNode* searchBST(TreeNode* root, int val) {
    if(root == nullptr) return NULL; 
    if(root->val == val) return root; 
    if(root->val > val) return searchBST(root->left, val); 
    else return searchBST(root->right, val); 
}

//530. Minimum Absolute Difference in BST
class Solution {
private: 
    void traversal(TreeNode* root) {
        if(root == nullptr) return;
        traversal(root->left);
        if(prev != nullptr) {
            if(root->val - prev->val < result){
                result = root->val - prev->val;
            }
        }
        prev = root; //处理完当前节点之后就可以存放成前一个节点了
        traversal(root->right);  
    }
public:
    int result = INT_MAX;
    TreeNode* prev;
    int getMinimumDifference(TreeNode* root) {
        traversal(root);
        return result;
    }
};

//501. Find Mode in Binary Search Tree
class Solution {
private: 
    void traversal(TreeNode* root){
        if(root == nullptr) return;
        if(root->left) traversal(root->left); 
        if(prev == nullptr) { //第一个节点
            count = 1 
        } else if (prev->val == root->val) { //与前一个数相同
            count++; 
        } else { //与前一个数不同
            count = 1;
        }
        prev = root; 
        if(count > maxCount) {
            result.clear(); 
            result.push_back(root->val);
            maxCount = count;
        }
        if(count == maxCount && find(result.begin(), result.end(), root->val) == result.end()) {
            result.push_back(root->val);
        }
        if(root->right) traversal(root->right);
    }
public:
    int maxCount = 0; 
    int count = 0; 
    vector<int> result; 
    TreeNode* prev;
    vector<int> findMode(TreeNode* root) {
        traversal(root); 
        return result;
    }
};

//450. Delete Node in a BST
TreeNode* deleteNode(TreeNode* root, int key) {
    if(root == nullptr) return root; 
    if(root->val == key) {
        if (root->left == nullptr && root->right == nullptr){
            return nullptr; 
        }
        if(root->right != nullptr){
            TreeNode* right_pointer = root->right; 
            TreeNode* parent = root->right;
            while(right_pointer != nullptr){
                parent = right_pointer;
                right_pointer = right_pointer->left; 
            }
            parent->left = root->left; 
            return root->right;
        }
        else return root->left; 
    }
    if(root->val > key) root->left = deleteNode(root->left, key);
    if(root->val < key) root->right = deleteNode(root->right, key); 
    return root; 
}