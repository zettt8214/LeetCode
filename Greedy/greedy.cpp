#include <iostream>
#include <algorithm>
#include <vector>
#include <valarray>
using namespace std;


/// <summary>
///455. Assign Cookies
/// </summary>
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


/// <summary>
///  135. Candy
/// </summary>
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


/// <summary>
/// 435. Non-overlapping Intervals
/// </summary>
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


/// <summary>
/// 605. Can Place Flowers
/// </summary>
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

/// <summary>
/// 452. Minimum Number of Arrows to Burst Balloons
/// </summary>
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



/// <summary>
///  763. Partition Labels
/// </summary>
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


/// <summary>
/// 122. Best Time to Buy and Sell Stock II
/// </summary>
int maxProfitII(vector<int>& prices) {
	int profit = 0;
	for (int i = 0; i < prices.size() - 1; i++) {
		if (prices[i + 1] - prices[i] > 0) {
			profit += prices[i + 1] - prices[i];
		}
	}
	return profit;
}


/// <summary>
///  406. Queue Reconstruction by Height
/// </summary>
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


/// <summary>
/// 665. Non-decreasing Array
/// </summary>
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