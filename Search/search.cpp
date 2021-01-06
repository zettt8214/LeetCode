#include <iostream>
#include <iterator>
#include <algorithm>
#include <vector>
#include <stack>
#include <set>
using namespace std;

/*************************************************************************
* 69.Sqrt(x)
* 
* Given a non-negative integer x, compute and return the square root of x.
* 
* Since the return type is an integer, the decimal digits are truncated, 
* and only the integer part of the result is returned.
* 
***************************************************************************/
int MySqrt(int x) {
	int l = 0, r = x, ans = -1;
	int mid;
	while (r >= l) {
		mid = l + (r - l) / 2;
		if ((long long)mid * mid <= x) {
			ans = mid;
			l = mid + 1;
		}
		else {
			r = mid - 1;
		}
	}
	return ans;
}

/***************************************************************************
* 34. Find First and Last Position of Element in Sorted Array
* 
* Given an array of integers nums sorted in ascending order,
* find the starting and ending position of a given target value.
* 
* If target is not found in the array, return [-1, -1].
* 
* Follow up: Could you write an algorithm with O(log n) runtime complexity?
*****************************************************************************/
int findFirstPosition(vector<int>& nums, int target) {
	int left = 0, right = nums.size() - 1;
	int mid;
	while (left < right) {
		//出循环时left = right
		mid = (left + right) >> 1;
		if (nums[mid] < target) {
			//搜索[mid + 1,right]区间
			left = mid + 1;
		}
		else if (nums[mid] == target) {
			//搜索[left,mid]区间
			right = mid;
		}
		else {
			//搜索[left,mid - 1]区间
			right = mid - 1;
		}
	}
	if (nums[left] != target) {
		//未找到目标
		return -1;
	}
	return left;
} 
int findLastPosition(vector<int>& nums, int target) {
	int left = 0, right = nums.size() - 1;
	int mid;
	while (left < right) {
		//出循环时left = right
		mid = (left + right + 1) >> 1; //选取偏右元素做中间元素，防止进入死循环
		if (nums[mid] < target) {
			//搜索[mid + 1,right]区间
			left = mid + 1;
		}
		else if (nums[mid] == target) {
			//搜索[left,mid]区间
			left = mid;
		}
		else {
			//搜索[left,mid - 1]区间
			right = mid - 1;
		}
	}
	return right;
}
vector<int> searchRange(vector<int>& nums, int target) {
	if (nums.empty()) {
		return vector<int>{ -1,-1 };
	}

	int left = findFirstPosition(nums,target);
	if (left == -1) {
		return vector<int>{ -1, -1 };
	}

	int right = findLastPosition(nums, target);
	return vector<int>{left, right};
}
vector<int> searchRangeSTL(vector<int>& nums, int target) {
	auto liter = lower_bound(nums.begin(), nums.end(), target); //寻找第一个不小于target
	auto riter = upper_bound(nums.begin(), nums.end(), target); //寻找第一个大于target
	if (liter == nums.end() || *liter != target) {
		return vector<int>{-1, -1};
	}
	return vector<int>{distance(nums.begin(),liter), distance(nums.begin(),riter) - 1};

}

/*********************************************************************************************
* 81. Search in Rotated Sorted Array II
* 
* Suppose an array sorted in ascending order is rotated 
* at some pivot unknown to you beforehand.
* (i.e., [0,0,1,2,2,5,6] might become [2,5,6,0,0,1,2]).
* You are given a target value to search. If found in the array return true, 
* otherwise return false.
*********************************************************************************/
bool search(vector<int>& nums, int target) {
	int left = 0, right = nums.size() - 1;
	int mid;
	while (left <= right) {
		mid = (left + right) >> 1;
		if (nums[mid] == target) {
			return true;
		}
		if (nums[left] < nums[mid]) {
			//左区间递增
			if (nums[mid] > target && nums[left] <= target) {
				//target在左区间范围
				right = mid - 1;
			}
			else {
				//target不在左区间范围
				left = mid + 1;
			}
		}
		else if(nums[left] > nums[mid]){
			//右区间递增
			if (target > nums[mid] && target <= nums[right]) {
				//target在右区间范围
				left = mid + 1;
			}
			else {
				//target不在右区间范围
				right = mid - 1;
			}
		}
		else {
			left++;
			continue;
		}
	}
	return false;
}

/**********************************************************
* 154. Find Minimum in Rotated Sorted Array II
* 
* Suppose an array sorted in ascending order is rotated at 
* some pivot unknown to you beforehand.
* (i.e.,  [0,1,2,4,5,6,7] might become  [4,5,6,7,0,1,2]).
* 
*	Find the minimum element.
* 	The array may contain duplicates.
************************************************************/
int findMin(vector<int>& nums) {
	int ans = INT_MAX;
	int left = 0, right = nums.size() - 1;
	int mid;
	while (left <= right) {
		mid = (left + right) >> 1;
		if (nums[left] == nums[mid]) {
			if (nums[mid] < ans)
				ans = nums[mid];
			left++;
			continue;
		}
		else if (nums[left] < nums[mid]) {
			//左区间递增，左区间最小值为nums[left]
			if (nums[left] < ans) {
				ans = nums[left];
			}
			//搜索剩余区间
			left = mid + 1;
		}
		else {
			//右区间递增,右区间最小值为nums[mid]
			if (nums[mid] < ans) {
				ans = nums[mid];
			}
			//搜索剩余区间
			right = mid - 1;
		}

	}
	return ans;
}
//method 2
int findMin2(vector<int>& nums) {
	int left = 0, right = nums.size() - 1;
	int mid;
	while (left < right) {
		mid = (left + right) / 2; 
		if (nums[mid] == nums[right]) {
			right--;
			continue;
		}
		else if(nums[mid] < nums[right]){
			right = mid;
		}
		else {
			left = mid + 1;
		}
	}
	return nums[left];
}

/***********************************************************************
* 540. Single Element in a Sorted Array
* 
* You are given a sorted array consisting of only integers where every 
* element appears exactly twice, except for one element which appears 
* exactly once. Find this single element that appears only once.

Follow up: Your solution should run in O(log n) time and O(1) space.
************************************************************************/
int singleNonDuplicate(vector<int>& nums) {
	int left = 0, right = nums.size() - 1;
	int mid;
	while (left < right) {
		mid = (left + right) >> 1;
		if (mid % 2 == 0) {
			if (nums[mid + 1] == nums[mid]) {	//finally, left = mid < right
				left = mid + 1;
			}
			else {
				right = mid;
			}
		}
		else {
			if (nums[mid - 1] == nums[mid]) {	//mid % 2 = 1,mid != 0;
				left = mid + 1;
			}
			else {
				right = mid;
			}
		}
	}
	return nums[left];
}


/**********************************************************************
* 4. Median of Two Sorted Arrays
* 
* Given two sorted arrays nums1 and nums2 of size m and n respectively, 
* return the median of the two sorted arrays.
* Follow up : The overall run time complexity should be O(log(m + n)).
*	Solution:
*		find the Kth samllest element, compare the k/2 element of two arrays
***********************************************************************/
int getKthElement(const vector<int>& nums1, const vector<int>& nums2, int k) {
	int m = nums1.size();
	int n = nums2.size();
	int index1 = 0, index2 = 0;

	while (true) {
		if (index1 == m) {
			return nums2[index2 + k - 1];
		}
		if (index2 == n) {
			return nums1[index1 + k - 1];
		}
		if (k == 1) {
			return min(nums2[index2], nums1[index1]);
		}

		int newIndex1 = min(m - 1,index1 + k / 2 -1 );
		int newIndex2 = min(n - 1, index2 + k / 2 -1);
		if (nums1[newIndex1] <= nums2[newIndex2]) {
			//delete  the element2 before newIndex1;
			k = k - (newIndex1 - index1 + 1);
			index1 = newIndex1 + 1;
		}
		else {
			k = k - (newIndex2 - index2 + 1);
			index2 = newIndex2 + 1;
		}
	}
}
double findMedianSortedArrays(vector<int>& nums1, vector<int>& nums2) {
	int m = nums1.size();
	int n = nums2.size();
	int flag = (m + n) % 2 == 0 ? 1 : 0;
	if (flag) {
		return (double)(getKthElement(nums1, nums2, (m + n ) / 2) + getKthElement(nums1, nums2, (m + n) / 2 + 1)) / 2;
	}
	else {
		return getKthElement(nums1, nums2, (m + n + 1) / 2);
	}
}


// DFS
/**
* @brief	695. Max Area of Island
* @detail	Given a non-empty 2D array grid of 0's and 1's, 
*			an island is a group of 1's (representing land) connected 4-directionally (horizontal or vertical.) 
*			You may assume all four edges of the grid are surrounded by water.
*			Find the maximum area of an island in the given 2D array. (If there is no island, the maximum area is 0.)
*/
int DfsHelper(int i,int j, vector<vector<bool>>& is_visited, vector<vector<int>>& grid) {
	int rows = grid.size();
	int column = grid[0].size();
	is_visited[i][j] = true;

	if (grid[i][j] != 1) {
		return 0;
	}
	int area = 1;
	if (i < rows - 1 && !is_visited[i + 1][j])
		area += DfsHelper( i + 1, j, is_visited, grid);

	if (i > 0 && !is_visited[i - 1][j])
		area += DfsHelper(i - 1, j, is_visited, grid);

	if (j < rows - 1 && !is_visited[i][j + 1])
		area += DfsHelper( i, j + 1, is_visited, grid);

	if (j > 0 && !is_visited[i][j - 1])
		area += DfsHelper(i, j - 1, is_visited, grid);

	return area;

}
int maxAreaOfIsland(vector<vector<int>>& grid) {
	int rows = grid.size();
	int column = grid[0].size();
	vector<vector<bool>> is_visited(rows,
		vector<bool>(column,false));
	
	int max_area = 0;
	for (int i = 0; i < rows; i++) {
		for (int j = 0; j < column; j++) {
			if (!is_visited[i][j]) {
				int area = DfsHelper(i, j, is_visited, grid);
				max_area = max(area, max_area);
			}
		}
	}
	return max_area;
}

/*
* @brief	547. Number of Provinces
* @detail	There are n cities. Some of them are connected, while some are not. 
*			If city a is connected directly with city b, and city b is connected directly with city c, 
*			then city a is connected indirectly with city c.
*			A province is a group of directly or indirectly connected cities and no other cities outside of the group.
*			You are given an n x n matrix isConnected where isConnected[i][j] = 1 
*			if the ith city and the jth city are directly connected, and isConnected[i][j] = 0 otherwise.
*			Return the total number of provinces.
*/

int findCircleNum(vector<vector<int>>& isConnected) {
	int city_nums = isConnected.size();
	vector<bool> is_visited(city_nums,false);

	int provice_nums = 0;
	for (int i = 0; i < city_nums; i++) {
		if (!is_visited[i]) {
			is_visited[i] = true;
			provice_nums++;
			stack<int> connected_city;
			connected_city.push(i);
			while (!connected_city.empty()) {
				int city = connected_city.top();
				connected_city.pop();
				for (int j = 0; j < city_nums; j++) {		//	找邻接城市
					if (j != city && isConnected[city][j] == 1 && !is_visited[j]) {
						is_visited[j] = true;
						connected_city.push(j);

					}
				}
				
			}
			
		}
	}
	return provice_nums;
}

typedef struct City {
	int parent;
	int rank;
}City;

int FindSet(vector<City>& cities,int city) {
	if (cities[city].parent != city) {
		cities[city].parent = FindSet(cities, cities[city].parent);		//路径压缩，将根节点做为集合代表
	}
	return cities[city].parent;
}
void UnionSet(vector<City>& cities,int city1,int city2) {
	int root1 = FindSet(cities, city1);
	int root2 = FindSet(cities, city2);
	if (cities[root1].rank > cities[root2].rank) {
		cities[root2].parent = root1;
	}
	else {
		cities[root1].parent = root2;
		if (cities[root1].rank == cities[root2].rank) {
			cities[root2].rank++;
		}
	}
}
int findCircleNumByUnionFind(vector<vector<int>>& isConnected){
	int city_nums = isConnected.size();
	vector<City> cities(city_nums);
	for (int i = 0; i < city_nums;i++) {	//设置集合
		cities[i].parent = i;
		cities[i].rank = 0;
	}
	int privonces = city_nums;
	for (int i = 0; i < city_nums; i++) {
		for (int j = 0; j < city_nums; j++) {
			if (i != j &&isConnected[i][j] == 1 ) {
				if (FindSet(cities, i) != FindSet(cities, j)) {
					UnionSet(cities, i, j);
					privonces--;
				}
					


			}
		}
	}
	
	return privonces;
}

/**
* @brief	417. Pacific Atlantic Water Flow
* @detail	Given an m x n matrix of non-negative integers representing the height 
*			of each unit cell in a continent, the "Pacific ocean" touches the left 
*			and top edges of the matrix and the "Atlantic ocean" touches the right and bottom edges.
*
*			Water can only flow in four directions (up, down, left, or right) 
*			from a cell to another one with height equal or lower.
*
*			Find the list of grid coordinates where water can flow to both the Pacific and Atlantic ocean.
* 
* @note:	The order of returned grid coordinates does not matter.
*			Both m and n are less than 150.
*/



void DfsHelper(vector<vector<int>>& matrix, int abscissa, int ordinate, vector<vector<bool>>& can_arrive) {
	int row = matrix.size();
	int column = matrix[0].size();
	can_arrive[abscissa][ordinate] = true;

	
	int direction[4][2] = { {1,0},{-1,0},{0,1},{0,-1} };
	for (int i = 0; i < 4; i++) {
		int next_abscissa = abscissa + direction[i][0];
		int next_ordinate = ordinate + direction[i][1];
		if (next_abscissa >= 0 && next_abscissa < row && next_ordinate >= 0 && next_ordinate < column) {
			if (matrix[next_abscissa][next_ordinate] >= matrix[abscissa][ordinate] && !can_arrive[next_abscissa][next_ordinate]) {
				DfsHelper(matrix, next_abscissa, next_ordinate, can_arrive);
			}
		}
	}

	
}

vector<vector<int>> pacificAtlantic(vector<vector<int>>& matrix) {
	int row = matrix.size();
	if (row == 0 ) {
		return { };
	}
	int column = matrix[0].size();
	
	vector<vector<bool>> can_arrive_pacific(row, vector<bool>(column, false));
	vector<vector<bool>> can_arrive_atlantic(row, vector<bool>(column, false));
	vector<vector<int>> right_position;		

	//逆流,DFS遍历四边，重合处为符合条件的点
	for (int i = 0; i < row; i++) {
		DfsHelper(matrix, i, 0, can_arrive_pacific);
		DfsHelper(matrix, i, column - 1, can_arrive_atlantic);
	}
	for (int i = 0; i < column; i++) {
		DfsHelper(matrix, 0, i, can_arrive_pacific);
		DfsHelper(matrix, row - 1, i, can_arrive_atlantic);
	}
	
	for (int i = 0; i < row; i++) {
		for (int j = 0; j < column; j++) {
			if (can_arrive_pacific[i][j] && can_arrive_atlantic[i][j]) {
				right_position.push_back({ i,j });
			}
		}
	}
	return right_position;
}


//trace back
/*
* @brief	46. Permutations
* @detail	Given an array nums of distinct integers, return all the possible permutations. 
*			You can return the answer in any order.
*/


vector<vector<int>> ans;
vector<int> permutation;
vector<bool> used;
void TraceBack(vector<int>& nums) {
	if (permutation.size() == nums.size()) {
		ans.push_back(permutation);
		return;
	}
	for (int i = 0; i < nums.size(); i++) {
		if (!used[i]) {
			used[i] = true;					//固定一个数字
			permutation.push_back(nums[i]);
			TraceBack(nums);
			permutation.pop_back();
			used[i] = false;
		}
	}
}
vector<vector<int>> permute(vector<int>& nums) {
	used.resize(nums.size(), false);
	TraceBack(nums);
	
	return ans;
}

/**
* @brief	77. Combinations
* @detail	Given two integers n and k, return all possible combinations of k numbers out of 1 ... n.
*			You may return the answer in any order.
*/

vector<int> combination;
vector<vector<int>>	combinations_result;
void CombineTraceBack(int n,int k,int start_index) {
	if (combination.size() == k) {
		combinations_result.push_back(combination);
		return;
	}
	for (int i = start_index; i <= n - (k - combination.size()) + 1; i++) {
		combination.push_back(i);
		CombineTraceBack(n, k, i + 1);
		combination.pop_back();
	}
}

vector<vector<int>> combine(int n, int k) {
	CombineTraceBack(n, k, 1);
	return combinations_result;
}

/**
* @brief	79. Word Search
* @detail	Given an m x n board and a word, find if the word exists in the grid.
*			The word can be constructed from letters of sequentially adjacent cells, 
*			where "adjacent" cells are horizontally or vertically neighboring. 
*			The same letter cell may not be used more than once.
* 
*/

void ExitTraceBack(vector<vector<bool>>& used, vector<vector<char>>& board, string word,int index ,int abscissa,int ordinate,bool& is_find) {
	int row = board.size();
	int column = board[0].size();
	
	if (is_find) {
		return;
	}

	if (board[abscissa][ordinate] == word[index]) {
		if (index == word.size() - 1) {
			is_find = true;
			return;
		}
		used[abscissa][ordinate] = true;
		int direction[4][2] = { {1,0},{-1,0},{0,1},{0,-1} };
		for (int i = 0; i < 4; i++) {
			int next_abscissa = abscissa + direction[i][0];
			int next_ordinate = ordinate + direction[i][1];
			if (next_abscissa >= 0 && next_abscissa < row && next_ordinate >= 0 && next_ordinate < column) {
				if (!used[next_abscissa][next_ordinate]) {
					 ExitTraceBack(used, board, word, index + 1, next_abscissa, next_ordinate,is_find);
				}
			}
		}
		used[abscissa][ordinate] = false;
		
	}
	
}

bool exist(vector<vector<char>>& board, string word) {
	vector<vector<bool>> used;
	used.resize(board.size(), vector<bool>(board[0].size(), false));
	int row = board.size();
	int column = board[0].size();
	bool is_find = false;
	for (int i = 0; i < row; i++) {
		for (int j = 0; j < column; j++) {
			ExitTraceBack(used, board, word, 0, i, j, is_find);
			}
	}
	return is_find;
}

/**
* @brief	51. N-Queens
* @detail	The n-queens puzzle is the problem of placing n queens on an n x n chessboard such that no two queens attack each other.
*			Given an integer n, return all distinct solutions to the n-queens puzzle.
*
*			Each solution contains a distinct board configuration of the n-queens' placement, where 'Q' and '.' 
*			both indicate a queen and an empty space, respectively.
*/

vector<vector<string>> solveNQueens(int n) {

}