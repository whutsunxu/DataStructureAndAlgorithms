#pragma once
/*
reference: data structures and algorithm analysis in C++ fourth edition: p158, chapter 5
*/
template <class T>
struct node
{
	T data;
	node* pNext;
};
template <class T>
class LinkedStack
{
private:
	node<T>* headNode;
	unsigned int length;
public:
	LinkedStack();
	~LinkedStack();
	bool IsEmpty() const;
	unsigned int GetLength() const;
	void MakeEmpty();
	void Push(const T& x);
	T Top() const;
	void Pop();
};
template class LinkedStack <int>;
template class LinkedStack <double>;