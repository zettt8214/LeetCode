#pragma once
#include <iostream>
#include <vector>
#include "list.h"
using std::vector;

struct TreeNode {
	int val;
	TreeNode* left;
	TreeNode* right;
	TreeNode() : val(0), left(nullptr), right(nullptr) {}
	TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
	TreeNode(int x, TreeNode* left, TreeNode* right) : val(x), left(left), right(right) {}
};
TreeNode* createTree(vector<int> nodes);

int maxDepth(TreeNode* root);												/// 104. Maximum Depth of Binary Tree
bool isBalanced(TreeNode* root);											/// 110. Balanced Binary Tree
int diameterOfBinaryTree(TreeNode* root);									/// 543. Diameter of Binary Tree
int pathSum(TreeNode* root, int sum);										/// 437. Path Sum III
vector<TreeNode*> delNodes(TreeNode* root, vector<int>& to_delete);			/// 1110. Delete Nodes And Return Forest
vector<double> averageOfLevels(TreeNode* root);								/// 637. Average of Levels in Binary Tree
TreeNode* buildTree(vector<int>& preorder, vector<int>& inorder);			/// 105. Construct Binary Tree from Preorder and Inorder Traversal
vector<int> preorderTraversal(TreeNode* root);								/// 144. Binary Tree Preorder Traversal
void recoverTree(TreeNode* root);											/// 99. Recover Binary Search Tree
TreeNode* trimBST(TreeNode* root, int low, int high);						/// 669. Trim a Binary Search Tree
TreeNode* invertTree(TreeNode* root);										/// 226. Invert Binary Tree
TreeNode* mergeTrees(TreeNode* t1, TreeNode* t2);							/// 617. Merge Two Binary Trees
bool isSubtree(TreeNode* s, TreeNode* t);									/// 572. Subtree of Another Tree
int sumOfLeftLeaves(TreeNode* root);										/// 404. Sum of Left Leaves
int findBottomLeftValue(TreeNode* root);									/// 513. Find Bottom Left Tree Value
TreeNode* lowestCommonAncestor(TreeNode* root, TreeNode* p, TreeNode* q);	/// 235. Lowest Common Ancestor of a Binary Search Tree
int getMinimumDifference(TreeNode* root);									/// 530. Minimum Absolute Difference in BST
TreeNode* convertBST(TreeNode* root);										/// 538. Convert BST to Greater Tree
TreeNode* increasingBST(TreeNode* root);									/// 897. Increasing Order Search Tree
bool findTarget(TreeNode* root, int k);										/// 653. Two Sum IV - Input is a BST
TreeNode* constructFromPrePost(vector<int>& pre, vector<int>& post);		/// 889. Construct Binary Tree from Preorder and Postorder Traversal
TreeNode* buildTree2(vector<int>& inorder, vector<int>& postorder);			/// 106. Construct Binary Tree from Inorder and Postorder Traversal
vector<int> inorderTraversal(TreeNode* root);								/// 94. Binary Tree Inorder Traversal
vector<int> postorderTraversal(TreeNode* root);								/// 145. Binary Tree Postorder Traversal
TreeNode* lowestCommonAncestor2(TreeNode* root, TreeNode* p, TreeNode* q);	/// 236. Lowest Common Ancestor of a Binary Tree
TreeNode* sortedListToBST(ListNode* head);									/// 109. Convert Sorted List to Binary Search Tree
TreeNode* deleteNode(TreeNode* root, int key);								/// 450. Delete Node in a BST