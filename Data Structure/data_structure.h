#pragma once
#include <vector>
#include <string>
using std::vector;
using std::string;
typedef struct ListNode {
	int val;
	ListNode* next;
	ListNode() : val(0), next(nullptr) {}
	ListNode(int x) : val(x), next(nullptr) {}
	ListNode(int x, ListNode* next) : val(x), next(next) {}
}ListNode;

vector<int> findDisappearedNumbers(vector<int>& nums);			/// 448. Find All Numbers Disappeared in an Array
void rotate(vector<vector<int>>& matrix);						/// 48. Rotate Image
bool searchMatrix(vector<vector<int>>& matrix, int target);		/// 240. Search a 2D Matrix II
int maxChunksToSorted(vector<int>& arr);						/// 769. Max Chunks To Make Sorted
bool isValid(string s);											/// 20. Valid Parentheses
vector<int> dailyTemperatures(vector<int>& T);					/// 739. Daily Temperatures
ListNode* mergeKLists(vector<ListNode*>& lists);				/// 23. Merge k Sorted Lists
vector<vector<int>> getSkyline(vector<vector<int>>& buildings); /// 218. The Skyline Problem
vector<int> maxSlidingWindow(vector<int>& nums, int k);			/// 239. Sliding Window Maximum
vector<int> twoSum(vector<int>& nums, int target);				/// 1. Two Sum
int longestConsecutive(vector<int>& nums);						/// 128. Longest Consecutive Sequence
int maxPoints(vector<vector<int>>& points);						/// 149. Max Points on a Line
vector<string> findItinerary(vector<vector<string>>& tickets);	/// 332. Reconstruct Itinerary
int subarraySum(vector<int>& nums, int k);						/// 560. Subarray Sum Equals K
vector<vector<int>> matrixReshape(vector<vector<int>>& nums, int r, int c);	/// 566. Reshape the Matrix
vector<int> nextGreaterElements(vector<int>& nums);				/// 503. Next Greater Element II
bool containsDuplicate(vector<int>& nums);						/// 217. Contains Duplicate
int findShortestSubArray(vector<int>& nums);					/// 697. Degree of an Array
int findLHS(vector<int>& nums);									/// 594. Longest Harmonious Subsequence
int findDuplicate(vector<int>& nums);							/// 287. Find the Duplicate Number
int nthSuperUglyNumber(int n, vector<int>& primes);				/// 313. Super Ugly Number
vector<int> advantageCount(vector<int>& A, vector<int>& B);		///870. Advantage Shuffle

