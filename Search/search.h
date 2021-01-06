#pragma once
#include <vector>
#include <string>
using namespace std;
// 二分查找
int mySqrt(int x);											//69. Sqrt(x)
vector<int> searchRange(vector<int>& nums, int target);		//34. Find First and Last Position of Element in Sorted Array
vector<int> searchRangeSTL(vector<int>& nums, int target);	//34.
bool search(vector<int>& nums, int target);					//81. Search in Rotated Sorted Array II
int findMin(vector<int>& nums);								//154. Find Minimum in Rotated Sorted Array II
int findMin2(vector<int>& nums);							//154. Find Minimum in Rotated Sorted Array II
int singleNonDuplicate(vector<int>& nums);					//540. Single Element in a Sorted Array
double findMedianSortedArrays(vector<int>& nums1, vector<int>& nums2); //4. Median of Two Sorted Arrays

// DFS
int maxAreaOfIsland(vector<vector<int>>& grid);						//695. Max Area of Island
int findCircleNum(vector<vector<int>>& isConnected);				//547. Number of Provinces
int findCircleNumByUnionFind(vector<vector<int>>& isConnected);		//547. Number of Provinces
vector<vector<int>> pacificAtlantic(vector<vector<int>>& matrix);	//417. Pacific Atlantic Water Flow

// 回溯算法
bool exist(vector<vector<char>>& board, string word);				//79. Word Search
vector<vector<int>> combine(int n, int k);							//77. Combinations
vector<vector<int>> permute(vector<int>& nums);						//46. Permutations
vector<vector<string>> solveNQueens(int n);							//51. N-Queens