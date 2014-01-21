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
	int NumberOfItemsInIndex(int index);
	void PrintTable();
	void PrintItemsInIndex(int index);
	void FindValue(std::string item);
	void RemoveItem(std::string item);

};

#endif
