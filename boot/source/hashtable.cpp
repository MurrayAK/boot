#include "hashtable.h"

HashTable::HashTable() 
{
	for (int i = 0; i < tableSize; i++)
	{
		table[i] = new HashItem;

		table[i]->key = "empty";
		table[i]->data = "empty";

		table[i]->next = nullptr;
	}
}

HashTable::~HashTable() 
{

}

void HashTable::AddItem(std::string item, std::string value)
{
	int index = Hash(item);

	if (table[index]->key == "empty")
	{
		table[index]->key = item;
		table[index]->data = value;
	}
	else
	{
		HashItem* ptr = table[index];
		HashItem* n = new HashItem;

		n->key = item;
		n->data = value;
		n->next = nullptr;

		while (ptr->next != nullptr) 
			ptr = ptr->next;

		ptr->next = n;
	}
}

void HashTable::RemoveItem(std::string item)
{
	int index = Hash(item);

	HashItem* delPtr;
	HashItem* p1;
	HashItem* p2;

	// Case 0 - bucket/index is empty
	if (table[index]->key == "empty" && table[index]->data == "empty")
	{
		std::cout << item << " was not found in the Hash Table\n";
	}

	// Case 1 - only 1 item contained in the bucket/index and that item has matching item name
	else if (table[index]->key == item && table[index]->next == nullptr)
	{
		table[index]->key = "empty";
		table[index]->data = "empty";

		std::cout << item << " was removed from the Hash Table\n";
	}

	// Case 2 - match is located in the first item in the bucket/index but there are more items in the bucket/index
	else if (table[index]->key == item)
	{
		delPtr = table[index];
		table[index] = table[index]->next;

		delete delPtr;
		std::cout << item << " was removed from the Hash Table\n";
	}

	// Case 3 - bucket/index contains items but first item is not a match
	else 
	{
		p1 = table[index]->next;
		p2 = table[index];

		while (p1 != nullptr && p1->key != item)
		{
			p2 = p1;
			p1 = p1->next;
		}

		// Case 3.1 - no match
		if (p1 == nullptr)
		{
			std::cout << item << " was not found in the Hash Table\n";
		}

		// Case 3.2 - match is found
		else
		{
			delPtr = p1;
			p1 = p1->next;
			p2->next = p1;

			delete delPtr;
			std::cout << item << " was removed from the Hash Table\n";
		}
	}
}

void HashTable::FindValue(std::string item)
{
	int index = Hash(item);
	bool foundName = false;
	std::string value;

	HashItem* ptr = table[index];

	while (ptr != nullptr)
	{
		if (ptr->key == item)
		{
			foundName = true;
			value = ptr->data;
		}

		ptr = ptr->next;
	}

	if (foundName == true)
	{
		std::cout << "Value = " << value << std::endl; 
	}
	else
	{
		std::cout << item << "'s data was not found in the Hash Table";
	}
}

int HashTable::NumberOfItemsInIndex(int index)
{
	int count = 0;
	
	if (table[index]->key == "empty")
	{
		return count;
	}
	else
	{
		count++;

		HashItem* ptr = table[index];
		
		while (ptr->next != nullptr)
		{
			count++;
			ptr = ptr->next;
		}
	}

	return count;
}

void HashTable::PrintTable()
{
	int number;

	for (int i = 0; i < tableSize; i++)
	{
		number = NumberOfItemsInIndex(i);

		std::cout << "-------------------------------\n";
		std::cout << "index = " << i << std::endl;
		std::cout << table[i]->key << std::endl;
		std::cout << table[i]->data << std::endl;
		std::cout << "# of Items = " << number << std::endl;
		std::cout << "-------------------------------\n";
	}
}

void HashTable::PrintItemsInIndex(int index)
{
	HashItem* ptr = table[index];

	if (ptr->key == "empty")
	{
		std::cout << "index = " << index << " is empty" << std::endl;
	}
	else
	{
		std::cout << "index " << index << " contains the following items\n";

		while (ptr != nullptr)
		{
			std::cout << "---------------------\n";
			std::cout << ptr->key << std::endl;
			std::cout << ptr->data << std::endl;
			std::cout << "---------------------\n";

			ptr = ptr->next;
		}
	}
}

int HashTable::Hash(std::string item) 
{
	int hash = 0;
	int index;

	for (int i = 0; i < (int) item.length(); i++)
	{
		hash = (hash + (int)item[i]) * 17;
	}

	index = hash % tableSize;

	return index;
}