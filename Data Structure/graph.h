#pragma once
#include <vector>
using std::vector;

bool isBipartite(vector<vector<int>>& graph);								/// 785. Is Graph Bipartite?
bool canFinish(int numCourses, vector<vector<int>>& prerequisites);			/// 207. Course Schedule
vector<int> findOrder(int numCourses, vector<vector<int>>& prerequisites);	/// 210. Course Schedule II
