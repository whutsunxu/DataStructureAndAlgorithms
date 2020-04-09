#pragma once
#include <iostream>
#include <vector>
#include <list>

template <class HashObj>
class hash
{
public:
	size_t operator()(const HashObj& key)
	{
		size_t hashVal = 0;
		for (char ch : key)
			hashVal = 37 * hashVal + ch;
		return hashVal;
	}
};

template class hash <std::string>;

template <class HashObj>
class HashTable {
public:
	explicit HashTable(int length = 101);
	bool contain(const HashObj& x) const;
	void makeEmpty();
	bool insert(const HashObj& x);
	bool remove(const HashObj& x);
private:
	std::vector<std::list<HashObj>> theLists;
	int currentLength;

	void rehash();
	size_t myHash(const HashObj& x) const;
};

template class HashTable <std::string>;