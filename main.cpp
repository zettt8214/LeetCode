#include <unordered_map>
#include <algorithm>
#include <set>
#include <unordered_set>
#include <iostream>
#include "Sort\sort.h"
#include "Greedy\greedy.h"
#include "Search\search.h"
#include "Dynamic Programming\dp.h"
#include "Divide and Conquer\divide_conquer.h"

using namespace std;
int main() {
	vector<vector<int>> p = { {10,16} ,{2,8},{1,6},{7,12} };
	vector<vector<int>> q = { {1,2},{3, 4}, {5, 6},{7, 8} };
	vector<vector<int>> g = { {3,9},{7,12},{3,8},{6,8},{9,10},{2,9},{0,9},{3,9},{0,6},{2,8} };
	vector<vector<int>> f = { {9,12},{1,10},{4,11},{8,12},{3,9},{6,9},{6,7} };
	vector<vector<int>> people = { {{9,0},{7,0},{1,9},{3,0},{2,7},{5,3},{6,0},{3,4},{6,2},{5,2}} };
	vector<vector<int>> nums = { {1} };
	vector<int> nums2 = { 3,4,1 };
	vector<int> nums_sort = { 4,3,5,7,2,11,88,2,77,100,22 };
	vector<int> temp(nums_sort.size());

	vector < vector<int >> grid = { {0, 0, 0, 0, 0, 0}, {0, 1, 0, 0, 0, 0}, {1, 1, 0, 0, 0, 0}, {1, 1, 0, 0, 0, 0}, {0, 0, 0, 0, 0, 0}, {0, 0, 1, 1, 0, 0} };
	vector < vector<int >> ans = pacificAtlantic(grid);

	vector<vector<string>> result = solveNQueens(4);
	string beginWord = "cat";
	string endWord = "fin";
	vector<string> wordList = { "ion","rev","che","ind","lie","wis","oct","ham","jag","ray","nun","ref","wig","jul","ken","mit","eel","paw","per","ola","pat","old","maj","ell","irk","ivy","beg","fan","rap","sun","yak","sat","fit","tom","fin","bug","can","hes","col","pep","tug","ump","arc","fee","lee","ohs","eli","nay","raw","lot","mat","egg","cat","pol","fat","joe","pis","dot","jaw","hat","roe","ada","mac" };


	vector<vector<string>> res = findLaddersByTwoWayBfs(beginWord, endWord, wordList);


	string beginWord1 = "hit";
	string endWord1 = "cog";
	vector<string> wordList1 = { "hot","dot","dog","lot","log","cog" };
	//res = findLaddersByTwoWayBfs(beginWord1, endWord1, wordList1);
	TreeNode n5(5);
	TreeNode n2(2, &n5);
	TreeNode n3(3);
	TreeNode root(1, &n2, &n3);

	vector<string> s = binaryTreePaths(&root);

	//vector<int> a = { 1,1,3 };
	//permuteUnique(a);
	//vector<int> candidates = { 2,5,2,1,2 };
	//int target = 5;
	//combinationSum2(candidates, target);
	/*vector<vector<char>> board = {
		{'5', '3', '.', '.', '7', '.', '.', '.', '.'},
		{'6', '.', '.', '1', '9', '5', '.', '.', '.'},
		{'.', '9', '8', '.', '.', '.', '.', '6', '.'},
		{'8', '.', '.', '.', '6', '.', '.', '.', '3'},
		{'4', '.', '.', '8', '.', '3', '.', '.', '1'},
		{'7', '.', '.', '.', '2', '.', '.', '.', '6'},
		{'.', '6', '.', '.', '.', '.', '2', '8', '.'},
		{'.', '.', '.', '4', '1', '9', '.', '.', '5'},
		{'.', '.', '.', '.', '8', '.', '.', '7', '9'} };
	solveSudoku(board);*/

	//cout << climbStairs(1);
	//cout << numDecodings("2611055971756562");
	beautifulArray(7);
}
//"aasdfasdfasdfasdfas"
//"aasdf.*asdf.*asdf.*asdf.*s"