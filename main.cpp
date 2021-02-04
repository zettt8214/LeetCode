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
#include "Data Structure\data_structure.h"
#include "String\str.h"
#include "Data Structure\list.h"
#include "Data Structure\tree.h"

using namespace std;

int main() {
	vector<int> nodes1 = { 1,65535,2};
	vector<int> nodes2 = { 15,7,20 };
	vector<int> list = { -10, -3, 0, 5, 9 };
	ListNode* l = createList(list);
	TreeNode* t1 = createTree(nodes1);
	TreeNode* t2 = createTree(nodes2);
	deleteNode(t1,1);
}
