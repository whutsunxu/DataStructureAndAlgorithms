#include "SPHash.h"
#include <algorithm>
//given a number n, determine if it is prime
static bool isPrime(int n)
{
	//loop from 2 to n/2 to check for factors
	for (int i = 2; i <= n / 2; i++)
	{
		if (n % i == 0)     //found a factor that isn't 1 or n, therefore not prime
			return false;
	}

	return true;
}
//given a number n, find the next closest prime number above n
static int getNextPrime(int n)
{
	int nextPrime = n;
	bool found = false;

	//loop continuously until isPrime returns true for a number above n
	while (!found)
	{
		nextPrime++;
		if (isPrime(nextPrime))
			found = true;
	}

	return nextPrime;
}

template <class HashObj>
void HashTable<HashObj>::makeEmpty()
{
	for (auto& thisList : theLists)
		thisList.clear();
}
template <class HashObj>
HashTable<HashObj>::HashTable(int length) :theLists(getNextPrime(length)), currentLength(0)
{
	makeEmpty();
}
template <class HashObj>
size_t HashTable<HashObj>::myHash(const HashObj& x) const
{
	static hash<HashObj> hf;
	return hf(x) % theLists.size();
}
template <class HashObj>
bool HashTable<HashObj>::contain(const HashObj& x) const
{
	auto& y = theLists[myHash(x)];
	return std::find(y.begin(), y.end(), x) != y.end();
}
template <class HashObj>
bool HashTable<HashObj>::insert(const HashObj& x)
{
	auto& whichList = theLists[myHash(x)];
	if (std::find(whichList.begin(), whichList.end(), x) != whichList.end()) // 已经存在该元素
		return false;
	whichList.push_back(x);

	// 再散列
	if (++currentLength > theLists.size())
		rehash();
	return true;
}
template <class HashObj>
bool HashTable<HashObj>::remove(const HashObj& x) 
{
	auto& whichList = theLists[myHash(x)];
	// std::list<HashObj>::iterator iter= std::find(whichList.begin(), whichList.end(), x);
	auto iter = std::find(whichList.begin(), whichList.end(), x);
	if (iter == whichList.end())
		return false;

	whichList.erase(iter);
	currentLength--;
	return true;
}
template <class HashObj>
void HashTable<HashObj>::rehash()
{
	std::vector<std::list<HashObj>> oldLists;
	
	theLists.resize(getNextPrime(2 * theLists.size()));
	for (auto& thisList : theLists)
		thisList.clear();

	for (auto& thisList : oldLists)
		for (auto& x : thisList)
			insert(std::move(x));
}
