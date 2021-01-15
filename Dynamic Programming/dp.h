#pragma once
#include <vector>
#include <string>
using std::vector;
using std::string;

int climbStairs(int n);											//70. Climbing Stairs
int rob(vector<int>& nums);										//198. House Robber
int minPathSum(vector<vector<int>>& grid);						//64. Minimum Path Sum
int numberOfArithmeticSlices(vector<int>& A);					//413. Arithmetic Slices
vector<vector<int>> updateMatrix(vector<vector<int>>& matrix);	//542. 01 Matrix
int maximalSquare(vector<vector<char>>& matrix);				//221. Maximal Square
int numSquares(int n);											//279. Perfect Squares
int numDecodings(string s);										//91. Decode Ways
bool wordBreak(string s, vector<string>& wordDict);				//139. Word Break
int lengthOfLIS(vector<int>& nums);								//300. Longest Increasing Subsequence
int longestCommonSubsequence(string text1, string text2);		//1143. Longest Common Subsequence
bool canPartition(vector<int>& nums);							//416. Partition Equal Subset Sum
int findMaxForm(vector<string>& strs, int m, int n);			//474. Ones and Zeroes
int coinChange(vector<int>& coins, int amount);					//322. Coin Change
int minDistance(string word1, string word2);					//72. Edit Distance
int minSteps(int n);											//650. 2 Keys Keyboard
bool isMatch(string s, string p);								//10. Regular Expression Matching
int maxProfit(vector<int>& prices);								//121. Best Time to Buy and Sell Stock
int maxProfitIV(int k, vector<int>& prices);					//188. Best Time to Buy and Sell Stock IV
int maxProfitCooldown(vector<int>& prices);						//309. Best Time to Buy and Sell Stock with Cooldown
int maxProfitFee(vector<int>& prices, int fee);					//714. Best Time to Buy and Sell Stock with Transaction Fee
int maxSubArray(vector<int>& nums);								//53. Maximum Subarray
int robII(vector<int>& nums);									//213. House Robber II
int integerBreak(int n);										//343. Integer Break
int findTargetSumWays(vector<int>& nums, int S);				//494. Target Sum
int findLongestChain(vector<vector<int>>& pairs);				//646. Maximum Length of Pair Chain
int wiggleMaxLength(vector<int>& nums);							//376. Wiggle Subsequence