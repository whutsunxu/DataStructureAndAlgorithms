#pragma once
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