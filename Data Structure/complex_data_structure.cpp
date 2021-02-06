#include <utility>
#include <unordered_map>
#include "complex_data_structure.h"

using namespace std;
/// <summary>
/// 684. Redundant Connection
/// </summary>
vector<int> findRedundantConnection(vector<vector<int>>& edges) {
	int size = edges.size();
	if (!size) {
		return  {};
	}

	UnionFind uf(size + 1);
	for (auto edge : edges) {
		int x = edge[0];
		int y = edge[1];

		if (uf.FindSet(x) != uf.FindSet(y)) {
			uf.Link(x, y);
		}
		else {
			return edge;
		}
	}
	return {};
}

/// <summary>
/// 146. LRU Cache
/// </summary>
class LRUCache {
	list<pair<int,int>> cache_;
	unordered_map<int, list<pair<int, int>>::iterator> hash;
	int size;
public:
	LRUCache(int capacity) {
		size = capacity;
	}

	int get(int key) {
		if (hash.find(key) == hash.end()) {
			return -1;
		}
		cache_.splice(cache_.begin(), cache_, hash[key]);

		return hash[key]->second;
		
	}

	void put(int key, int value) {
		if (hash.find(key) != hash.end()) {
			cache_.splice(cache_.begin(), cache_, hash[key]);
			hash[key]->second = value;
		}
		else {
			if (size == cache_.size()) {
				hash.erase(cache_.back().first);
				cache_.pop_back();
			}
			cache_.insert(cache_.begin(), pair<int, int>(key, value));
			hash[key] = cache_.begin();
		}

	}
};


/// <summary>
/// 380. Insert Delete GetRandom O(1)
/// </summary>
class RandomizedSet {
	vector<int> a;
	unordered_map<int, int> hash;

public:
	/** Initialize your data structure here. */
	RandomizedSet() {

	}

	void swap(vector<int>& nums, int x, int y) {
		int temp = nums[x];
		nums[x] = nums[y];
		nums[y] = temp;
	}
	/** Inserts a value to the set. Returns true if the set did not already contain the specified element. */
	bool insert(int val) {
		if (hash.find(val) != hash.end()) {
			return false;
		}
		a.push_back(val);
		hash.insert(pair<int, int>(val, a.size() - 1));
		return true;
	}

	/** Removes a value from the set. Returns true if the set contained the specified element. */
	bool remove(int val) {
		if (hash.find(val) == hash.end()) {
			return false;
		}
		int index = hash[val];
		swap(a, index, a.size() - 1);
		a.pop_back();

		hash[a[index]] = index;
		hash.erase(val);
		return true;
	}

	/** Get a random element from the set. */
	int getRandom() {
		return a[rand() % a.size()];
	}
};