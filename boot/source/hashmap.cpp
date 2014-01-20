#include <hashmap.h>

template <typename K, typename V, typename F = KeyHash<K>>
HashMap::HashMap() {
	// construct zero initialized hash table of size
	table = new HashNode<K, V> *[TABLE_SIZE]();
}

template <typename K, typename V, typename F = KeyHash<K>>
HashMap::~HashMap() {
	// destroy all buckets one by one
    for (int i = 0; i < TABLE_SIZE; ++i) {
        HashNode<K, V> *entry = table[i];
        while (entry != NULL) {
            HashNode<K, V> *prev = entry;
            entry = entry->getNext();
            delete prev;
        }
        table[i] = NULL;
    }
    // destroy the hash table
    delete [] table;
}

template <typename K, typename V, typename F = KeyHash<K>>
bool HashMap::get(const K &key, V &value) {
    unsigned long hashValue = hashFunc(key);
    HashNode<K, V> *entry = table[hashValue];

    while (entry != NULL) {
        if (entry->getKey() == key) {
            value = entry->getValue();
            return true;
        }
        entry = entry->getNext();
    }
    return false;
}

template <typename K, typename V, typename F = KeyHash<K>>
void HashMap::put(const K &key, const V &value) {
    unsigned long hashValue = hashFunc(key);
    HashNode<K, V> *prev = NULL;
    HashNode<K, V> *entry = table[hashValue];

    while (entry != NULL && entry->getKey() != key) {
        prev = entry;
        entry = entry->getNext();
    }

    if (entry == NULL) {
        entry = new HashNode<K, V>(key, value);
        if (prev == NULL) {
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

template <typename K, typename V, typename F = KeyHash<K>>
void HashMap::remove(const K &key) {
    unsigned long hashValue = hashFunc(key);
    HashNode<K, V> *prev = NULL;
    HashNode<K, V> *entry = table[hashValue];

    while (entry != NULL && entry->getKey() != key) {
        prev = entry;
        entry = entry->getNext();
    }

    if (entry == NULL) {
        // key not found
        return;
    }
    else {
        if (prev == NULL) {
            // remove first bucket of the list
            table[hashValue] = entry->getNext();
        } else {
            prev->setNext(entry->getNext());
        }
        delete entry;
    }
}