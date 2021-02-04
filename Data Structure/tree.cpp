#include <vector>
#include <unordered_set>
#include <unordered_map>
#include <queue>
#include <stack>
#include "tree.h"

using namespace std;

TreeNode* createTree(vector<int> nodes) {
	vector<TreeNode*> tree;
	TreeNode* node;
	for (int i = 0; i < nodes.size(); i++) {
		if(nodes[i] == 65535) {
			node =nullptr;
		}
		else {
			node = new TreeNode(nodes[i]);
		}
		tree.push_back(node);
	}
	TreeNode* root = tree[0];
	for (int i = 0; i < tree.size(); i++) {
		int left = i * 2 + 1;
		int right = i * 2 + 2;
		if (tree[i]) {
			tree[i]->left = left < tree.size() ? tree[left] : nullptr;
			tree[i]->right = right < tree.size() ? tree[right] : nullptr;
		}
	}
	return root;
}

/// <summary>
/// 104. Maximum Depth of Binary Tree
/// </summary>
int maxDepth(TreeNode* root) {
	return  root ? ::max(maxDepth(root->left), maxDepth(root->right)) + 1 : 0;
}

/// <summary>
/// 110. Balanced Binary Tree
/// </summary>
int helper(TreeNode* root) {
	int left, right;
	if (!root) {
		return 0;
	}

	left = helper(root->left);
	right = helper(root->right);

	if (left == -1 || right == -1 || ::abs(left - right) > 1) {
		return -1;
	}
	return 1 + ::max(left, right);

}
bool isBalanced(TreeNode* root) {
	
	return helper(root) != -1;
}

/// <summary>
/// 543. Diameter of Binary Tree
/// </summary>
int max_diameter = 0;
int diameterHelper(TreeNode* root) {
	if (!root) {
		return 0;
	}
	int left = diameterHelper(root->left);
	int right = diameterHelper(root->right);
	max_diameter = ::max(max_diameter,left + right);
	return ::max(left, right) + 1;
}
int diameterOfBinaryTree(TreeNode* root) {
	diameterHelper(root);
	return max_diameter;
}


/// <summary>
/// 437. Path Sum III
/// </summary>
int sum_count = 0;;
void pathHelper(TreeNode* root, int sum ,vector<int> sum_list) {
	if (root) {
		sum_list.push_back(0);
		for (auto& s : sum_list) {
			s += root->val;
			if (s == sum) {
				sum_count++;
			}
		}
		pathHelper(root->left, sum, sum_list);
		pathHelper(root->right, sum, sum_list);
	}
}
int pathSum(TreeNode* root, int sum) {
	vector<int> sum_list;
	pathHelper(root, sum, sum_list);
	return sum_count;
}

/// <summary>
/// 1110. Delete Nodes And Return Forest
/// </summary>
vector<TreeNode*> forest;
TreeNode* delNodesHelper(TreeNode* root, unordered_set<int>& hash) {
	if (!root) {
		return root;
	}

	root->left = delNodesHelper(root->left, hash);
	root->right = delNodesHelper(root->right, hash);
	if (hash.count(root->val)) {
		if (root->left) {
			forest.push_back(root->left);
		}
		if (root->right) {
			forest.push_back(root->right);
		}
		root = nullptr;
	}
	return root;
}
vector<TreeNode*> delNodes(TreeNode* root, vector<int>& to_delete) {
	unordered_set<int> hash;
	for (auto& num : to_delete) {
		hash.insert(num);
	}
	root = delNodesHelper(root, hash);
	if (root) {
		forest.push_back(root);
	}
	return forest;
}


/// <summary>
/// 637. Average of Levels in Binary Tree
/// </summary>
vector<double> averageOfLevels(TreeNode* root) {
	queue<TreeNode*> q;
	vector<double> ans;
	
	if (!root) {
		return ans;
	}
	q.push(root);

	while (!q.empty()) {
		int level_size = q.size();
		double sum = 0;
		for (int i = 0; i < level_size; i++) {
			TreeNode* node;
			node = q.front();
			q.pop();
			sum += node->val;
			if (node->left)
				q.push(node->left);
			if (node->right)
				q.push(node->right);
		}
		ans.push_back(sum / level_size);
	}
	return ans;
}

/// <summary>
/// 105. Construct Binary Tree from Preorder and Inorder Traversal
/// </summary>
/// 
unordered_map<int, int> tree_hash;
TreeNode* buildTreeHelper(vector<int>& preorder, vector<int>& inorder,
	int preorder_left,int preorder_right,int inorder_left,int inorder_right) {

	if (preorder_left > preorder_right) {
		return nullptr;
	}

	int root_val = preorder[preorder_left];
	TreeNode* root = new TreeNode(root_val);
	int root_position = tree_hash[root_val];
	int left_len = root_position - inorder_left;

	root->left = buildTreeHelper(preorder, inorder, preorder_left + 1, preorder_left + left_len, inorder_left, root_position - 1);
	root->right = buildTreeHelper(preorder, inorder, preorder_left + left_len + 1, preorder_right, root_position + 1, inorder_right);
	return root;
}
TreeNode* buildTree(vector<int>& preorder, vector<int>& inorder) {
	for (int i = 0; i < inorder.size(); i++) {
		tree_hash[inorder[i]] = i;
	}
	return buildTreeHelper( preorder, inorder,0, preorder.size() - 1, 0, inorder.size());
}

/// <summary>
/// 144. Binary Tree Preorder Traversal
/// </summary>
vector<int> ans;
void preorderTraversalHelper(TreeNode* root) {
	if (root) {
		ans.push_back(root->val);
		preorderTraversalHelper(root->left);
		preorderTraversalHelper(root->right);
	}
}
vector<int> preorderTraversal(TreeNode* root) {
	preorderTraversalHelper(root);
	return ans;
}

/// <summary>
/// 99. Recover Binary Search Tree
/// </summary>
void recoverTreeHelper(TreeNode* root, TreeNode*& mistake1, TreeNode*& mistake2, TreeNode*& prev) {
	if (root) {
		recoverTreeHelper(root->left, mistake1, mistake2, prev);
		if (prev && prev->val > root->val) {
			if (!mistake1) {
				mistake1 = prev;
				mistake2 = root;
			}
			else {
				mistake2 = root;
			}
		}
		prev = root;
		
		recoverTreeHelper(root->right, mistake1, mistake2, prev);

	}
}
void recoverTree(TreeNode* root) {
	/* 二叉搜索树，中序遍历为从小到大排序*/
	TreeNode* mistake1 = nullptr;
	TreeNode* mistake2 = nullptr;
	TreeNode* prev = nullptr;
	/* prev 记录节点中序遍历的前一个节点 */
	recoverTreeHelper(root, mistake1, mistake2, prev);
	if (mistake1 && mistake2) {
		int temp = mistake1->val;
		mistake1->val = mistake2->val;
		mistake2->val = temp;
	}
}

/// <summary>
/// 669. Trim a Binary Search Tree
/// </summary>
TreeNode* trimBST(TreeNode* root, int low, int high) {
	if (!root)
		return root;
	if (root->left && root->left->val > high)
		return trimBST(root->left, low, high);
	if (root->right && root->right->val < low)
		return trimBST(root->right, low, high);
	root->left = trimBST(root->left, low, high);
	root->right = trimBST(root->right, low, high);
	return root;
}

/// <summary>
/// 208. Implement Trie (Prefix Tree)
/// </summary>
class Trie {
	class TrieNode {
	public:
		bool is_end;
		TrieNode* next[26];
		TrieNode() {
			is_end = false;
			for (int i = 0; i < 26; i++) {
				next[i] = nullptr;
			}
		}
		~TrieNode() {
			for (int i = 0; i < 26; i++) {
				if (!next[i]) {
					delete next[i];
				}
			}
		}
	};
	TrieNode root_;
public:
	/** Initialize your data structure here. */
	Trie() {
	}

	/** Inserts a word into the trie. */
	void insert(string word) {
		TrieNode* node = &root_;
		for (char c : word) {
			if (!node->next[c - 'a']) {
				node->next[c - 'a'] = new TrieNode;
			}
			node = node->next[c - 'a'];
		}
		node->is_end = true;
	}

	/** Returns if the word is in the trie. */
	bool search(string word) {
		TrieNode* node = &root_;
		for (char c : word) {
			if (!node->next[c - 'a']) {
				return false;
			}
			node = node->next[c - 'a'];
		}
		return node->is_end == true;
	}

	/** Returns if there is any word in the trie that starts with the given prefix. */
	bool startsWith(string prefix) {
		TrieNode* node = &root_;
		for (char c : prefix) {
			if (!node->next[c - 'a']) {
				return false;
			}
			node = node->next[c - 'a'];
		}
		return true;
	}
};

/// <summary>
/// 226. Invert Binary Tree
/// </summary>
TreeNode* invertTree(TreeNode* root) {
	if (!root) {
		return root;
	}
	TreeNode* left = root->left;
	root->left = invertTree(root->right);
	root->right = invertTree(left);
	return root;
}

/// <summary>
/// 617. Merge Two Binary Trees
/// </summary>
TreeNode* mergeTrees(TreeNode* t1, TreeNode* t2) {
	TreeNode* root = nullptr;
	if (!t1 && !t2) {
		return nullptr;
	}

	if (t1 && !t2) {
		return t1;
	}
	if (t2 && !t1) {
		return t2;
	}

	root = new TreeNode(0);
	root->val = t1->val + t2->val;
	root->left = mergeTrees(t1->left, t2->left);
	root->right = mergeTrees(t1->right, t2->right);
	return root;
}

/// <summary>
/// 572. Subtree of Another Tree
/// </summary>
bool IsSame(TreeNode* t1, TreeNode* t2) {
	if (!t1 && !t2) {
		return true;
	}
	if (t1 && !t2) {
		return false;
	}
	if (t2 && !t1) {
		return false;
	}

	if (t1->val != t2->val) {
		return false;
	}

	return IsSame(t1->left, t2->left) && IsSame(t1->right, t2->right);
	
}
bool isSubtree(TreeNode* s, TreeNode* t) {
	if (!t) {
		return true;
	}

	if (!s) {
		return false;
	}
	if (IsSame(s, t)) {
		return true;
	}
	
	return isSubtree(s->left, t) || isSubtree(s->right, t);
}

/// <summary>
/// 404. Sum of Left Leaves
/// </summary>
int sumOfLeftLeavesHelper(TreeNode* root,bool is_left) {
	int sum = 0;
	if (!root) {
		return sum;
	}
	if (is_left && !root->left && !root->right) {
		sum += root->val;
	}
	sum += sumOfLeftLeavesHelper(root->left,true);
	sum += sumOfLeftLeavesHelper(root->right,false);
	return sum;
}
int sumOfLeftLeaves(TreeNode* root) {
	return sumOfLeftLeavesHelper(root, false);
}

/// <summary>
/// 513. Find Bottom Left Tree Value
/// </summary>
int depth(TreeNode* root) {
	if (!root) {
		return 0;
	}
	return ::max(depth(root->left), depth(root->right)) + 1;
}
int findBottomLeftValue(TreeNode* root) {
	TreeNode* p = root;
	int left_depth, right_depth;
	while (p->left || p->right) {
		left_depth = depth(p->left);
		right_depth = depth(p->right);
		p = (left_depth >= right_depth ? p->left : p->right);
	}
	return p->val;
}

/// <summary>
/// 235. Lowest Common Ancestor of a Binary Search Tree
/// </summary>
TreeNode* lowestCommonAncestor(TreeNode* root, TreeNode* p, TreeNode* q) {
	int biger, smaller;
	if (p->val > q->val) {
		biger = p->val;
		smaller = q->val;
	}
	else {
		biger = q->val;
		smaller = p->val;
	}

	if (root->val < smaller) {
		return lowestCommonAncestor(root->right, p, q);
	}

	if (root->val > biger) {
		return lowestCommonAncestor(root->left, p, q);
	}
	return root;
}

/// <summary>
/// 530. Minimum Absolute Difference in BST
/// </summary>
int difference = INT_MAX;
void getMinimumDifferenceHelper(TreeNode* root, TreeNode*& prev) {
	if (!root) {
		return;
	}
	getMinimumDifferenceHelper(root->left, prev);
	if (prev) {
		difference = ::min(difference, root->val - prev->val);
	}
	prev = root;
	getMinimumDifferenceHelper(root->right, prev);
}
int getMinimumDifference(TreeNode* root) {
	TreeNode* prev = nullptr;
	getMinimumDifferenceHelper(root, prev);
	return difference == INT_MAX ? 0 : difference;

}

/// <summary>
/// 538. Convert BST to Greater Tree
/// </summary>
void convertBSThelper(TreeNode* root, TreeNode*& prev) {
	if (!root) {
		return;
	}
	convertBSThelper(root->right, prev);
	if (prev) {
		root->val = root->val + prev->val;
	}
	prev = root;
	convertBSThelper(root->left, prev);
}
TreeNode* convertBST(TreeNode* root) {
	TreeNode* prev = nullptr;
	convertBSThelper(root, prev);
	return root;
}

/// <summary>
/// 897. Increasing Order Search Tree
/// </summary>
void increasingBSTHelper(TreeNode* root, TreeNode*& prev) {
	if (!root) {
		return;
	}
	increasingBSTHelper(root->left, prev);
	if (prev) {
		prev->left = nullptr;
		prev->right = root;
	}
	prev = root;
	increasingBSTHelper(root->right, prev);
}
TreeNode* increasingBST(TreeNode* root) {
	TreeNode* new_root = root;
	while (new_root->left) {
		new_root = new_root->left;
	}

	TreeNode* prev = nullptr;
	increasingBSTHelper(root, prev);
	prev->left = nullptr;
	return new_root;
}

/// <summary>
/// 653. Two Sum IV - Input is a BST
/// </summary>
bool findTargetHelper(unordered_set<int>& hash, TreeNode* root, int k) {
	if (!root) {
		return false;
	}
	if (hash.count(k - root->val)) {
		return true;
	}
	hash.insert(root->val);
	return findTargetHelper(hash, root->left, k) || findTargetHelper(hash, root->right, k);
}
bool findTarget(TreeNode* root, int k) {
	unordered_set<int> hash;
	return findTargetHelper(hash, root, k);
}


/// <summary>
/// 889. Construct Binary Tree from Preorder and Postorder Traversal
/// </summary>
unordered_map<int, int> pre_hash;
TreeNode* constructFromPrePostHelper(vector<int>& pre, vector<int>& post,
	int pre_left, int pre_right, int post_left, int post_right) {
	if (pre_left > pre_right) {
		return nullptr;
	}
	if (pre_left == pre_right) {
		TreeNode* root = new TreeNode;
		root->val = pre[pre_left];
		return root;
	}
	
	TreeNode* root = new TreeNode;
	root->val = pre[pre_left];
	int right_tree_index = pre_hash[post[post_left + 1]];
	int right_tree_length = pre_right - right_tree_index + 1;

	root->left = constructFromPrePostHelper(pre,post, pre_left + 1, right_tree_index - 1, post_left + right_tree_length + 1 , post_right);
	root->right = constructFromPrePostHelper(pre,post, right_tree_index, pre_right, post_left +1, post_left + right_tree_length);
	return root;
}
TreeNode* constructFromPrePost(vector<int>& pre, vector<int>& post) {
	::reverse(post.begin(), post.end());
	for (int i = 0; i < pre.size(); i++) {
		pre_hash[pre[i]] = i;
	}
	return constructFromPrePostHelper(pre, post, 0, pre.size() - 1, 0, post.size() - 1);
}

/// <summary>
/// 106. Construct Binary Tree from Inorder and Postorder Traversal
/// </summary>
unordered_map<int, int> in_hash;
TreeNode* buildTreeHelper1(vector<int>& inorder, vector<int>& postorder,int l_inorder,int r_inorder,int l_postorder,int r_postorder) {
	if (l_inorder > r_inorder) {
		return nullptr;
	}
	TreeNode* root = new TreeNode;
	root->val = postorder[l_postorder];
	int root_index = in_hash[root->val];
	int right_tree_length = r_inorder - root_index;

	root->left = buildTreeHelper1(inorder, postorder, l_inorder, root_index - 1, l_postorder + right_tree_length + 1, r_postorder);
	root->right = buildTreeHelper1(inorder, postorder, root_index + 1, r_inorder, l_postorder + 1, l_postorder + right_tree_length);
	return root;
}
TreeNode* buildTree2(vector<int>& inorder, vector<int>& postorder) {
	::reverse(postorder.begin(), postorder.end());
	for (int i = 0; i < inorder.size(); i++) {
		in_hash[inorder[i]] = i;
	}
	return buildTreeHelper1(inorder, postorder, 0, inorder.size() - 1, 0, postorder.size() - 1);
}

/// <summary>
/// 94. Binary Tree Inorder Traversal
/// </summary>
vector<int> inorderTraversal(TreeNode* root) {
	vector<int> ans;
	stack<TreeNode*> s;
	TreeNode* p = root;

	while (p || !s.empty()) {
		while (p) {
			s.push(p);
			p = p->left;
		}

		p = s.top();
		s.pop();
		ans.push_back(p->val);
		p = p->right;
	}
	return ans;
}

/// <summary>
/// 145. Binary Tree Postorder Traversal
/// </summary>
vector<int> postorderTraversal(TreeNode* root) {
	stack<TreeNode*> s;
	vector<int> ans;

	if (!root) {
		return ans;
	}
	s.push(root);
	while (!s.empty()) {
		TreeNode* node = s.top();
		s.pop();
		if (node) {
			s.push(node);
			s.push(nullptr);  //标记需要输出的node
			if (node->right)s.push(node->right);
			if (node->left)s.push(node->left);
		}
		else {
			TreeNode* node = s.top();
			s.pop();
			ans.push_back(node->val);
		}
	}
	return ans;
}

/// <summary>
/// 236. Lowest Common Ancestor of a Binary Tree
/// </summary>
TreeNode* target;
bool isSonNode(TreeNode* root, TreeNode* p, TreeNode* q) {
	if (!root) {
		return false;
	}

	bool lson = isSonNode(root->left, p, q);
	bool rson = isSonNode(root->right, p, q);

	if ((lson && rson) || ((root->val == p->val || root->val == q->val) && (lson || rson))) {
		target = root;
	}

	return lson || rson || root->val == p->val || root->val == q->val;
}
TreeNode* lowestCommonAncestor2(TreeNode* root, TreeNode* p, TreeNode* q) {
	isSonNode(root, p, q);
	return target;
}

/// <summary>
/// 109. Convert Sorted List to Binary Search Tree
/// </summary>
ListNode* FindMiddleNode(ListNode* head, ListNode* tail) {
	ListNode* slow, *fast;
	slow = fast = head;
	while (fast != tail && fast->next != tail) {
		slow = slow->next;
		fast = fast->next->next;
	}
	return slow;
}
TreeNode* sortedListToBSTHelper(ListNode* head, ListNode* tail) {
	if (head == tail) {
		return nullptr;
	}

	ListNode* mid = FindMiddleNode(head, tail);
	TreeNode* root = new TreeNode(mid->val);
	root->left = sortedListToBSTHelper(head, mid);
	root->right = sortedListToBSTHelper(mid->next, tail);
	return root;
}
TreeNode* sortedListToBST(ListNode* head) {
	return sortedListToBSTHelper(head, nullptr);
}

/// <summary>
/// 450. Delete Node in a BST
/// </summary>
TreeNode* findKey(TreeNode* root, int key, TreeNode*& prev) {
	TreeNode* p = root;
	while (p) {
		if (p->val == key) {
			return p;
		}
		else if (key < p->val) {
			prev = p;
			p = p->left;
		}
		else if (key > p->val) {
			prev = p;
			p = p->right;
		}
	}
	return nullptr;
}
TreeNode* findNext(TreeNode* root, TreeNode*& prev) {
	while (root ->left) {
		prev = root;
		root = root->left;
	}
	return root;
}
void transplant(TreeNode* target, TreeNode* prev, TreeNode* source) {
	if (prev->left == target) {
		prev->left = source;
	}
	else {
		prev->right = source;
	}
}
TreeNode* deleteNode(TreeNode* root, int key) {
	TreeNode* dummy = new TreeNode;
	dummy->left = root;

	TreeNode* prev = dummy;
	TreeNode* target = findKey(root, key, prev);
	if (!target) {
		return root;
	}

	if (!target->left) {
		transplant(target, prev, target->right);
	}
	else if (!target->right) {
		transplant(target, prev, target->left);
	}
	else {
		TreeNode* prev2 = target;
		TreeNode* next = findNext(target->right, prev2);
		if (prev2 != target) {
			transplant(next, prev2, next->right);
			next->right = target->right;
		}
		transplant(target, prev, next);
		next->left = target->left;
	}

	return dummy->left;
}