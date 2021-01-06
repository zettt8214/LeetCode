#pragma once
#include <vector>
using namespace std;
// BINSEARCH
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