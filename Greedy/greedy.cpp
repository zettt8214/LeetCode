#include <iostream>
#include <algorithm>
#include <vector>
#include <valarray>
using namespace std;


/********************************************************************************************
* 455. Assign Cookies
* 
* Assume you are an awesome parent and want to give your children some cookies.
* But, you should give each child at most one cookie.
* Each child i has a greed factor g[i], which is the minimum size of a cookie
* that the child will be content with;and each cookie j has a size s[j].
* If s[j] >= g[i],we can assign the cookie j to the child i, and the child i will be content.
*
* Your goal is to maximize the number of your content children and output the maximum number.
*********************************************************************************************/
int findContentChildren(vector<int>& g, vector<int>& s) {
	sort(g.begin(), g.end());
	sort(s.begin(), s.end());
	int child = 0;
	int cookie = 0;
	while (child < g.size() && cookie < s.size()) {
		if (s[cookie] >= g[child]) {
			child++;
		}
		cookie++;
	}
	return child;
}

/***********************************************************************************
* 135. Candy
* 
* There are N children standing in a line. Each child is assigned a rating value.
* You are giving candies to these children subjected to the following requirements:
*	Each child must have at least one candy.
*	Children with a higher rating get more candies than their neighbors.
* What is the minimum candies you must give?
*
* Solution:
*	First: from 0 to size of array, for every two elemts ,if left lesser than right,
*		   right = left + 1.
*	Second: from  size of array to 0,do the same operation.
*************************************************************************************/
int candy(vector<int>& ratings) {
	valarray<int> candies(1, ratings.size());

	for (int i = 0; i < ratings.size() - 1; i++) {
		if (ratings[i] < ratings[i + 1]) {
			candies[i + 1] = candies[i] + 1;
		}
	}

	for (int i = ratings.size() - 1; i > 0; i--) {
		if (ratings[i] < ratings[i - 1]) {
			if (!(candies[i - 1] > candies[i]))
				candies[i - 1] = candies[i] + 1;
		}
	}
	return candies.sum();
}

/***************************************************************************
* 435. Non-overlapping Intervals
* 
* Given a collection of intervals, find the minimum number of intervals you
* need to remove to make the rest of the intervals non-overlapping.
*
* Solution:
*	First: sort the array by intervals' end point
*	Second: select more intervals
****************************************************************************/
int eraseOverlapIntervals(vector<vector<int>>& intervals) {
	if (intervals.size() == 0) {
		return 0;
	}

	// lambda function for sort;
	auto sort_func = [](const vector<int>& v1, const vector<int>& v2) {
		return v1[1] < v2[1];
	};

	sort(intervals.begin(), intervals.end(), sort_func);
	for (auto v : intervals) {
		cout << "[" << v[0] << "," << v[1] << "] ";
	}

	int move_count = 0;
	int end = intervals[0][1];
	for (int i = 1; i < intervals.size(); i++) {
		if (intervals[i][0] >= end) {
			end = intervals[i][1];

		}
		else {
			move_count++;
		}

	}
	return move_count;
}

/***************************************************************************
* 605. Can Place Flowers
* 
* You have a long flowerbed in which some of the plots are planted, 
* and some are not. However, flowers cannot be planted in adjacent plots.
* 
* Given an integer array flowerbed containing 0's and 1's, 
* where 0 means empty and 1 means not empty, and an integer n, 
* return if n new flowers can be planted in the flowerbed without 
* violating the no-adjacent-flowers rule.
* 
* Solution 
*	if plot is not planted ,then judge whether it's adjacent plots are empty.
****************************************************************************/
bool canPlaceFlowers(vector<int>& flowerbed, int n) {
	int len = flowerbed.size();
	int count = 0;
	
	for (int i = 0; i < len; i++) {
		if (flowerbed[i] == 0) {
			if ((i == 0 || flowerbed[i - 1] == 0) && (i == len - 1 || flowerbed[i + 1] == 0)) {
				flowerbed[i] = 1;
				count++;
			}
		}
		if (count >= n)
			return true;
	}
	
	for (int i = 0; i < len; i++) {
		cout << flowerbed[i] << " ";
	}
	return false;
}

/*********************************************************************************************
* 452. Minimum Number of Arrows to Burst Balloons
* 
* There are some spherical balloons spread in two-dimensional space.
* For each balloon, provided input is the start and end coordinates of the horizontal diameter.
* Since it's horizontal, y-coordinates don't matter, and hence the x-coordinates of start and 
* end of the diameter suffice. The start is always smaller than the end.
*
* An arrow can be shot up exactly vertically from different points along the x-axis. 
* A balloon with xstart and xend bursts by an arrow shot at x if xstart ≤ x ≤ xend. 
* There is no limit to the number of arrows that can be shot. 
* An arrow once shot keeps traveling up infinitely.
*
* Given an array points where points[i] = [xstart, xend], 
* return the minimum number of arrows that must be shot to burst all balloons.
***********************************************************************************************/
int findMinArrowShots(vector<vector<int>>& points) {
	if (points.size() == 0) {
		return 0;
	}

	// lambda function for sort;
	auto sort_func = [](const vector<int>& v1, const vector<int>& v2) {return v1[1] < v2[1]; };
	sort(points.begin(), points.end(), sort_func);
	int xend = points[0][1];
	int arrowCount = 1;
	for (int i = 1; i < points.size(); i++) {
		if (points[i][0] > xend) {
			xend = points[i][1];
			arrowCount++;
		}
		
	}
	return arrowCount;
}

/*********************************************************************
* 763. Partition Labels
* 
* A string S of lowercase English letters is given. 
* We want to partition this string into as many parts as possible 
* so that each letter appears in at most one part, 
* and return a list of integers representing the size of these parts.
*
**********************************************************************/
vector<int> partitionLabels(string S) {

	vector<int> partition;
	int last[26];

	// record the last position of every letter in string
	for (int i = 0; i < S.size(); i++) {
		last[S[i] - 'a'] = i;
	}

	int end = 0;
	int start = 0;
	for (int i = 0; i < S.size(); i++) {
		if (end == S.size() - 1) {
			partition.push_back(end - start + 1);
			break;
		}
		end = max(end, last[S[i] - 'a']);
		if (i == end) {
			partition.push_back(end - start + 1);
			start = end + 1;
		}
	}
	return partition;
}

/*********************************************************************
* 122. Best Time to Buy and Sell Stock II
* 
* Say you have an array prices for which the ith element 
* is the price of a given stock on day i.
* 
* Design an algorithm to find the maximum profit. 
* You may complete as many transactions as you like 
* (i.e., buy one and sell one share of the stock multiple times).
* 
* Note: You may not engage in multiple transactions at the same time 
* (i.e., you must sell the stock before you buy again).
***********************************************************************/
int maxProfitII(vector<int>& prices) {
	int profit = 0;
	for (int i = 0; i < prices.size() - 1; i++) {
		if (prices[i + 1] - prices[i] > 0) {
			profit += prices[i + 1] - prices[i];
		}
	}
	return profit;
}

/*******************************************************************************
* 406. Queue Reconstruction by Height
* 
* You are given an array of people, people, which are the attributes of 
* some people in a queue (not necessarily in order). 
* Each people[i] = [hi, ki] represents the ith person of height hi with 
* exactly ki other people in front who have a height greater than or equal 
* to hi.
* 
* Reconstruct and return the queue that is represented by the input array people. 
* The returned queue should be formatted as an array queue, 
* where queue[j] = [hj, kj] is the attributes of the jth person in the queue 
* (queue[0] is the person at the front of the queue).
*********************************************************************************/
vector<vector<int>> reconstructQueue(vector<vector<int>>& people) {
	vector<vector<int>> newQueue;
	if (people.empty())
		return newQueue;
	auto sortFunc = [](const vector<int>& v1, const vector<int>& v2) {
		return ((v1[0] > v2[0]) || (v1[0] == v2[0] && v1[1] < v2[1]));
	};
	// lambda function for sort;
	sort(people.begin(), people.end(), sortFunc);
	newQueue.push_back(people[0]);
	for (int i = 1; i < people.size(); i++) {
		newQueue.insert(newQueue.begin() + people[i][1] , people[i]);
	}
	return newQueue;
}

/*******************************************************************************
* 665. Non-decreasing Array
* 
* Given an array nums with n integers, your task is to check if it could 
* become non-decreasing by modifying at most 1 element.
* 
* We define an array is non-decreasing if nums[i] <= nums[i + 1] 
* holds for every i (0-based) such that (0 <= i <= n - 2).
*
********************************************************************************/
bool checkPossibility(vector<int>& nums) {
	int flag = 0;
	for (int i = 0; i < nums.size() - 1; i++) {
		if (nums[i] > nums[i + 1]) {
			if (flag == 1) {
				return false;
			}
			
			if (i != 0 && nums[i - 1] > nums[i + 1])
				nums[i + 1] = nums[i];
			else
				nums[i] = nums[i + 1];
			flag = 1;

		}
	}
	return true;
}