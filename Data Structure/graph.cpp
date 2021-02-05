#include <queue>
#include "graph.h"

using namespace std;

/// <summary>
/// 785. Is Graph Bipartite?
/// </summary>
typedef struct vertex {
	int color = 0;
	bool is_visited = false;
}vertex;

bool isBipartite(vector<vector<int>>& graph) {
	enum  { BLACK = 1, WHITE };
	int vertex_num = graph.size();
	vector<vertex> vertexs(vertex_num);
	queue<int> q;
	
	for (int i = 0; i < vertex_num; i++) {
		if (!vertexs[i].is_visited) {
			vertexs[i].is_visited = true;
			vertexs[i].color = BLACK;
			q.push(i);
		}

		while (!q.empty()) {
			int vertex_index = q.front();
			q.pop();
			for (int i = 0; i < graph[vertex_index].size(); i++) {
				int next_vertex = graph[vertex_index][i];

				if (!vertexs[next_vertex].is_visited) {
					vertexs[next_vertex].color = (vertexs[vertex_index].color == BLACK ? WHITE : BLACK);
					vertexs[next_vertex].is_visited = true;
					q.push(next_vertex);
				}
				else {
					if (vertexs[next_vertex].color == vertexs[vertex_index].color) {
						return false;
					}
				}

			}
		}
	}
	return true;
}

/// <summary>
/// 207. Course Schedule
/// </summary>
bool canFinishHelper(vector<vector<int>>& graph, vector<int>& visited,int index) {
	visited[index] = 1;
	for (auto next_courses : graph[index]) {
		if (visited[next_courses] == 1) {
			return false;
		}

		if (visited[next_courses] == 0) {
			if (!canFinishHelper(graph, visited, next_courses)) {
				return false;
			}
		}
	}
	visited[index] = 2;
	return true;
}

bool canFinish(int numCourses, vector<vector<int>>& prerequisites) {
	vector<vector<int>> graph(numCourses);
	vector<int> visited(numCourses,0);

	for (int i = 0; i < prerequisites.size(); i++) {
		graph[prerequisites[i][1]].push_back(prerequisites[i][0]);
	}

	for (int i = 0; i < numCourses; i++) {
		if (visited[i] == 0) {
			if (!canFinishHelper(graph, visited, i)) {
				return false;
			}
		}
	}
	return true;
}

/// <summary>
/// 210. Course Schedule II
/// </summary>
struct curriculum {
	int index = -1;
	int finish = 0;
	int is_visited = 0;
};
int time = 0;
bool dfs(vector<vector<int>>& graph, vector<curriculum>& courses,int index_courses) {
	time++;
	courses[index_courses].is_visited = 1;
	for (auto next_courses : graph[index_courses]) {
		if (courses[next_courses].is_visited == 1) {
			return false;
		}

		if (courses[next_courses].is_visited == 0) {
			if (!dfs(graph, courses, next_courses)) {
				return false;
			}
		}
	}
	courses[index_courses].is_visited = 2;
	time++;
	courses[index_courses].finish = time;
	return true;
}
vector<int> findOrder(int numCourses, vector<vector<int>>& prerequisites) {
	vector<vector<int>> graph(numCourses);
	vector<curriculum> courses(numCourses);
	for (int i = 0; i < numCourses; i++) {
		courses[i].index = i;
	}
	for (int i = 0; i < prerequisites.size(); i++) {
		graph[prerequisites[i][1]].push_back(prerequisites[i][0]);
	}

	for (int i = 0; i < numCourses; i++) {
		if (courses[i].is_visited == 0) {
			if (!dfs(graph, courses, i)) {
				return {};
			}
		}
	}
	::sort(courses.begin(), courses.end(), [](curriculum& c1, curriculum& c2) {return c1.finish > c2.finish; });
	vector<int> ans;
	for (int i = 0; i < numCourses; i++) {
		ans.push_back(courses[i].index);
	}
	return ans;
}

