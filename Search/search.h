#pragma once
#include <vector>
#include <string>
using namespace std;

typedef struct TreeNode { ///< 257. Binary Tree Paths 
	int val;
	TreeNode* left;
	TreeNode* right;
	TreeNode(int x, TreeNode* l = NULL, TreeNode* r = NULL) : val(x), left(l), right(r) {}
}TreeNode;

// binsearch
int MySqrt(int x);											//69. Sqrt(x)
vector<int> searchRange(vector<int>& nums, int target);		//34. Find First and Last Position of Element in Sorted Array
vector<int> searchRangeSTL(vector<int>& nums, int target);	//34.
bool search(vector<int>& nums, int target);					//81. Search in Rotated Sorted Array II
int findMin(vector<int>& nums);								//154. Find Minimum in Rotated Sorted Array II
int findMin2(vector<int>& nums);							//154. Find Minimum in Rotated Sorted Array II
int singleNonDuplicate(vector<int>& nums);					//540. Single Element in a Sorted Array
double findMedianSortedArrays(vector<int>& nums1, vector<int>& nums2); //4. Median of Two Sorted Arrays

// DFS BFS traceback
int maxAreaOfIsland(vector<vector<int>>& grid);						//695. Max Area of Island
int findCircleNum(vector<vector<int>>& isConnected);				//547. Number of Provinces
int findCircleNumByUnionFind(vector<vector<int>>& isConnected);		//547. Number of Provinces
vector<vector<int>> pacificAtlantic(vector<vector<int>>& matrix);	//417. Pacific Atlantic Water Flow

bool exist(vector<vector<char>>& board, string word);		//79. Word Search
vector<vector<int>> combine(int n, int k);					//77. Combinations
vector<vector<int>> permute(vector<int>& nums);				//46. Permutations
vector<vector<string>> solveNQueens(int n);					//51. N-Queens
int shortestBridge(vector<vector<int>>& A);					//934. Shortest Bridge
vector<vector<string>> findLadders(string beginWord, string endWord, vector<string>& wordList);				//126. Word Ladder II
vector<vector<string>> findLaddersByTwoWayBfs(string beginWord, string endWord, vector<string>& wordList);	//126. Word Ladder II
void solve(vector<vector<char>>& board);									//130. Surrounded Regions
vector<string> binaryTreePaths(TreeNode* root);								//257. Binary Tree Paths
vector<vector<int>> permuteUnique(vector<int>& nums);						//47 Permutations II
vector<vector<int>> combinationSum2(vector<int>& candidates, int target);	//40. Combination Sum II
vector<int> findMinHeightTrees(int n, vector<vector<int>>& edges);			//310. Minimum Height Trees
void solveSudoku(vector<vector<char>>& board);								//37. Sudoku Solver

