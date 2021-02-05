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
#include "Data Structure\graph.h"
using namespace std;

int main() {
	vector<vector<int>> a = {
		{1,0},
		{0,1}
	};
	cout << canFinish(2, a);

}
