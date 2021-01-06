#include <unordered_map>
#include <algorithm>
#include "Sort\sort.h"
#include "Sort\my_sort.h"
#include "Greedy\greedy.h"
#include "Search\search.h"

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
	
	vector < vector<int >> grid = {{1, 2, 3}, {8, 9, 4}, {7, 6, 5}};
	vector < vector<int >> ans = pacificAtlantic(grid);
	for (auto x : ans) {
		cout << "(" << x[0] << "," << x[1] << ") ";
	}
	return 0;
}