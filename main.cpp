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


using namespace std;

int main() {
	ListNode n0(0);
	ListNode n4(4, &n0);
	ListNode n3(3, &n4);
	ListNode n5(5, &n3);
	ListNode n1(-1, &n5);
	sortList(&n1);

}
