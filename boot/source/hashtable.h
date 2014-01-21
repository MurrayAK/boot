#ifndef HASHTABLE_H
#define HASHTABLE_H

#include <iostream>
#include <string>

class HashTable {

private:
	static const int tableSize = 4;

	struct HashItem {
		std::string key;
		std::string data;
		HashItem* next;
	};

	HashItem* table[tableSize];

public:
	HashTable();
	~HashTable();
	int Hash(std::string item);
	void AddItem(std::string item, std::string value);
	void RemoveItem(std::string item);
	void FindValue(std::string item);
	int NumberOfItemsInIndex(int index);
	void PrintTable();
	void PrintItemsInIndex(int index);
	
};

#endif
