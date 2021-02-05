#include <iostream>
#include <iterator>
#include <algorithm>
#include <vector>
#include <stack>
#include <set>
#include <queue>
#include <unordered_map>
#include <unordered_set>
#include "search.h"
using namespace std;

/// 二分查找

/// <summary>
/// 69.Sqrt(x)
/// </summary>
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


/// <summary>
/// 34. Find First and Last Position of Element in Sorted Array
/// </summary>
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
		return vector<int>{ -1, -1 };
	}

	int left = findFirstPosition(nums, target);
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
	return vector<int>{distance(nums.begin(), liter), distance(nums.begin(), riter) - 1};

}


/// <summary>
/// 81. Search in Rotated Sorted Array II
/// </summary>
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
		else if (nums[left] > nums[mid]) {
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

/// <summary>
///  154. Find Minimum in Rotated Sorted Array II
/// </summary>
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
		else if (nums[mid] < nums[right]) {
			right = mid;
		}
		else {
			left = mid + 1;
		}
	}
	return nums[left];
}


/// <summary>
/// 540. Single Element in a Sorted Array
/// </summary>
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


/// <summary>
/// 4. Median of Two Sorted Arrays
/// </summary>
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

		int newIndex1 = min(m - 1, index1 + k / 2 - 1);
		int newIndex2 = min(n - 1, index2 + k / 2 - 1);
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
		return (double)(getKthElement(nums1, nums2, (m + n) / 2) + getKthElement(nums1, nums2, (m + n) / 2 + 1)) / 2;
	}
	else {
		return getKthElement(nums1, nums2, (m + n + 1) / 2);
	}
}


// DFS


/// <summary>
/// @brief	695. Max Area of Island
/// </summary>
int DfsHelper(int i, int j, vector<vector<bool>>& is_visited, vector<vector<int>>& grid) {
	int rows = grid.size();
	int column = grid[0].size();
	is_visited[i][j] = true;

	if (grid[i][j] != 1) {
		return 0;
	}
	int area = 1;
	if (i < rows - 1 && !is_visited[i + 1][j])
		area += DfsHelper(i + 1, j, is_visited, grid);

	if (i > 0 && !is_visited[i - 1][j])
		area += DfsHelper(i - 1, j, is_visited, grid);

	if (j < rows - 1 && !is_visited[i][j + 1])
		area += DfsHelper(i, j + 1, is_visited, grid);

	if (j > 0 && !is_visited[i][j - 1])
		area += DfsHelper(i, j - 1, is_visited, grid);

	return area;

}
int maxAreaOfIsland(vector<vector<int>>& grid) {
	int rows = grid.size();
	int column = grid[0].size();
	vector<vector<bool>> is_visited(rows,
		vector<bool>(column, false));

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

/// <summary>
/// 547. Number of Provinces
/// </summary>
int findCircleNum(vector<vector<int>>& isConnected) {
	int city_nums = isConnected.size();
	vector<bool> is_visited(city_nums, false);

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
	//并查集
	int parent;
	int rank;
}City;

int FindSet(vector<City>& cities, int city) {
	if (cities[city].parent != city) {
		cities[city].parent = FindSet(cities, cities[city].parent);		//路径压缩，将根节点做为集合代表
	}
	return cities[city].parent;
}
void UnionSet(vector<City>& cities, int city1, int city2) {
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
int findCircleNumByUnionFind(vector<vector<int>>& isConnected) {
	int city_nums = isConnected.size();
	vector<City> cities(city_nums);
	for (int i = 0; i < city_nums; i++) {	//设置集合
		cities[i].parent = i;
		cities[i].rank = 0;
	}
	int privonces = city_nums;
	for (int i = 0; i < city_nums; i++) {
		for (int j = 0; j < city_nums; j++) {
			if (i != j && isConnected[i][j] == 1) {
				if (FindSet(cities, i) != FindSet(cities, j)) {
					UnionSet(cities, i, j);
					privonces--;
				}



			}
		}
	}

	return privonces;
}


/// <summary>
/// 417. Pacific Atlantic Water Flow
/// </summary>
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
	if (row == 0) {
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


//回溯算法

/// <summary>
/// 46. Permutations
/// </summary>
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


/// <summary>
/// 77. Combinations
/// </summary>
vector<int> combination;
vector<vector<int>>	combinations_result;
void CombineTraceBack(int n, int k, int start_index) {
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


/// <summary>
/// 79. Word Search
/// </summary>
void ExitTraceBack(vector<vector<bool>>& used, vector<vector<char>>& board, string word, int index, int abscissa, int ordinate, bool& is_find) {
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
					ExitTraceBack(used, board, word, index + 1, next_abscissa, next_ordinate, is_find);
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



/// <summary>
/// 51. N-Queens
/// </summary>
vector<vector<string>> result;
vector<string> solution;
void NQueensHelper(vector<vector<bool>>& used, int row, int n) {

	if (row == n) {
		result.push_back(solution);
		return;
	}
	string row_layout;
	row_layout.assign(n, '.');

	for (int j = 0; j < n; j++) {
		if (!used[0][j] && !used[1][row + j] && !used[2][n - 1 - j + row]) {
			row_layout[j] = 'Q';
			solution.push_back(row_layout);
			used[0][j] = used[1][row + j] = used[2][n - 1 - j + row] = true;
			NQueensHelper(used, row + 1, n);
			solution.pop_back();
			used[0][j] = used[1][row + j] = used[2][n - 1 - j + row] = false;
			row_layout[j] = '.';
		}
	}
}
vector<vector<string>> solveNQueens(int n) {
	vector<bool> columns_used(n, false);
	vector<bool> left_diagonals_used(2 * n - 1, false);		// 棋盘上左斜‘/’方向共2 * n - 1 行
	vector<bool> right_diagonals_used(2 * n - 1, false);    // 棋盘上右斜‘\’方向共2 * n - 1 行
	vector<vector<bool>> used;
	used.push_back(columns_used);
	used.push_back(left_diagonals_used);
	used.push_back(right_diagonals_used);
	NQueensHelper(used, 0, n);	//第一排,第一个位置放置棋子。
	return result;
}



/// <summary>
/// 934. Shortest Bridge
/// </summary>
void Dfs(vector<vector<int>>& A, queue<pair<int, int>>& Q, int abscissa, int ordinate) {
	if (abscissa < 0 || abscissa >= A.size() || ordinate < 0 || ordinate >= A[0].size() || A[abscissa][ordinate] == -1) {
		return;
	}

	if (A[abscissa][ordinate] == 1) {
		A[abscissa][ordinate] = -1;
		int direction[4][2] = { {1,0},{-1,0},{0,-1},{0,1} };
		int next_abscissa;
		int next_ordinate;
		for (int i = 0; i < 4; i++) {
			next_abscissa = abscissa + direction[i][0];
			next_ordinate = ordinate + direction[i][1];
			Dfs(A, Q, next_abscissa, next_ordinate);
		}
	}

	if (A[abscissa][ordinate] == 0) {
		A[abscissa][ordinate] = -1;
		Q.push({ abscissa ,ordinate });		///< 将与第一个岛相邻的点入队列，作为第一层,此时距离为0，用-1表示；
		return;
	}
}
int shortestBridge(vector<vector<int>>& A) {
	int row = A.size();
	int column = A[0].size();
	
	queue<pair<int, int>> Q;
	bool is_searched = false;
	for (int i = 0; i < row; i++) {
		if (is_searched) break;
		for (int j = 0; j < column; j++) {
			if (A[i][j] == 1) {
				Dfs(A, Q, i, j);
				is_searched = true;
				break;
			}
		}
	}

	int direction[4][2] = { {1,0},{-1,0},{0,-1},{0,1} };
	
	int distance = 1;
	while (!Q.empty()) {
		
		int current_size = Q.size(); ///< 每层的数量
		while (current_size--) {
			auto coordinate = Q.front();
			int x = coordinate.first;
			int y = coordinate.second;
			int next_x;
			int next_y;
			Q.pop();
			for (int i = 0; i < 4; i++) {
				next_x = x + direction[i][0];
				next_y = y + direction[i][1];
				if (next_x >= 0 && next_x < A.size() && next_y >= 0 && next_y < A[0].size()) {
					if (A[next_x][next_y] == -1) {
						continue;
					}

					if (A[next_x][next_y] == 1) {
						return distance;
					}

					if (A[next_x][next_y] == 0) {
						A[next_x][next_y] = -1;
						Q.push({ next_x ,next_y });
					}
				}
			}
		}
		distance++;								///< 搜索下一层，距离+1；
	}
	return 0;

}

/// <summary>
/// 126. Word Ladder II
/// </summary>
void TraceBack(vector<vector<string>>& results, vector<string>& ans,string word, string endWord, 
	unordered_map<string, vector<string>>& next,int distance,int count) {
	if (count == distance) {
		if (word == endWord) {
			results.push_back(ans);
		}
		return;
	}

	for (auto next_word : next[word]) {
		ans.push_back(next_word);
		TraceBack(results, ans, next_word, endWord, next, distance, count + 1);
		ans.pop_back();
	}
}
void FindNextWords(unordered_map<string, vector<string>>& next, const vector<string>& wordList, string& word) {
	if (next.find(word) != next.end()) {
		return;
	}
	int difference;
	for (int i = 0; i < wordList.size(); i++) {
		difference = 0;
		for (int j = 0; j < word.size(); j++) {
			if (word[j] != wordList[i][j]) {
				difference++;
			}
		}
		if (difference == 1) {
			next[word].push_back(wordList[i]);
		}
	}

}

vector<vector<string>> findLadders(string beginWord, string endWord, vector<string>& wordList) { /// < 超时！！！
	unordered_map<string,int> distance_tree;
	unordered_map<string, bool> is_searched;

	for (int i = 0; i < wordList.size(); i++) {
		distance_tree[wordList[i]] = 0;
		is_searched[wordList[i]] = false;
	}
	if (distance_tree.find(endWord)== distance_tree.end()) {
		return {};
	}
	queue<string> Q;
	unordered_map<string, vector<string>> next;

	/// 广度优先找到到endWord的最小距离
	bool is_find_end = false;
	Q.push(beginWord);
	while (!Q.empty()) {
		if (is_find_end) {
			break;
		}
		string word = Q.front();
		Q.pop();
		FindNextWords(next, wordList, word);		///< 找到每一个单词的子节点
		if (word == endWord) {
			is_find_end = true;
			break;
		}
		for (auto w : next[word]) {
			if (is_searched[w] == false) {
				distance_tree[w] = distance_tree[word] + 1;
				Q.push(w);
				is_searched[w] = true;
			}
		}
	}

	int distance = distance_tree[endWord];
	vector<vector<string>> results;
	vector<string> ans;
	ans.push_back(beginWord);
	/// 回溯，深度为最小距离
	TraceBack(results, ans,beginWord,endWord,next, distance,0);
	return results;

}

/// <summary>
/// 126. Word Ladder II - 使用双向BFS加速搜索过程
/// </summary>
void TwoWayBfs(unordered_set<string>& set1, unordered_set<string>& set2, unordered_set<string>& word_list,
	unordered_map<string, vector<string>>& next, bool direction) {
	if (set1.empty()) {
		return;
	}

	if (set1.size() > set2.size()) {
		
		TwoWayBfs(set2, set1, word_list, next, !direction);
		return;
	}

	for (auto str : set1) {
		word_list.erase(str);
	}

	for (auto str : set2) {
		word_list.erase(str);
	}
	bool found = false;
	unordered_set<string> temp;
	for (auto str : set1) {
		for (int i = 0; i < str.size(); i++) {
			string next_str  = str;
			for (char ch = 'a'; ch<='z'; ch++) {
				if (next_str[i] == ch) {
					continue;
				}
				next_str[i] = ch;
				string key = direction ? str : next_str;
				string val = direction ? next_str : str;
				
				if (set2.count(next_str)) {
					next[key].push_back(val);
					found = true;
				}
				if (!found && word_list.count(next_str)) {
					temp.insert(next_str);
					next[key].push_back(val);
				}
			}
		}
	}
	if (!found) {
		TwoWayBfs(set2, temp, word_list, next, !direction);
	}
}
void TraceBackHelper(vector<vector<string>>& results, vector<string>& ans, string& word, string& endWord,
	unordered_map<string, vector<string>>& next) {
	if (word == endWord) {
		results.push_back(ans);
		return;
	}
	for (auto next_word : next[word]) {
		ans.push_back(next_word);
		TraceBackHelper(results, ans, next_word, endWord, next);
		ans.pop_back();
	}
}

vector<vector<string>> findLaddersByTwoWayBfs(string beginWord, string endWord, vector<string>& wordList) {
	unordered_set<string> word_list;
	vector<vector<string>> results;
	for (const auto& str : wordList) {
		word_list.insert(str);
	}

	if (!word_list.count(endWord)) {
		return results;
	}

	word_list.erase(beginWord);
	word_list.erase(endWord);
	unordered_set<string> set1;
	unordered_set<string> set2;
	unordered_map<string, vector<string>> next;
	set1.insert(beginWord);
	set2.insert(endWord);

	TwoWayBfs(set1,set2,word_list,next,true);
	
	
	vector<string> ans;
	ans.push_back(beginWord);
	TraceBackHelper(results, ans, beginWord, endWord, next);
	return results;

}


/// <summary>
/// 130. Surrounded Regions
/// </summary>
void dfs(vector<vector<char>>& board,vector<vector<bool>>& is_full,int x,int y) {
	int row = board.size();
	int column = board[0].size();

	if (x < 0 || x >= row || y < 0 || y >= column || is_full[x][y] == false || board[x][y] == 'X') {
		return;
	}

	is_full[x][y] = false;
	int direction[4][2] = { {1,0},{-1,0},{0,-1},{0,1} };
	for (int i = 0; i < 4; i++) {
		dfs(board, is_full, x + direction[i][0], y + direction[i][1]);
	}
}
void solve(vector<vector<char>>& board) {
	int row = board.size();
	int column = board[0].size();
	if (row == 0) {
		return;
	}
	vector<vector<bool>> is_full(row,vector<bool>(column,true));
	for (int i = 0; i < row; i++) {
		if (board[i][0] == 'O')
			dfs(board, is_full, i, 0);
		if(board[i][column - 1] == 'O')
			dfs(board,is_full, i, column - 1);
	}
	for (int i = 0; i < column; i++) {
		if (board[0][i] == 'O')
			dfs(board, is_full, 0, i);
		if (board[row - 1][i] == 'O')
			dfs(board, is_full, row - 1, i);
	}
	for (int i = 0; i < row; i++) {
		for (int j = 0; j < column; j++) {
			if (is_full[i][j]) {
				board[i][j] = 'X';
			}
		}
	}
}
void binaryTreePathsHelper(TreeNode* root, vector<string>& result, vector<int>& path) {
	if (!root->left && !root->right) {
		string str_path;
		str_path += to_string(path[0]);
		for (int i = 1; i < path.size(); i++) {
			str_path += "->";
			str_path += to_string(path[i]);
		}
		result.push_back(str_path);
		return;
	}
	vector<TreeNode*> next_node;
	if (root->left) {
		next_node.push_back(root->left);
	}
	if (root->right) {
		next_node.push_back(root->right);
	}

	for (const auto& p : next_node) {
		path.push_back(p->val);
		binaryTreePathsHelper(p, result, path);
		path.pop_back();
	}
	
}
/// <summary>
/// 257. Binary Tree Paths
/// </summary>
vector<string> binaryTreePaths(TreeNode* root) {
	vector<string> result;
	if (!root) {
		return  result;
	}
	vector<int> path ;
	path.push_back(root->val);
	
	binaryTreePathsHelper(root, result, path);
	return result;

	
}

/// <summary>
/// 47 Permutations II
/// </summary>
void permuteUniqueHelper(vector<int>& nums, vector<vector<int>>& result, vector<int>& path, vector<bool>& used) {
	
	if (path.size() == nums.size()  ) {
		result.push_back(path);
		return;
	}
	
	unordered_map<int,int> unique_flag;
	for (int i = 0; i < nums.size(); i++) {
		if (!used[i]) {
			unique_flag[nums[i]]++;
			used[i] = true;
			path.push_back(nums[i]);
			if (unique_flag[nums[i]] == 1) {
				permuteUniqueHelper(nums, result, path, used);
			}
			used[i] = false;
			path.pop_back();
			
		}
	}
	
	

}
vector<vector<int>> permuteUnique(vector<int>& nums) {
	vector<vector<int>> result;
	if (nums.empty()) {
		return result;
	}

	vector<int> path;
	

	vector<bool> used(nums.size(), false);
	
	//result.push_back(nums);
	permuteUniqueHelper(nums,result,path,used);
	for (auto x : result) {
		for (auto y : x) {
			cout << y << " ";
		}
		cout << endl;
	}
	return result;
}

/// <summary>
//40. Combination Sum II
/// </summary>
void combinationSum2Helper(vector<int>& candidates, vector<vector<int>>& result, 
	vector<int>& path, vector<bool>& used,int target,int sum,int start) {
	if (sum == target) {
		result.push_back(path);
		return;
	}
	else {
		for (int i = start; i < candidates.size()&& sum + candidates[i] <= target; i++) {
			if (used[i] || (i > 0 && candidates[i] == candidates[i - 1] && !used[i - 1])) {
				continue;
			}
			path.push_back(candidates[i]);
			sum += candidates[i];
			used[i] = true;
			combinationSum2Helper(candidates, result, path, used, target, sum,i + 1);
			used[i] = false;
			sum -= candidates[i];
			path.pop_back();
		}
	}

}
vector<vector<int>> combinationSum2(vector<int>& candidates, int target) {
	vector<vector<int>> result;
	if (candidates.empty()) {
		return result;
	}
	
	vector<int> path;
	vector<bool> used(candidates.size());
	sort(candidates.begin(), candidates.end());
	combinationSum2Helper(candidates,result,path,used,target,0,0);
	for (auto x : result) {
		for (auto y : x) {
			cout << y << " ";
		}
		cout << endl;
	}
	return result;
}

/// <summary>
/// 310. Minimum Height Trees
/// </summary>
void CreateHelper(vector<vector<int>>& adjacency_matrix, vector<int>& vertex_degreeint, const vector<vector<int>>& edges) {

	for (int i = 0; i < edges.size(); i++) {
		int x = edges[i][0];
		int y = edges[i][1];
		adjacency_matrix[x][y] = 1;
		adjacency_matrix[y][x] = 1;
		vertex_degreeint[x]++;
		vertex_degreeint[y]++;
	}
}
void findMinHeightTreesBfsHelper(vector<int>& reslut,vector<vector<int>>& adjacency_matrix, vector<int>& vertex_degree) {
	queue<int> Q;
	int vextor_nums = vertex_degree.size();
	
	for (int i = 0; i < vertex_degree.size(); i++) {
		if (vertex_degree[i] == 1) {
			Q.push(i);
		}
	}
	
	while (vextor_nums > 2) {
		int size = Q.size();
		vextor_nums -= size;
		for (int i = 0; i < size; i++) {
			int vertex_index = Q.front();
			vertex_degree[vertex_index] = 0;
			Q.pop();
			for (int j = 0; j < adjacency_matrix[vertex_index].size(); j++) {
				if (adjacency_matrix[vertex_index][j] == 1) {
					vertex_degree[j]--;
					if (vertex_degree[j] == 1) {
						Q.push(j);
					}
				}
			}
		}
		

	}
	while (!Q.empty()) {
		reslut.push_back(Q.front());
		Q.pop();
	}
	
}
vector<int> findMinHeightTrees(int n, vector<vector<int>>& edges) {
	
	vector<int> reslut;
	if (n == 0)
		return reslut;
	if (n == 1)
		return { 0 };
	if (n == 2)
		return{ 0,1 };

	vector<int> height(n, 0);
	vector<vector<int>> adjacency_matrix(n, vector<int>(n, 0));
	vector<int> vertex_degree(n,0);
	CreateHelper(adjacency_matrix, vertex_degree,edges);

	findMinHeightTreesBfsHelper(reslut, adjacency_matrix, vertex_degree);
	return reslut;
}

/// <summary>
/// 37. Sudoku Solver
/// </summary>
bool IsValid(vector<vector<char>>& board, int row, int column, char c) {
	for (int i = 0; i < 9; i++) {
		if (c == board[row][i]) {
			return false;
		}
	}
	for (int i = 0; i < 9; i++) {
		if (c == board[i][column]) {
			return false;
		}
	}

	int start_row = (row / 3) * 3;
	int start_column = (column / 3) * 3;
	for (int i = 0; i < 3; i++) {
		for (int j = 0; j < 3; j++) {
			if (c == board[start_row + i][start_column + j]) {
				return false;
			}
		}
	}
	return true;
}
bool SudokuTraceBack(vector<vector<char>>& board) {
	for (int i = 0; i < board.size(); i++) {
		for (int j = 0; j < board.size(); j++) {
			if (board[i][j] != '.') {
				continue;
			}
			for (char c = '1'; c <= '9'; c++) {
				if (IsValid(board, i, j, c)) {
					board[i][j] = c;
					if (SudokuTraceBack(board)) {
						return true;
					}
					board[i][j] = '.';
				}
			}
			return false;
			
		}
	}
	return true;
}
void solveSudoku(vector<vector<char>>& board) {
	SudokuTraceBack(board);
}
