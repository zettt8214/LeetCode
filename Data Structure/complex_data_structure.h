#pragma once
#include <vector>
#include <list>
using std::vector;



class UnionFind {
	struct element {
		int rank;
		int parent;
	};
	vector<element> set_;
public:
	UnionFind(int size) {
		set_.resize(size);
		for (int i = 1; i < size; i++) {
			set_[i].parent = i;
			set_[i].rank = 0;
		}
	}

	void Link(int x,int y) {
		int set1 = FindSet(x);
		int set2 = FindSet(y);

		if (set_[set1].rank > set_[set2].rank) {
			set_[set2].parent = set1;
		}
		else {
			set_[set1].parent = set2;
			if (set_[set1].rank == set_[set2].rank) {
				set_[set2].rank++;
			}
		}
	}

	int FindSet(int x) {
		if (x != set_[x].parent) {
			set_[x].parent = FindSet(set_[x].parent);
		}
		return set_[x].parent;
	}
	
};

vector<int> findRedundantConnection(vector<vector<int>>& edges);	/// 684. Redundant Connection