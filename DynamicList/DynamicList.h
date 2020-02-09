#pragma once
#include <iostream>
template <class T>
struct node
{
	T data;
	node* pNext;
};

template <class T>
class DynamicList
{
public:
	DynamicList();
	DynamicList(const DynamicList<T>& list);
	DynamicList<T>& operator= (const DynamicList<T>& rhs);
	~DynamicList();
public:
	void headAdd(const T& data); // add new element at the start of list
	void rearAdd(const T& data); // add the element at the end of list
	int  size() const; // return the length of list
	bool isEmpty() const; // judge if list is empty
	void print() const; // scan the list
	T    getElement(int n) const; // get the Nth element
	void insertElement(int n, const T& data); // insert the data at list's Nth position
	void deleteElement(int n = 1); // delete the Nth element
	void modifyElement(int n, const T& data); // change the element at position N
	int  find(const T& data) const; // find the first apperance of element data, return -1 if not found
	void sort(); // sort out the list
	void destroy(); // destroy the list, makr it empty
private:
	node<T>* header;
	int length;
};

template <class T>
DynamicList<T>::DynamicList() :header(nullptr), length(0) {};
template <class T>
DynamicList<T>::DynamicList(const DynamicList<T>& list) :header(nullptr), length(0)
{
	for (int i = 1; i <= list.size(); i++)
		rearAdd(list.getElement(i));
}
template <class T>
DynamicList<T>& DynamicList<T>:: operator=(const DynamicList<T>& rhs)
{
	if (this == &rhs)
		return *this;
	destroy();
	for (int i = 0; i < rhs.size(); i++)
		rearAdd(rhs.getElement(i));
	return *this;
}
template <class T>
DynamicList<T>::~DynamicList()
{
	destroy();
}
template <class T>
void DynamicList<T>::headAdd(const T& data)
{
	node<T>* pnode = new node<T>;
	pnode->data = data;
	pnode->pNext = nullptr;

	if (header == nullptr)
		header = pnode;
	else
	{
		pnode->pNext = header;
		header = pnode;
	}
	length++;
}
template<class T>
void DynamicList<T>::rearAdd(const T& data)
{
	node<T>* pnode = new node<T>;
	pnode->data = data;
	pnode->pNext = nullptr;

	if (header == nullptr)
		header = pnode;
	else
	{
		node<T>* rear = header;
		while (rear->pNext != nullptr)
			rear = rear->pNext;
		rear->pNext = pnode;
	}
	length++;
}
template<class T>
int DynamicList<T>::size() const
{
	return length;
}
template<class T>
bool DynamicList<T>::isEmpty() const
{
	return header == nullptr;
}
template <class T>
void DynamicList<T>::print() const
{
	using namespace std;
	node<T>* ptemp = header;
	int count = 0;
	cout<< "%-------------Elements------------%" << endl;
	while (ptemp != nullptr)
	{
		cout << ptemp->data << "\t";
		ptemp = ptemp->pNext;
		count++;
		if (count % 5 == 0)
			cout << endl;
	}
	cout << endl << "%---------------------------------%" << endl;
}
template<class T>
T DynamicList<T>::getElement(int n) const
{
	if (n<1 || n>length)
		std::cout<< "illeagal element position!\n";
	else
	{
		node<T>* pnode = header;
		for (int i = 1; i < n; i++)
			pnode = pnode->pNext;
		return pnode->data;
	}
}
template <class T>
void DynamicList<T>::insertElement(int n, const T& data)
{
	if (n<1 || n>length)
		std::cout << "illeagal element position!\n";
	else if (n == 1)
	{
		node<T>* ptemp = new node<T>;
		ptemp->data = data;
		ptemp->pNext = header;
		header = ptemp;
	}
	else
	{
		int i = 1;
		node<T>* ptemp = header;
		while (++i < n)
			ptemp = ptemp->pNext;
		node<T>* pinsert = new node<T>;
		pinsert->data = data;
		pinsert->pNext = ptemp->pNext;
		ptemp->pNext = pinsert;
	}
	length++;
}
template <class T>
void DynamicList<T>::deleteElement(int n)
{
	if (n<1 || n>length)
		std::cout << "illeagal element position!\n";
	else
	{
		node<T>* deleteElement = new node<T>;
		if (n == 1)
		{
			deleteElement = header;
			header = header->pNext;
		}
		else
		{
			int i = 1;
			node<T>* ptemp = header;
			while (++i < n)
				ptemp = ptemp->pNext;
			deleteElement = ptemp->pNext;
			ptemp->pNext = deleteElement->pNext;
		}
		delete deleteElement;
		length--;
	}
}
template <class T>
void DynamicList<T>::modifyElement(int n, const T& data)
{
	if (n<1 || n>length)
		std::cout << "illeagal element position!\n";
	else
	{
		if (n == 1)
			header->data = data;
		else
		{
			node<T>* pnode = header;
			int i = 1;
			while (i++ < n)
				pnode = pnode->pNext;
			pnode->data = data;

		}
	}
}
template <class T>
int DynamicList<T>::find(const T& data) const
{
	int i = 1;
	int re = -1;
	node<T>* pnode = header;
	while (pnode != nullptr)
	{
		if (pnode->data == data)
		{
			re = i;
			break;
		}
		i++;
		pnode = pnode->pNext;
	}
	return re;
}
template <class T>
void DynamicList<T>::sort()
{
	if (length > 1)
	{
		for (int i = length; i > 0; i--)
			for (int j = 1; j < i; j++)
			{
				T left = getElement(j);
				T right = getElement(j + 1);
				if (left > right)
				{
					modifyElement(j, right);
					modifyElement(j + 1, left);
				}
			}
	}
}
template <class T>
void DynamicList<T>::destroy()
{
	while (header != nullptr)
	{
		node<T>* pnode = header;
		header = header->pNext;
		delete pnode;
	}
	length = 0;
}