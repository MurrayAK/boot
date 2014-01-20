#ifndef HASHMAP_H
#define HASHMAP_H

template <typename K, typename V, typename F = KeyHash<K>>

class HashMap {

private:
    // hash table
    HashNode<K, V> **table;
    F hashFunc;

public:
    HashMap() 
	{
        // construct zero initialized hash table of size
        table = new HashNode<K, V> *[TABLE_SIZE]();
    }

    ~HashMap()
	{
        // destroy all buckets one by one
        for (int i = 0; i < TABLE_SIZE; ++i) 
		{
            HashNode<K, V> *entry = table[i];

            while (entry != nullptr) {
                HashNode<K, V> *prev = entry;
                entry = entry->getNext();
                delete prev;
            }

            table[i] = nullptr;
        }

        // destroy the hash table
        delete [] table;
    }

    bool get(const K &key, V &value) 
	{
        unsigned long hashValue = hashFunc(key);
        HashNode<K, V> *entry = table[hashValue];

        while (entry != nullptr) {
            if (entry->getKey() == key) {
                value = entry->getValue();
                return true;
            }

            entry = entry->getNext();
        }

        return false;
    }

    void put(const K &key, const V &value) 
	{
        unsigned long hashValue = hashFunc(key);
        HashNode<K, V> *prev = nullptr;
        HashNode<K, V> *entry = table[hashValue];

        while (entry != nullptr && entry->getKey() != key) {
            prev = entry;
            entry = entry->getNext();
        }

        if (entry == nullptr) {
            entry = new HashNode<K, V>(key, value);

            if (prev == nullptr) {
                // insert as first bucket
                table[hashValue] = entry;
            } else {
                prev->setNext(entry);
            }

        } else {
            // just update the value
            entry->setValue(value);
        }
    }

    void remove(const K &key) 
	{
        unsigned long hashValue = hashFunc(key);
        HashNode<K, V> *prev = nullptr;
        HashNode<K, V> *entry = table[hashValue];

        while (entry != nullptr && entry->getKey() != key) {
            prev = entry;
            entry = entry->getNext();
        }

        if (entry == nullptr) {
            // key not found
            return;
        }
        else {
            if (prev == nullptr) {
                // remove first bucket of the list
                table[hashValue] = entry->getNext();
            } else {
                prev->setNext(entry->getNext());
            }

            delete entry;
        }
    }

};

#endif