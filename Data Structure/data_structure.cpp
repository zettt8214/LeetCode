#include <iostream>
#include <stack>
#include <queue>
#include <set>
#include <map>
#include <numeric>
#include <unordered_map>
#include <cassert>
#include <algorithm>
#include "data_structure.h"



using namespace std;

/// <summary>
/// 448. Find All Numbers Disappeared in an Array
/// </summary>
vector<int> findDisappearedNumbers(vector<int>& nums) {
	vector<int> ans;
	int n = nums.size();
	for (int i = 0; i < n; i++) {
		int position = abs(nums[i]) - 1;
		if (nums[position] > 0) {
			nums[position] *= -1;
		}
	}

	for (int i = 0; i < n; i++) {
		if (nums[i] > 0) {
			ans.push_back(i + 1);
		}
	}
	return ans;
}

/// <summary>
/// 48. Rotate Image
/// </summary>
void RotateHelper(vector<vector<int>>& matrix,int index_level) {
	int len = matrix.size();
	int len_of_level = len - index_level * 2;
	int i = index_level;
	
	for (int j = index_level; j < i + len_of_level - 1; j++) {
		int temp = matrix[i][j];
		matrix[i][j] = matrix[len - 1 - j][i];
		matrix[len - 1 - j][i] = matrix[len - 1 - i][len - 1 - j];
		matrix[len - 1 - i][len - 1 - j] = matrix[j][len - 1 - i];
		matrix[j][len - 1 - i] = temp;
	}
}
void rotate(vector<vector<int>>& matrix) {
	int len = matrix.size();
	int level_count = (len + 1) / 2;

	for (int i = 0; i < level_count; i++) {		//由外到内，一圈一圈旋转
		RotateHelper(matrix, i);
	}

	for (auto x : matrix) {
		for (auto y : x) {
			cout << y << " ";
		}
		cout << endl;
	}
}


/// <summary>
/// 240. Search a 2D Matrix II
/// </summary>
bool SearchMatrixHelper(vector<vector<int>>& matrix, int target,int x,int y) {
	if (x >= matrix.size() || y >= matrix[0].size() || matrix[x][y] > target) {
		return false;
	}

	if (matrix[x][y] == target) {
		return true;
	}
	

	int left = y, right = matrix[0].size() - 1;
	while (left <= right) {
		int mid = left + (right - left) / 2;
		if (target == matrix[x][mid]) {
			return true;
		}
		else if (target > matrix[x][mid]) {
			left = mid + 1;
		}
		else {
			right = mid - 1;
		}
	}

	left = x;
	right = matrix.size() - 1;
	while (left <= right) {
		int mid = left + (right - left) / 2;
		if (target == matrix[mid][y]) {
			return true;
		}
		else if (target > matrix[mid][y]) {
			left = mid + 1;
		}
		else {
			right = mid - 1;
		}
	}

	return SearchMatrixHelper(matrix, target, x + 1, y + 1);
}
bool searchMatrix(vector<vector<int>>& matrix, int target) {

	return SearchMatrixHelper(matrix,target,0,0);
}


/// <summary>
/// 769. Max Chunks To Make Sorted
/// </summary>
int maxChunksToSorted(vector<int>& arr) {
	vector<int> dp(arr.size());
	dp[0] = 1;
	int index;
	for (int i = 1; i < arr.size(); i++) {
		for (int j = 0; j <= i; j++) {
			if (j == i) {
				dp[i] = dp[i - 1] + 1;
				break;
			}
			if (arr[j] > arr[i]) {
				index = j;
				while (index < i) {
					dp[index + 1] = dp[index];
					index++;
				}
				break;
			}
		}
	}
	return dp[arr.size() - 1];
}
int maxChunksToSorted2(vector<int>& arr) {
	///arr[0] - arr[i]的最大值 max = i 时，排序后正好为 0 - i，为一块。

	int max_value = -1;
	int count = 0;
	for (int i = 0; i < arr.size(); i++) {
		max_value = ::max(max_value, arr[i]);
		if (max_value == i) {
			count++;
		}
	}
	return count;
}

/// <summary>
/// 232. Implement Queue using Stacks
/// </summary>
class MyQueue {
private:
	std::stack<int> in_, out_;

public:
	/** Initialize your data structure here. */
	MyQueue() {

	}

	/** Push element x to the back of queue. */
	void push(int x) {
		in_.push(x);

	}

	/** Removes the element from in front of queue and returns that element. */
	int pop() {
		in2out();
		int ret = out_.top();
		out_.pop();
		return ret;
	}

	
	/** Get the front element. */
	int peek() {
		in2out();
		int ret = out_.top();
		return ret;
	}

	void in2out() {
		if (out_.empty()) {
			while (!in_.empty()) {
				out_.push(in_.top());
				in_.pop();
			}
		}
	}
	/** Returns whether the queue is empty. */
	bool empty() {
		return in_.empty() && out_.empty();
	}
};

/// <summary>
/// 155. Min Stack
/// </summary>
class MinStack {
	stack<int> min_stack_, stack_;
	
public:
	/** initialize your data structure here. */
	MinStack() {
		
	}

	void push(int x) {
		stack_.push(x);
		if (min_stack_.empty()) {
			min_stack_.push(x);
		}
		else {
			if (x <= min_stack_.top()) {
				min_stack_.push(x);
			}
		}
	}

	void pop() {
		int top = stack_.top();
		stack_.pop();
		if (top == min_stack_.top()) {
			min_stack_.pop();
		}
		
	}

	int top() {
		return stack_.top();
	}

	int getMin() {
		return min_stack_.top();
	}
};


/// <summary>
/// 20. Valid Parentheses
/// </summary>
bool isValid(string s) {
	stack<char> is_valid;

	for (const auto& c : s) {
		if (is_valid.empty()) {
			is_valid.push(c);
		}
		else {
			switch (is_valid.top()) {
			case '(':
				if (c == ')') {
					is_valid.pop();
				}
				else {
					is_valid.push(c);
				}
				break;
			case '[':
				if (c == ']') {
					is_valid.pop();
				}
				else {
					is_valid.push(c);
				}
				break;
			case '{':
				if (c == '}') {
					is_valid.pop();
				}
				else {
					is_valid.push(c);
				}
				break;
			}
		}
	}
	
	return is_valid.empty();
}

/// <summary>
/// 739. Daily Temperatures
/// </summary>
vector<int> dailyTemperatures(vector<int>& T) {
	/// <summary>
	/// 单调递减栈，记录日期
	/// </summary>
	stack<int> helper;
	vector<int> ans(T.size(), 0);
	for (int i = 0; i < T.size(); i++) {
		while (!helper.empty() && T[helper.top()] < T[i]) {
			ans[helper.top()] = i - helper.top();
			helper.pop();
		}
		helper.push(i);
	}
	return ans;
}


/// <summary>
/// 23. Merge k Sorted Lists
/// </summary>
struct Cmp {
	bool operator()(ListNode* a, ListNode* b) {
		return a->val > b->val;
	}
};
ListNode* mergeKLists(vector<ListNode*>& lists) {
	priority_queue<ListNode*, vector<ListNode*>, Cmp> p_queue;
	for (auto& p : lists) {
		if (p) {
			p_queue.push(p);
		}
	}
	ListNode  dummy;
	ListNode* cur = &dummy;
	while (!p_queue.empty()) {
		cur->next = p_queue.top();
		p_queue.pop();
		cur = cur->next;
		if (cur->next) {
			p_queue.push(cur->next);
		}
	}

	cur = dummy.next;
	while (cur) {
		cout << cur->val << " ";
		cur = cur->next;
	}
	return dummy.next;
}

/// <summary>
/// 218. The Skyline Problem
/// </summary>

struct Comp {
	bool operator()(pair<int, int> a, pair<int, int> b) { 
		if (a.first == b.first) {					///< 调整高度不同，横坐标相同的建筑，排序顺序
			return a.second > b.second;
		}
		else {
			return a.first > b.first;
		}

	}
};
vector<vector<int>> getSkyline(vector<vector<int>>& buildings) {
	priority_queue<pair<int, int>, vector<pair<int, int>>, Comp> q;
	for (auto b : buildings) {
		q.push(make_pair(b[0], -b[2])); ///< 高度为负值，代表左端点
		q.push(make_pair(b[1], b[2]));
	}

	multiset<int> height({ 0 });
	vector<int> last = { 0,0 };
	vector<vector<int>> ans;
	while (!q.empty()) {
		auto point = q.top();
		q.pop();
		if (point.second < 0) {
			height.insert(-point.second);
		}
		else {
			height.erase(height.find(point.second));
		}

		auto max_height = *height.rbegin();

		if (last[1] != max_height) {
			last[0] = point.first;
			last[1] = max_height;
			ans.push_back(last);
		}
	}
	return ans;
}


/// <summary>
/// 239. Sliding Window Maximum
/// </summary>
int GetMaxValue(vector<int>& nums, int start, int end) {
	int max_value = nums[start];
	for (int i = start + 1; i <= end; i++) {
		max_value = ::max(nums[i], max_value);
	}
	return max_value;
}
vector<int> maxSlidingWindow(vector<int>& nums, int k) {
	vector<int> ans;
	/** 暴力搜索 */
	/*for (int i = 0; i + k - 1 < nums.size(); i++) {
		ans.push_back(GetMaxValue(nums, i, i + k - 1));
	}*/


	/** 单调队列 */
	deque<int> dq;
	for (int i = 0; i < k; i++) {
		while (!dq.empty() && dq.back() < nums[i]) {
			dq.pop_back();
		}
		dq.push_back(i);
	}
	ans.push_back(nums[dq.front()]);
	for (int i = k; i  < nums.size(); i++) {
		if (dq.front() < i - k + 1) {
			dq.pop_front();
		}

		while (!dq.empty() && dq.back() < nums[i]) {
			dq.pop_back();
		}
		dq.push_back(i);

		ans.push_back(nums[dq.front()]);
	}
	

	return ans;
}


/// <summary>
/// 1. Two Sum
/// </summary>
vector<int> twoSum(vector<int>& nums, int target) {
	unordered_map<int, int> hash;
	
	for (int i = 0; i < nums.size(); i++) {
		int num1 = nums[i];
		int num2 = target - num1;
		if (hash.count(num2)) {
			return { i,hash[num2] };
		}
		else {
			hash[num1] = i;
		}
	}

	return {};

}


/// <summary>
/// 128. Longest Consecutive Sequence
/// </summary>
int longestConsecutive(vector<int>& nums) {
	map<int, int> my_map;
	for (auto num : nums) {
		my_map[num] = 1;
	}
	
	auto iter = my_map.begin();
	int max_long = 0;
	for (; iter != my_map.end(); iter++) {
		if (my_map.count(iter->first - 1)) {
			iter->second = my_map[iter->first - 1] + 1;
		}
		max_long = ::max(iter->second, max_long);
	}
	return max_long;
}



/// <summary>
/// 149. Max Points on a Line
/// </summary>

inline int gcd(int a, int b) { // 辗转相除
	if (b == 0) return a;
	return gcd(b, a % b);
}
int maxPoints(vector<vector<int>>&points) {
	unordered_map<string, int> hash;
	int max_points = 0;
	for (int i = 0; i < points.size(); i++) {
		int same_y = 1;
		int same = 1;
		for (int j = i + 1; j < points.size(); j++) {
			if (points[i][1] == points[j][1]) {
				same_y++;
				if (points[i][0] == points[j][0]) {
					same++;
				}
				
			}else {
				int dx = points[i][0] - points[j][0];
				int dy = points[i][1] - points[j][1];
				int g = gcd(dx, dy);
				string slope = to_string(dx/g) + '/' + to_string(dy/g);
				hash[slope]++;
			}
			
		}
		max_points = ::max(max_points, same_y);
		for (auto& count : hash) {
			max_points = ::max(count.second + same, max_points);
		}
		hash.clear();
	}
	return max_points;
}


/// <summary>
/// 332. Reconstruct Itinerary
/// </summary>
bool findItineraryHelper(unordered_map<string, map<string, int>>& hash, string cur_airport, vector<string>& itinerary , int n) {
	if (itinerary.size() == n + 1) {
		return true;
	}
	
	for (auto& next_airport : hash[cur_airport]) {
		if (next_airport.second > 0) {
			itinerary.push_back(next_airport.first);
			next_airport.second--;
			if (findItineraryHelper(hash, next_airport.first, itinerary, n)) {
				return true;
			}
			next_airport.second++;
			itinerary.pop_back();
		}
	}

	return false;
}

vector<string> findItinerary(vector<vector<string>>& tickets) {
	
	vector<string> itinerary;
	if (tickets.empty()) {
		return itinerary;
	}

	unordered_map<string, map<string,int>> hash;
	for (auto& ticket : tickets) {
		hash[ticket[0]][ticket[1]]++;   //可能存在完全重复的机票
	}
	itinerary.push_back("JFK");
	findItineraryHelper(hash, "JFK", itinerary, tickets.size());
	for (auto x : itinerary) {
		cout << x << " ";
	}
	return itinerary;
}

/// <summary>
/// 303. Range Sum Query - Immutable
/// </summary>
class NumArray {
	vector<int> nums_;
	vector<int> prefix_sum_;
public:
	NumArray(vector<int>& nums) :nums_(nums) {
		prefix_sum_.resize(nums.size() + 1, 0);
		std::partial_sum(nums.begin(), nums.end(), prefix_sum_.begin() + 1);
	}

	int sumRange(int i, int j) {
		return prefix_sum_[j + 1] - prefix_sum_[i];
	}
};

/// <summary>
/// 304. Range Sum Query 2D - Immutable
/// </summary>
class NumMatrix {
	vector<vector<int>> prefix_sum_;
public:
	NumMatrix(vector<vector<int>>& matrix){
		int m = matrix.size();
		int n = (m > 0 ? matrix[0].size() : 0);
		prefix_sum_.resize(m + 1, vector<int>(n + 1, 0));
		for (int i = 1; i <= matrix.size(); i++) {
			for (int j = 1; j <= matrix[0].size(); j++) {
				prefix_sum_[i][j] = prefix_sum_[i][j - 1] + prefix_sum_[i - 1][j] 
					- prefix_sum_[i - 1][j - 1] + matrix[i - 1][j - 1];

			}
		}
	}

	int sumRegion(int row1, int col1, int row2, int col2) {
		return prefix_sum_[row2 + 1][col2 + 1] + prefix_sum_[row1][col1] 
			- prefix_sum_[row1][col2 + 1] - prefix_sum_[row2 + 1][col1];
	}
};

/// <summary>
/// 560. Subarray Sum Equals K
/// </summary>
int subarraySum(vector<int>& nums, int k) {
	int count = 0;
	int prefix_sum = 0;
	unordered_map<int, int> hash;
	hash[0] = 1;
	for (auto& num : nums) {
		prefix_sum += num;
		hash[prefix_sum]++;
		count += hash[prefix_sum - k];
	}
	return count;
}

/// <summary>
/// 566. Reshape the Matrix
/// </summary>
vector<vector<int>> matrixReshape(vector<vector<int>>& nums, int r, int c) {
	int m = nums.size();
	int n = (m > 0 ? nums[0].size() : 0);
	if (m * n != r * c) {
		return nums;
	}
	vector<int> temp(m * n, 0);
	vector<vector<int>> ans(r, vector<int>(c, 0));
	int index = 0;
	for (int i = 0; i < m; i++) {
		for (int j = 0; j < n; j++) {
			temp[index++] = nums[i][j];
		}
	}
	index = 0;
	for (int i = 0; i < r; i++) {
		for (int j = 0; j < c; j++) {
			ans[i][j] = temp[index++];
		}
	}

	for (auto x : ans) {
		for (auto y : x) {
			cout << y << " ";
		}
	}
	return ans;
}


/// <summary>
/// 225. Implement Stack using Queues
/// </summary>
class MyStack {
	queue<int> q_;
public:
	/** Initialize your data structure here. */
	MyStack() {

	}

	/** Push element x onto stack. */
	void push(int x) {
		int pre_size = q_.size();
		q_.push(x);
		while (pre_size--) {
			int temp;
			temp = q_.front();
			q_.pop();
			q_.push(temp);
		}
	}

	/** Removes the element on top of the stack and returns that element. */
	int pop() {
		int temp = q_.front();
		q_.pop();
		return temp;
	}

	/** Get the top element. */
	int top() {
		return q_.front();
	}
	/** Returns whether the stack is empty. */
	bool empty() {
		return q_.empty();
	}
};


/// <summary>
/// 503. Next Greater Element II
/// </summary>
vector<int> nextGreaterElements(vector<int>& nums) {
	int n = nums.size();
	
	if (n < 1) {
		return {};
	}

	vector<int> ans(n, -1);

	/**  单调栈  */
	stack<int> s;

	for (int i = 0; i < 2 * n ; i++) {
		while (!s.empty() && nums[s.top()] < nums[i % n]) {
				ans[s.top()] = nums[i % n];
				s.pop();
		}
		s.push(i % n);
	}
	return ans;
}

/// <summary>
/// 217. Contains Duplicate
/// </summary>
bool containsDuplicate(vector<int>& nums) {
	unordered_map<int, int> hash;
	for (auto num : nums) {
		if (hash[num] > 0) {
			return true;
		}
		
		hash[num]++;
	}
	return false;
}

/// <summary>
/// 697. Degree of an Array
/// </summary>
int findShortestSubArray(vector<int>& nums) {
	unordered_map<int, pair<int,vector<int>>> hash;
	for (int i = 0; i < nums.size(); i++) {
		hash[nums[i]].first++;
		hash[nums[i]].second.push_back(i);
	}
	int degree = 0;
	int size = 0;
	for (auto iter = hash.begin(); iter != hash.end(); iter++) {
		if (degree < (iter->second).first) {
			degree = (iter->second).first;
			size = (iter->second).second.back() - (iter->second).second.front() + 1;
		}else if(degree == (iter->second).first){
			size = ::min(size, (iter->second).second.back() - (iter->second).second.front() + 1);
		}
	}
	return size;
}


/// <summary>
/// 594. Longest Harmonious Subsequence
/// </summary>
int findLHS(vector<int>& nums) {
	map<int, int> hash;
	for (auto num : nums) {
		hash[num]++;
	}

	int longest_size = 0;
	for (auto iter = hash.begin(); iter != hash.end(); iter++) {
		if (hash.count(iter->first - 1)) {
			longest_size = ::max(hash[iter->first - 1] + iter->second, longest_size);
		}
	}
	return longest_size;
}

/// <summary>
/// 287. Find the Duplicate Number
/// </summary>
int findDuplicate(vector<int>& nums) {
	map<int, int> hash;
	for (auto num : nums) {
		hash[num]++;
		if (hash[num] > 1) {
			return num;
		}
	}
	return 0;
}

/// <summary>
/// 313. Super Ugly Number
/// </summary>
int nthSuperUglyNumber(int n, vector<int>& primes) {
	priority_queue<long long,vector<long long>,greater<long long>> Q;
	Q.push(1);

	long long ugly_number = 0;
	while (n--) {
		/** 去重，优先队列中存在重复入队列的元素 */
		while (!Q.empty() && Q.top() == ugly_number) {
			
			Q.pop();
		}
		ugly_number = Q.top();
		cout << ugly_number << " ";
		Q.pop();
		for (int i = 0; i < primes.size(); i++) {
			if(ugly_number * primes[i] <= INT32_MAX)
				Q.push(ugly_number * (long long)primes[i]);
		}
	}
	
	return ugly_number;
}

/// <summary>
/// 870. Advantage Shuffle
/// </summary>
vector<int> advantageCount(vector<int>& A, vector<int>& B) {
	vector<int> ans;
	vector<int> b(B);
	map<int, deque<int>> hash;
	deque<int> remaining;

	::sort(A.begin(), A.end());
	::sort(b.begin(), b.end());

	int i = 0;

	/** 田忌赛马 */
	for (auto num : A) {
		if (num > b[i]) {
			hash[b[i]].push_back(num);
			i++;
		}
		else {
			remaining.push_back(num);
		}
	}

	for (auto num : B) {
		if (hash.count(num)) {
			ans.push_back(hash[num].front());
			hash[num].pop_front();
			if (hash[num].empty()) {
				hash.erase(num);
			}
		}
		else {
			ans.push_back(remaining.front());
			remaining.pop_front();
		}
	}
	return ans;
}