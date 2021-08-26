//Preorder traversal -> mid, left, right
//method 1: use recursion 
struct TreeNode {
    int val; 
    TreeNode *left; 
    TreeNode *right; 
    TreeNode(int x): val(x), left(nullptr), right(nullptr) {}
}

class Solution {
public:
    void traversal(TreeNode* curr, vector<int> &v){
        if(curr == nullptr){
            return;
        }
        else {
            v.push_back(curr->val); 
            traversal(curr->left, v);
            traversal(curr->right, v);
        }
    }
    vector<int> preorderTraversal(TreeNode* root) {
        vector<int> ans; 
        traversal(root, ans); 
        return ans;
    }
};

//method 2: iteration with stack
//use stack to record the elements. 
//push root to stack first, and pop it in the loop, then check if root has left or right
//push right child before left child (so that we can pop left child first) 
//loop ends if stack is empty (i.e we went through every node)
vector<int> preorderTraversal(TreeNode* root) {
    vector<int> ans; 
    stack<TreeNode*> s; 
    if(root == nullptr) return ans;
    s.push(root);
    while(!s.empty()){
        TreeNode* node = s.top();
        ans.push_back(node->val);
        s.pop(); 
        if(node->right){s.push(node->right);}
        if(node->left){s.push(node->left);}
    }
    return ans;
}

//Postorder => left, right, mid 
class Solution {
public:
    void traversal(TreeNode *curr, vector<int> &v) {
        if(curr == nullptr){
            return ;
        }
        traversal(curr->left, v);
        traversal(curr->right, v);
        v.push_back(curr->val);
    }
    vector<int> postorderTraversal(TreeNode* root) {
        vector<int> ans; 
        traversal(root, ans);
        return ans;
    }
};

//inorder: left, mid, right
//iteration
//思路： 用stack来储存将要被处理的node，从root开始，push左子树node入栈，用pointer来跟踪当前节点。
//停止条件：pointer为null（上一节点没有左/右子节点->叶子节点或者最后一个节点）或者stack空的（当前没有要处理的节点->根节点被处理或最后一个节点被处理）
vector<int> inorderTraversal(TreeNode* root) {
    vector<int> ans;
    stack<TreeNode*> s;
    TreeNode* curr = root; 
    while(curr != nullptr || !s.empty()){
        if(curr != nullptr){
            s.push(curr);
            curr = curr->left; //left
        }
        else {
            curr = s.top(); //mid
            ans.push_back(curr->val); 
            s.pop();
            curr = curr->right; //right
        }
    }
    return ans;
}

//102.二叉树的层序遍历
vector<vector<int>> levelOrder(TreeNode* root) {
    queue<TreeNode*> q; 
    vector<vector<int>> ans;
    if(root == nullptr){
        return ans;
    }
    q.push(root);
    while(!q.empty()){
        int size = q.size();
        vector<int> temp; 
        for(int i = 0; i < size; i++){
            TreeNode* curr = q.front();
            q.pop();
            temp.push_back(curr->val);
            if(curr->left){q.push(curr->left);}
            if(curr->right){q.push(curr->right);}
        } 
        ans.push_back(temp);
    }
    return ans;
}

//199. 二叉树的右视图
vector<int> rightSideView(TreeNode* root) {
    queue<TreeNode*> q; 
    vector<int> ans; 
    if(root == nullptr) return ans; 
    q.push(root);
    while(!q.empty()){
        int size = q.size(); 
        for(int i = 0; i < size; i++){
            TreeNode* temp = q.front(); 
            q.pop();
            if(i == size - 1){
                ans.push_back(temp->val);
            }
            if(temp->left){q.push(temp->left);}
            if(temp->right){q.push(temp->right);}
        }
    }
    return ans;
}

//101. 对称二叉树
//recursion
bool checkSymmetric(TreeNode* left, TreeNode* right){
    if(left == nullptr && right == nullptr) return true; 
    if(left == nullptr || right == nullptr) return false;
    if(left->val != right->val) return false; 
    bool outside = checkSymmetric(left->left, right->right); 
    bool inside = checkSymmetric(left->right, right->left);
    return outside && inside;
}
bool isSymmetric(TreeNode* root) {
    if (root == nullptr) return true;  
    bool ans = checkSymmetric(root->left, root->right);
    return ans;
}
//iteration
bool isSymmetric(TreeNode* root) {
    if(root == nullptr) return true; 
    stack<TreeNode*> s; 
    s.push(root->right); 
    s.push(root->left);
    while(!s.empty()){
        TreeNode* leftNode = s.top(); s.pop();
        TreeNode* rightNode = s.top(); s.pop();
        if(leftNode == nullptr && rightNode == nullptr) continue; 
        if(leftNode == nullptr || rightNode == nullptr || leftNode->val != rightNode->val) return false; 
        s.push(leftNode->right); 
        s.push(rightNode->left); 
        s.push(rightNode->right);
        s.push(leftNode->left);
    }
    return true;
}

//110. 平衡二叉树
//从顶至底 O(n^2) 需要多次重复计算高度
int getDepth(TreeNode* node){
    if(node == nullptr) return 0; 
    return max(getDepth(node->left), getDepth(node->right)) + 1;
}
bool isBalanced(TreeNode* root) {
    if(root == nullptr) return true; 
    int left = getDepth(root->left);
    int right = getDepth(root->right);
    return abs(left-right) <= 1 && isBalanced(root->left) && isBalanced(root->right);
}
//从底至顶 后序遍历
//后序遍历可得出高度（该节点到叶子节点的最长简单路径边的条数）
//前序遍历可得出深度（根节点到该节点的最长简单路径的条数）
int getDepth(TreeNode* curr) {
    if(curr == nullptr) return 0;
    int leftCount = getDepth(curr->left);
    if(leftCount < 0) return -1;
    int rightCount = getDepth(curr->right);
    if(rightCount < 0) return -1;
    if (abs(leftCount - rightCount) > 1){
        return -1;
    }
    return max(leftCount, rightCount) + 1;
} 
bool isBalanced(TreeNode* root) {
    if(root == nullptr) return true; 
    return getDepth(root) > 0;
}

//257. 二叉树的所有路径
//前序遍历
vector<string> binaryTreePaths(TreeNode* root) {
    vector<string> ans;
    if(root == nullptr) return ans;
    stack<TreeNode*> s; 
    s.push(root);
    stack<string> path;
    path.push(to_string(root->val));
    while(!s.empty()){
        TreeNode* curr = s.top(); s.pop(); 
        string p = path.top(); path.pop();
        if(curr->left == nullptr && curr->right == nullptr) {
            ans.push_back(p); 
        }
        if(curr->right){
            s.push(curr->right);
            path.push(p + "->" + to_string(curr->right->val));
        }
        if(curr->left){
            s.push(curr->left);
            path.push(p + "->" + to_string(curr->left->val));
        }
    }
    return ans;
}

// recursion too slow
bool isSameTree(TreeNode* p, TreeNode* q) {
    if(p == nullptr && q == nullptr) return true; 
    if(p == nullptr || q == nullptr) return false; 
    if(p->val != q->val) return false; 
    bool left = isSameTree(p->left, q->left);
    bool right = isSameTree(p->right, q->right);
    return left && right; 
}

//recursion easier than iteration 
class Solution {
public:
    vector<int> path; 
    vector<vector<int>> ans; 
    void dfs(TreeNode* curr, int count) {
        if(curr->left == nullptr && curr->right == nullptr){
            if(count == 0) {
                ans.push_back(path);
            }
            return; 
        }
        if(curr->right) {
            path.push_back(curr->right->val);
            count -= curr->right->val; 
            dfs(curr->right, count); 
            count += curr->right->val; 
            path.pop_back(); 
        }
        if(curr->left) {
            path.push_back(curr->left->val); 
            count -= curr->left->val; 
            dfs(curr->left, count);
            count += curr->left->val; 
            path.pop_back();
        }
    }
    vector<vector<int>> pathSum(TreeNode* root, int targetSum) {
        if(root == nullptr) return ans; 
        path.push_back(root->val);
        dfs(root, targetSum - root->val); 
        return ans;
    }
};


TreeNode* buildTree(vector<int>& inorder, vector<int>& postorder) {
    //空节点
    if(inorder.size() == 0) return nullptr;
    //找到后序遍历最后一位便是当前的node
    int rootValue = postorder[postorder.size() - 1];
    TreeNode* root = new TreeNode(rootValue);
    //如果当前node是叶子节点，则直接返回
    if(inorder.size() == 1) return root;
    //找到node在inorder中的index作为切割点
    auto it = find(inorder.begin(), inorder.end(), rootValue);
    int rootIndex = it - inorder.begin();
    postorder.resize(postorder.size() - 1);
    vector<int> left_inorder(inorder.begin(), inorder.begin() + rootIndex); 
    vector<int> left_postorder(postorder.begin(), postorder.begin() + left_inorder.size()); 
    vector<int> right_inorder(inorder.begin() + rootIndex + 1, inorder.end()); 
    vector<int> right_postorder(postorder.begin() + rootIndex, postorder.end()); 
    root->left = buildTree(left_inorder, left_postorder); 
    root->right = buildTree(right_inorder, right_postorder);
    return root;
}

//236. Lowest Common Ancestor of a Binary Tree
TreeNode* lowestCommonAncestor(TreeNode* root, TreeNode* p, TreeNode* q) {
    if(root == nullptr || root->val == p->val || root->val == q->val) return root; 
    TreeNode* left = lowestCommonAncestor(root->left, p, q); 
    TreeNode* right = lowestCommonAncestor(root->right, p, q);
    if(left != nullptr && right != nullptr) return root; 
    if(left == nullptr) return right; 
    return left;  
}

