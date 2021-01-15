#include <vector>
#include <algorithm>
#include <utility>
#include <string>
#include <unordered_set>
#include <iostream>
#include <array>
#include "dp.h"

using namespace std;

/// <summary>
/// 70. Climbing Stairs
/// </summary>
int climbStairs(int n) {
	vector<int> ways(n + 1);
	ways[0] = 0;
	ways[1] = 1;
	if (n > 1) {
		ways[2] = 2;
		for (int i = 3; i <= n; i++) {
			ways[i] = ways[i - 1] + ways[i - 2];  ///< 走i步的方法，走到i-1步再走一步，走到i-2步再走两步
		}
	}
	
	return ways[n];
}


/// <summary>
/// 198. House Robber
/// </summary>
int rob(vector<int>& nums) {
	int n = nums.size();
	if (nums.empty()) {
		return 0;
	}
	if (n < 2) {
		return nums[0];
	}
	vector<int> money(nums.size());
	money[0] = nums[0];
	money[1] = max(nums[0], nums[1]);
	for (int i = 2; i < n; i++) {
		money[i] = max(money[i - 2] + nums[i], money[i - 1]);
	}

	return money[n - 1];
}

/// <summary>
/// 413. Arithmetic Slices
/// </summary>
int numberOfArithmeticSlices(vector<int>& A) {
	int n = A.size();
	if (n < 3) {
		return 0;
	}
	int arithmtic_slices_element_nums = 2;
	int difference = A[1] - A[0];
	vector<int> ans(n);
	ans[0] = 0;
	ans[1] = 0;
	for (int i = 2; i < n; i++) {
		if (difference == A[i] - A[i - 1]) {
			arithmtic_slices_element_nums++;
			ans[i] = ans[i - 1] + arithmtic_slices_element_nums - 2;
		}
		else {
			difference = A[i] - A[i - 1];
			arithmtic_slices_element_nums = 2;
			ans[i] = ans[i - 1];
		}
	}
	return ans[n - 1];
}

/// <summary>
/// 64. Minimum Path Sum
/// </summary>
int minPathSum(vector<vector<int>>& grid) {
	if (grid.empty()) {
		return 0;
	}
	
	int m = grid.size();
	int n = grid[0].size();
	vector<vector<int>> min_distance(m, vector<int>(n, 0));
	min_distance[0][0] = grid[0][0];
	for (int i = 1; i < m; i++) {
		min_distance[i][0] += min_distance[i - 1][0] + grid[i][0];
	}
	for (int i = 1; i < n; i++) {
		min_distance[0][i] += min_distance[0][i-1] + grid[0][i];
	}

	for (int i = 1; i < m; i++) {
		for (int j = 1; j < n; j++) {
			min_distance[i][j] = min(min_distance[i - 1][j], min_distance[i][j - 1]) + grid[i][j];
		}
	}
	return min_distance[m - 1][n - 1];
}

/// <summary>
/// 542. 01 Matrix
/// </summary>
vector<vector<int>> updateMatrix(vector<vector<int>>& matrix) {
	if (matrix.empty()) {
		return {};
	}
	int m = matrix.size();
	
	int n = matrix[0].size();
	const int kInfinity = 65535;
	vector<vector<int>> min_distance(m, vector<int>(n, kInfinity));
	for (int i = 0; i < m; i++) {
		for (int j = 0; j < n; j++) {
			if (matrix[i][j] == 0) {
				min_distance[i][j] = 0;
			}
			else {
				if (i > 0) {
					min_distance[i][j] = min(min_distance[i][j], min_distance[i - 1][j] + 1);
				}
				if (j > 0) {
					min_distance[i][j] = min(min_distance[i][j], min_distance[i][j - 1] + 1);
				}
			}
		}
	}

	for (int i = m - 1; i >= 0; i--) {
		for (int j = n - 1; j >= 0; j--) {
			if (matrix[i][j] == 0) {
				min_distance[i][j] = 0;
			}
			else {
				if (i < m - 1) {
					min_distance[i][j] = min(min_distance[i][j], min_distance[i + 1][j] + 1);
				}
				if (j < n - 1) {
					min_distance[i][j] = min(min_distance[i][j], min_distance[i][j + 1] + 1);
				}
			}
		}
	}

	return min_distance;
}

/// <summary>
/// 221. Maximal Square
/// </summary>
int maximalSquare(vector<vector<char>>& matrix) {
	int m = matrix.size();
	int n = matrix[0].size();

	vector<vector<int>> side_length(m, vector<int>(n, 0));
	int max_length = 0;
	for (int i = 0; i < m; i++) {
		for (int j = 0; j < n; j++) {
			if (matrix[i][j] == '1') {
				if (i > 0 && j > 0) {
					side_length[i][j] = min({ side_length[i - 1][j],side_length[i][j - 1],side_length[i - 1][j - 1] }) + 1;
				}
				else {
					side_length[i][j] = 1;
				}
			}
			max_length = max(side_length[i][j], max_length);
		}
	}
	return max_length * max_length;
}


/// <summary>
/// 279. Perfect Squares
/// </summary>
int numSquares(int n) {
	const int kInfinIty = 65535;
	vector<int> least_nums(n + 1, kInfinIty);
	least_nums[0] = 0;
	for (int i = 1; i <= n; i++) {
		for (int j = 0; j*j <= i; j++) {
			least_nums[i] = min(least_nums[i], least_nums[i - j * j] + 1);
		}
	}
	return least_nums[n];
}

/// <summary>
/// 91. Decode Ways
/// </summary>
int numDecodings(string s) {
	vector<int> dp(s.size() + 1);
	
	if (s[0] == '0') {
		return 0;
	}
	if (s.size() < 2) {
		return 1;
	}
	

	dp[0] = 1;
	dp[1] = 1;

	for (int i =  2; i <= s.size(); i++) {
		int cur = i - 1;
		if (s[cur] == '0' && (s[cur - 1] < '1' || s[cur - 1] >'2')) {
			return 0;
		}
		if (s[cur - 1] == '2' && s[cur] <= '6' || (s[cur - 1] == '1' )) {
			if (s[cur] == '0') {
				dp[i] = dp[i - 2];
			}
			else {
				dp[i] = dp[i - 1] + dp[i - 2];
			}
		}
		else {
			dp[i] = dp[i -1];
		}
	}
	return dp[s.size()];
}

/// <summary>
/// 139. Word Break
/// </summary>
bool wordBreak(string s, vector<string>& wordDict) {
	int n = s.size();
	if (n == 0) {
		return true;
	}
	unordered_set<string> word_set;
	for (const auto& word : wordDict) {
		word_set.insert(word);
	}

	vector<bool> dp(n + 1, false);
	dp[0] = true;

	for (int i = 1; i <= n; i++) {
		int position_in_s = i - 1;
		for (int j = 0; j < i; j++) {
			int start_position_in_s = j;
			if (dp[j] == true) {
				string word = s.substr(start_position_in_s, position_in_s - start_position_in_s + 1);
				if (word_set.count(word)) {
					dp[i] = true;
					break;
				}
			}
			
		}
	}
	return dp[n];
}

/// <summary>
/// 300. Longest Increasing Subsequence
/// </summary>
int lengthOfLIS(vector<int>& nums) {
	int n = nums.size();
	vector<int> dp(n, 1);

	int max_lis = 1;
	for (int i = 1; i < n; i++) {
		int j = i - 1;
		for (int j = 0; j < i; j++) {
			if (nums[j] < nums[i]) {
				dp[i] = ::max(dp[j] + 1, dp[i]);
				max_lis = ::max(dp[i], max_lis);
			}
		}

	}

	return max_lis;
}

/// <summary>
/// 1143. Longest Common Subsequence
/// </summary>
int longestCommonSubsequence(string text1, string text2) {  ///< 算法导论
	
	int m = text1.size();
	int n = text2.size();
	vector<vector<int>> dp(m + 1, vector<int>(n + 1, 0));

	for (int i = 1; i <= m; i++) {
		int position1 = i - 1;
		for (int j = 1; j <= n; j++) {
			int position2 = j - 1;
			if (text1[position1] == text2[position2]) {
				dp[i][j] = dp[i - 1][j - 1] + 1;
			}
			else {
				dp[i][j] = ::max(dp[i - 1][j], dp[i][j - 1]);
			}
		}
	}
	return dp[m][n];
}

/// <summary>
/// 416. Partition Equal Subset Sum
/// </summary>
bool canPartition(vector<int>& nums) { ///< 转换成0-1背包问题，
	/// nums[i],同时表示物品的体积和价值
	int total_sum = 0;
	for (const auto& num : nums) {
		total_sum += num;
	}
	if (total_sum % 2 != 0) {
		return false;
	}

	int sum = total_sum / 2; ///表示背包容量，
	vector<int> f(sum + 1, 0);

	for (int i = 0; i < nums.size(); i++) {
		for (int j = sum; j >= nums[i]; j--) {
			f[j] = ::max(f[j - nums[i]] + nums[i], f[j]);
		}
		if (f[sum] == sum) {
			return true;
		}
	}
	
	return false;
}

/// <summary>
/// 474. Ones and Zeroes
/// </summary>
pair<int, int> CalculationWeightVolume(const string& s) {
int weight = 0;
int volume = 0;
for (int i = 0; i < s.size(); i++) {
	if (s[i] == '1') {
		volume++;
	}
	else {
		weight++;
	}
}
return ::make_pair(weight, volume);
}
int findMaxForm(vector<string>& strs, int m, int n) {
	/// 二维0-1背包问题，将m看作背包质量，n看作背包容量，每个string元素质量为包含0的数量，
	/// 体积为1的数量,价值为1，最后最大价值即为元素数量
	
	
	vector<vector<int>> f(m + 1, vector<int>(n + 1, 0));
	for (const auto& str : strs) {
		int weight = CalculationWeightVolume(str).first;
		int volume = CalculationWeightVolume(str).second;
		for (int j = m; j >= weight; j--) {
			for (int k = n; k >= volume; k--) {
				f[j][k] =::max(f[j][k], f[j - weight][k - volume] + 1);
			}
		}
	}
	return f[m][n];
}


/// <summary>
/// 322. Coin Change
/// </summary>
int coinChange(vector<int>& coins, int amount) {
	/// 完全背包问题,假设背包体积的amount,每个硬币体积为面额，价值为1，找到最小总价值
	int n = coins.size();

	vector<int> f(amount + 1, amount + 2);

	f[0] = 0;
	for (int i = 0; i < n; i++) {
		for (int j = coins[i]; j <= amount; j++) {
			f[j] = ::min(f[j - coins[i]] + 1, f[j]);
		}
	}
	if (f[amount] != amount + 2) {
		return f[amount];
	}
	return -1;
}

/// <summary>
/// 72. Edit Distance
/// </summary>
int minDistance(string word1, string word2) {
	/// <summary>
	/// 从最长公共子序列获得思路，
	/// 二维数组min_distance[i][j]表示：word1前i个元素，转换成word2前j个元素，需要多少步骤
	/// 状态转换：
	///		1.word1[i - 1] == word2[j - 1] 字符相等，
	///			状态不变min_distance[i][j] = min_distance[i - 1][j - 1]	
	///		2.不相等min_distance[i][j] = min( min_distance[i - 1][j], min_distance[i][j - 1], min_distance[i - 1][j - 1] ) + 1
	///			min_distance[i - 1][j] + 1			word1 删除一个元素，操作加1	（相对word2添加一个元素）
	///			min_distance[i][j - 1] + 1			word2 删除一个元素，操作加1 （相对word1添加一个元素）
	///			min_distance[i - 1][j - 1] + 1		修改元素,操作加1
	/// </summary>
	
	int m = word1.size();
	int n = word2.size();
	vector<vector<int>> min_distance(m + 1, vector<int>(n + 1, 0));
	for (int i = 1; i < n + 1; i++) {
		min_distance[0][i] = i;
	}
	for (int i = 1; i < m + 1; i++) {
		min_distance[i][0] = i;
	}

	for (int i = 1; i <= m; i++) {
		int position1 = i - 1;
		for (int j = 1; j <= n; j++) {
			int position2 = j - 1;
			if (word1[position1] == word2[position2]) {
				min_distance[i][j] = min_distance[i - 1][j - 1];
			}
			else {
				min_distance[i][j] = ::min({ min_distance[i - 1][j], min_distance[i][j - 1], min_distance[i - 1][j - 1] }) + 1;
				
			}
		}
	}
	return min_distance[m][n];
}

/// <summary>
/// 583. Delete Operation for Two Strings
/// </summary>
int minDistanceII(string word1, string word2) {
	vector<vector<int>> dp(word1.size() + 1, vector<int>(word2.size() + 1, 0));
	for (int i = 1; i <= word1.size(); i++) {
		dp[i][0] = i;
	}
	for (int i = 1; i <= word2.size(); i++) {
		dp[0][i] = i;
	}

	for (int i = 1; i <= word1.size(); i++) {
		for (int j = 1; j <= word2.size(); j++) {
			if (word1[i - 1] == word2[j - 1]) {
				dp[i][j] = dp[i - 1][j - 1];
			}
			else {
				//删除word1元素，删除word2元素和同时删除两个元素，使得两字符串相等，取最小操作步骤
				dp[i][j] = ::min({ dp[i - 1][j] + 1,dp[i][j - 1] + 1,dp[i - 1][j - 1] + 2 }); 
			}

		}
	}
	return dp[word1.size()][word2.size()];
}

/// <summary>
/// 650. 2 Keys Keyboard
/// </summary>
int minSteps(int n) {
	vector<int> steps(n + 1, n + 1);
	steps[1] = 0;
	for (int i = 2; i <= n; i++) {
		for (int j = 1; j < i; j++) {
			if (i % j == 0) {
				int times = i / j;
				steps[i] = ::min(steps[j] + times,steps[i]);
			}
		}
	}
	return steps[n];
}

/// <summary>
/// 10. Regular Expression Matching
/// </summary>
bool isMatch(string s, string p) {
	/// <summary>
	/// 二维数组dp[i][j] 表示s中前i个字符与p中前j个字符是否匹配
	/// 状态方程： 
	///		1. s[i - 1] == p[j - 1] s中第i个字符与p中第j个字符相等(.与任何字符都相等)：
	///			dp[i][j] = dp[i - 1][j - 1];
	///		2. 不相等且p[j - 1]!= *
	///			dp[i][j] = false
	///		3. p[j - 1] = '*'
	///			1）若p[j - 2] != s[i - 1]
	///				考虑前字符出现0次的情况 dp[i][j] = dp[i][j - 2];
	///			2）若p[j - 2] == s[i - 1] 或者p[j - 2] == '.'
	///				则有三种情况，
	///					前字符出现0次的情况 ： dp[i][j] = dp[i][j - 2]；
	///					假设* 与当前字符匹配：  dp[i][j] = dp[i - 1][j - 1]；
	///					*与.搭配			:	dp[i][j] = dp[i - 1][j - 1] || dp[i - 1][j];
	/// </summary>
	
	int m = s.size();
	int n = p.size();
	vector<vector<bool>> dp(m + 1, vector<bool>(n + 1, false));
	dp[0][0] = true;
	for (int i = 2; i <= n; i++) {
		int position_p = i - 1;
		if (p[position_p] == '*') {
			dp[0][i] = dp[0][i - 2];
		}
	}

	for (int i = 1; i <= m; i++) {
		int position_s = i - 1;
		for (int j = 1; j <= n; j++) {
			int position_p = j - 1;
			if (s[position_s] == p[position_p] || p[position_p] == '.') {
				dp[i][j] = dp[i - 1][j - 1];
			}else if(p[position_p] == '*'){
				if (s[position_s] == p[position_p - 1] || p[position_p - 1] == '.') {
					dp[i][j] = dp[i - 1][j - 1] || dp[i - 1][j] || dp[i][j - 2];
				}
				else {
					dp[i][j] = dp[i][j - 2];
				}
			}

		}
	}
	for (auto a : dp) {
		for (auto p : a) {
			cout << p << " ";
		}
		cout << endl;
	}
	return dp[m][n];
}


/// <summary>
/// 121. Best Time to Buy and Sell Stock
/// </summary>
int maxProfit(vector<int>& prices) {
	int min_price = INT_MAX;
	int max_profit = 0;
	for (int i = 0; i < prices.size(); i++) {
		min_price = ::min(min_price, prices[i]);
		max_profit = ::max(max_profit, prices[i] - min_price);
	}
	return max_profit;
}

/// <summary>
/// 188. Best Time to Buy and Sell Stock IV
/// </summary>
int maxProfitIVHelper(vector<int>& prices);
int maxProfitIV(int k, vector<int>& prices) {
	/// <summary>
	/// dp[i][j][0] 表示第i天，操作j次，最后没有股票，手中的钱
	/// dp[i][j][1] 表示第i天，操作j次，最后又股票，手中的钱
	/// </summary>
	
	int days = prices.size();

	if (k > days / 2) {					///< 可以看作无限次操作，一次操作最少需要2天
		return maxProfitIVHelper(prices);
	}
	vector<vector<vector<int>>> dp(days + 1, vector<vector<int>>(k + 1, vector<int>(2, 0)));
	for (int i = 1; i <= k; i++) {
		dp[0][i][0] = 0;
		dp[0][i][1] = -prices[0];
	}

	for (int i = 1; i <= days; i++) {
		for (int j = 1; j <= k; j++) {
			//// dp[i] 只与 dp[i-1]相关，可进行空间压缩
			dp[i][j][0] = ::max(dp[i - 1][j][0], dp[i - 1][j][1] + prices[i - 1]); 
			dp[i][j][1] = ::max(dp[i - 1][j][1], dp[i - 1][j - 1][0] - prices[i - 1]);
		}
	}

	return dp[days][k][0];
}

int maxProfitIVHelper(vector<int>& prices) {

	int days = prices.size();
	int max_profit = 0;
	for (int i = 1; i < days; i++) {
		max_profit += ::max(prices[i] - prices[i - 1], 0);
	}
	return max_profit;
}

/// <summary>
/// 309. Best Time to Buy and Sell Stock with Cooldown
/// </summary>
int maxProfitCooldown(vector<int>& prices) {
	/// <summary>
	/// dp[i][0] 表示第i天，手中没有股票时的钱
	/// dp[i][1] 表示第i天，手中有股票时的钱
	///		1.dp[i][0] = max(dp[i - 1][0], dp[i - 1][1] + prices[i]);
	///		2.dp[i][1] = max(dp[i - 1][1],dp[i - 1][0] - price[i])
	///		 然而dp[i - 1][0] = max(dp[i - 2][0], dp[i - 2][1] + prices[i - 1])
	///		 由于存在冷却时间，今天要买入股票，前一天不能卖出股票，所以此时
	///		 dp[i - 1][0]只能由dp[i - 2][0]转化而来，
	///		 所以：
	///		 dp[i][1] = max(dp[i - 1][1],dp[i - 2][0] - price[i])；
	/// </summary>
	
	int days = prices.size();
	if (days < 2) {
		return 0;
	}
	vector<vector<int>> dp(days, vector<int>(2, 0));
	dp[0][0] = 0;
	dp[0][1] = -prices[0];

	for (int i = 1; i < days; i++) {
		dp[i][0] = ::max(dp[i - 1][0], dp[i - 1][1] + prices[i]);
		dp[i][1] = ::max(dp[i - 1][1], (i >= 2 ? dp[i - 2][0] : 0) - prices[i]);
	}
	return dp[days - 1][0];
}

/// <summary>
/// 714. Best Time to Buy and Sell Stock with Transaction Fee
/// </summary>
int maxProfitFee(vector<int>& prices, int fee) {
	/// <summary>
	/// dp[i][0] 表示第i天，手中没有股票时的钱
	/// dp[i][1] 表示第i天，手中有股票时的钱
	/// </summary>
	int days = prices.size();
	if (days < 2) {
		return 0;
	}
	vector<vector<int>> dp(days, vector<int>(2, 0));
	dp[0][0] = 0;
	dp[0][1] = -prices[0];

	for (int i = 1; i < days; i++) {
		dp[i][0] = ::max(dp[i - 1][0], dp[i - 1][1] + prices[i] - fee);
		dp[i][1] = ::max(dp[i - 1][1], dp[i - 1][0] - prices[i]);
	}
	return dp[days - 1][0];
}

/// <summary>
/// 53. Maximum Subarray
/// </summary>
int maxSubArray(vector<int>& nums) {
	int value;
	value = nums[0];
	int max_sub = value;
	for (int i = 1; i < nums.size(); i++) {
		value = ::max(value + nums[i], nums[i]);
		max_sub = ::max(value, max_sub);
	}
	return max_sub;
}

/// <summary>
/// 213. House Robber II
/// </summary>
int robII(vector<int>& nums) {
	/// <summary>
	/// 头尾不能同时取，可以分为[1:len] 和[0:len-1]两部分求金额，取最大值
	/// </summary>
	int len = nums.size();
	if (len == 1) {
		return nums[0];
	}
	if (len == 2) {
		return ::max(nums[0], nums[1]);
	}
	if (len == 3) {
		return ::max({ nums[0], nums[1],nums[2] });
	}
	vector<int> dp1(len - 1, 0);
	vector<int> dp2(len - 1, 0);
	
	dp1[0] = nums[0];
	dp1[1] = ::max(dp1[0],nums[1]);

	dp2[0] = nums[1];
	dp2[1] = ::max(dp2[0], nums[2]);
	for (int i = 2; i < len - 1; i++) {
		dp1[i] = ::max(dp1[i - 1], dp1[i - 2] + nums[i]);
		dp2[i] = ::max(dp2[i - 1], dp2[i - 2] + nums[i + 1]);
	}
	return ::max(dp1[len - 2], dp2[len - 2]);
}

/// <summary>
/// 343. Integer Break
/// </summary>
int integerBreak(int n) {
	vector<int> dp(n + 1, 0);
	for (int i = 2; i <= n; i++) {
		for (int j = 1; j < i ; j++) {
			dp[i] = ::max(dp[i], ::max(j * dp[i - j], j * (i - j)));
		}
		
	}
	return dp[n];
}

/// <summary>
/// 494. Target Sum
/// </summary>
int count_494 = 0;
void findTargetSumWayshelper(vector<int>& nums,int sum,int S,int index) {
	if (index == nums.size()) {
		if(sum == S)
			count_494++;
		return;
	}
	
	int sign[2] = { 1,-1 };
	for (int i = 0; i < 2; i++) {
		sum += nums[index] * sign[i];
		findTargetSumWayshelper(nums, sum, S, index + 1);
		sum -= nums[index] * sign[i];
	}
}
int findTargetSumWays(vector<int>& nums, int S) {
	// findTargetSumWayshelper(nums, 0, S, 0); 回溯法，超时

	/// <summary>
	/// 转化为0-1背包问题;
	/// 设x为某种可能选择中的正数和，-y为负数和
	///		x-y = S
	///		x+y = sum(nums)
	///		=>x = (S + sum(nums)) / 2  转化为背包容量 x,找出装满背包的方案总数
	/// </summary>
	int sum = 0;
	for (const auto& num : nums) {
		sum += num;
	}
	
	if (sum < S || (S + sum) % 2 != 0) {
		return 0;
	}
	int x = (S + sum) / 2;
	
	vector<int> dp(x + 1, 0);
	dp[0] = 1;
	for (const auto& num : nums) {
		for (int i = x; i >= num; i--) {
			dp[i] = dp[i - num] + dp[i]; ///< dp[i - num] 表示上一个这个数放入正好装满体积为i的背包
										 /// dp[i] 表示上一个数放入已经使得体积为i背包满了，这次不放	
		}
	}
	return dp[x];
}

/// <summary>
/// 646. Maximum Length of Pair Chain
/// </summary>
int findLongestChain(vector<vector<int>>& pairs) {
	auto cmp = [](vector<int> a, vector<int> b) {
		return a[1] < b[1];
	};
	::sort(pairs.begin(), pairs.end(), cmp);

	vector<int> dp(pairs.size(), 1);
	int longest_chain = 0;
	for (int i = 1; i < dp.size(); i++) {
		for (int j = 0; j < i; j ++) {
			if (pairs[j][1] < pairs[i][0]) {
				dp[i] = ::max(dp[j] + 1,dp[i]);
			}
		}
		longest_chain = ::max(longest_chain, dp[i]);
	}
	
	return longest_chain;
}

/// <summary>
/// 376. Wiggle Subsequence
/// </summary>
int wiggleMaxLength(vector<int>& nums) {
	int len = nums.size();
	if (len <= 1) {
		return len;
	}
	vector<int> difference(len - 1);
	for (int i = 1; i < len; i++) {
		difference[i - 1] = nums[i] - nums[i - 1];
	}

	vector<int> dp(len - 1, 1);
	int front_zeros = 0;
	while (front_zeros < len - 1 && difference[front_zeros] == 0) {
		dp[front_zeros] = 0;
		front_zeros++;
	}
	int max_length = 0;
	for (int i = front_zeros; i < len - 1; i++) {
		for (int j = 0; j < i; j++) {
			if (difference[i] * difference[j] < 0) {
				dp[i] = ::max(dp[j] + 1, dp[i]);
			}
		}
		max_length = ::max(dp[i], max_length);
	}
	return max_length + 1;
}