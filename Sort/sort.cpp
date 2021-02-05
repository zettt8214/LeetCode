#include "sort.h"
#include <vector>
#include <algorithm>
#include <ctime>
#include <iostream>
#include <unordered_map>

using namespace std;

void swap(vector<int>& nums, int i, int j) {
	int temp;
	temp = nums[i];
	nums[i] = nums[j];
	nums[j] = nums[i];
}


/// <summary>
/// 215. Kth Largest Element in an Array
/// </summary>
int quickSelect(vector<int>&nums,int left,int right) {  
	int mid = left + (right - left) / 2;
	swap(nums,left, mid);
	int j = left;
	for (int i = left + 1; i < right; i++) {
		if (nums[i] < nums[left])
			swap(nums, ++j, i);
	}
	swap(nums, left, j);
	for (auto x : nums) {
		cout << x<<" ";
	}
	cout << endl;
	cout << j << endl;
	return j;
}
int findKthLargest(vector<int>& nums, int k) {
	int left = 0, right = nums.size();
	int target = nums.size() - k;
	int j;
	while (true) {
		j = quickSelect(nums, left, right); //使用快速排序性质，每次确定一个元素位置，
											//根据确定元素的位置进行下一次搜索范围。
		if (target == j) {
			return nums[target];
		}
		else if (target < j) {
			right = j;
		}
		else {
			left = j + 1;
		}
	}
}

/*
* 347. Top K Frequent Elements
* 
* Given a non-empty array of integers, return the k most frequent elements.
*/

/// <summary>
/// 347. Top K Frequent Elements
/// </summary>
vector<int> topKFrequent(vector<int>& nums, int k) { 
	unordered_map<int, int> counts;
	int maxCount = 0;
	for (auto nums : nums) {
		maxCount = max(maxCount, ++counts[nums]);
	}

	vector<vector<int>> buckets(maxCount + 1);
	for (auto p : counts) {
		buckets[p.second].push_back(p.first);
	}

	vector<int> ans;
	for (int i = buckets.size() - 1; i >= 0 && k > 0; i--) {
		for (auto x : buckets[i]) {
			ans.push_back(x);
			k--;
		}
	}
	return ans;
}


/// <summary>
///  451. Sort Characters By Frequency
/// </summary>
string frequencySort(string s) {
	unordered_map<char, int> counts;
	int maxCount = 0;

	for (auto c : s) {
		maxCount = max(maxCount, ++counts[c]);
	}
	vector<vector<char>> bucket(maxCount + 1);
	for (auto p : counts) {
		bucket[p.second].push_back(p.first);
	}

	
	string ans;
	for (int i = bucket.size() - 1; i > 0; i--) {
		for (auto c : bucket[i]) {
			for (int j = 0; j < i; j++)
				ans += c;
		}
	}
	return ans;
}


/// <summary>
/// 75. Sort Colors
/// </summary>
void sortColors(vector<int>& nums) {
	int p0 = 0, p1 = 0;
	for (int i = 0; i < nums.size(); i++) {
		if (nums[i] == 0) {
			swap(nums, i, p0);
			if (p0 < p1) {  //有1被交换到p0后面的位置
				swap(nums, i, p1);
			}
			p0++;
			p1++;
			
		}
		else if (nums[i] == 1) {
			swap(nums, i, p1);
			p1++;
		}
	}
}

