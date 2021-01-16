#include <ctype.h>
#include <utility>
#include <iostream>
#include "divide_conquer.h"
using namespace std;

/// <summary>
/// 241. Different Ways to Add Parentheses
/// </summary>
vector<int> diffWaysToComputeHelper(vector<vector<vector<int>>>& memo, vector<int>& numbers, vector<char>& symbols, int start, int end) {
	vector<int> result;
	if (end - start == 1) {
		result.push_back(numbers[start]);
	}
	else {
		for (int i = start; i < end - 1; i++) {
			vector<int> nums1;
			if (!memo[start][i + 1].empty()) {
				nums1 = memo[start][i + 1];
			}
			else {
				nums1  = diffWaysToComputeHelper(memo,numbers, symbols, start, i + 1);
				memo[start][i + 1] = nums1;
			}
			vector<int> nums2;
			if (!memo[i+1][end].empty()) {
				nums2 = memo[i + 1][end];
			}
			else {
				nums2 = diffWaysToComputeHelper(memo, numbers, symbols, i + 1, end);
				memo[i + 1][end] = nums2;
			}
			for (const int& num1 : nums1) {
				for (const int& num2 : nums2) {
					switch (symbols[i]) {
					case '+':
						result.push_back(num1 + num2);
						break;
					case '*':
						result.push_back(num1 * num2);
						break;
					case '-':
						result.push_back(num1 - num2);
						break;
					}
				}
			}
		}
	}
	return result;
}
void DivideNumsSymbols(string input, vector<int>& numbers, vector<char>& symbols) {
	string temp = "";
	int i = 0;
	while (i < input.size()) {
		char ch = input[i];
		if (ch == '+' || ch == '-' || ch == '*') {
			symbols.push_back(ch);
			int num = atol(temp.c_str());
			numbers.push_back(num);
			temp = "";
		}
		else {
			temp += ch;
		}
		i++;
	}
	int num = atol(temp.c_str());
	numbers.push_back(num);
}
vector<int> diffWaysToCompute(string input) {
	vector<int> numbers;
	vector<char> symbols;
	DivideNumsSymbols(input, numbers, symbols);
	int n = numbers.size();
	vector<vector<vector<int>>> memo(n, vector<vector<int>>(n + 1)); ///< 备忘录机制，优化递归过程
	return diffWaysToComputeHelper(memo,numbers, symbols, 0, numbers.size());
}

/// <summary>
/// 932. Beautiful Array
/// </summary>
vector<int> helper(vector<int>& nums) {
	if (nums.size() == 1) {
		return nums;
	}
	vector<int> v1;
	vector<int> v2;
	for (int i = 0; i < nums.size(); i += 2) {
		v1.push_back(nums[i]);
	}
	for (int i = 1; i < nums.size(); i += 2) {
		v2.push_back(nums[i]);
	}
	v1 = helper(v1);
	v2 = helper(v2);

	vector<int> result = v1;
	for (auto x : v2) {
		result.push_back(x);
	}
	return result;
}
vector<int> beautifulArray(int N) {
	vector<int> v;
	for (int i = 1; i <= N; i++) {
		v.push_back(i);
	}
	return helper(v);
}

/// <summary>
/// 312. Burst Balloons
/// </summary>
int MaxCoinsHelper(vector<vector<int>>& memo,vector<int>& val,int start,int end) {
	//开区间 (start,end)
	//考虑区间内最后一个被戳破的气球i，此时可获得硬币 val[start] * val[i] * val[end];
	//在考虑i戳破前的情况，分为两个区间：(start,i)  和 (i,end);
	if (start == end - 1) {
		return 0;
	}

	if (memo[start][end] != -1) {
		return memo[start][end];
	}

	int max_coins = 0;
	for (int i = start + 1; i < end; i++) {
		int coins = val[start] * val[i] * val[end];
		coins += MaxCoinsHelper(memo,val, start, i) + MaxCoinsHelper(memo,val, i, end);
		max_coins = ::max(max_coins, coins);
	}
	memo[start][end] = max_coins;
	return max_coins;
}
int maxCoins(vector<int>& nums) {
	int n = nums.size();
	vector<int> val(n + 2, 1);
	for (int i = 0; i < n; i++) {
		val[i + 1] = nums[i];
	}
	vector<vector<int>> memo(n + 2, vector<int>(n + 2, -1)); //记录计算值，避免重复计算
	return MaxCoinsHelper(memo,val, 0, n + 1);
}