#include "stdafx.h"
class LRUCache {
public:
	LRUCache(int demo) 
		: capacity(demo){
		
	}

	int get(int key) {
		if (Test.find(key) != Test.end()){
			put(key, Test[key]);
			return Test[key];
		}
		return -1;
	}

	void put(int key, int value) {
		if (Test.find(key) != Test.end()){
			Test.find(key)->second = value;
		}
		List_Test.push_front({ key, value });

		if (List_Test.size() > capacity){
			Test.erase(List_Test.back().first);
			List_Test.pop_back();
		}

		Test.find(key)->second = List_Test.begin()->second;
	}
private:
	int capacity;
	list<pair<int, int>>List_Test;
	unordered_map<int, int>Test;
};
void Test146(){
	LRUCache Lru(2);
	Lru.put(1, 1);
	Lru.put(2, 2);
	Lru.get(1);
	Lru.put(3, 3); 
	Lru.get(2);
	system("pause");
}