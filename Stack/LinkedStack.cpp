#include "LinkedStack.h"
#include <iostream>
#include <exception>

template <class T>
LinkedStack<T>::LinkedStack() :length(0)
{
	using namespace std;
	try
	{
		headNode = new node<T>;
	}
	catch (exception & e)
	{
		cerr << "Standard exception" << e.what() << endl;
		exit(-1);
	}
	headNode->pNext = nullptr; //initilize
	length = 0;
}
template <class T>
LinkedStack<T>::~LinkedStack()
{

}
template <class T>
bool LinkedStack<T>::IsEmpty() const
{
	return headNode->pNext == nullptr;
}
template <class T>
void LinkedStack<T>::MakeEmpty()
{
	if (this->IsEmpty()) return;
	node<T>* temp;
	while (headNode->pNext != nullptr)
	{
		temp = headNode->pNext;
		headNode->pNext = headNode->pNext->pNext;
		delete temp;
	}
}
template <class T>
unsigned int LinkedStack<T>::GetLength() const
{
	return length;
}
template <class T>
void LinkedStack<T>::Push(const T& x)
{
	node<T>* temp = new node<T>;
	temp->data = x;
	temp->pNext = headNode->pNext;
	headNode->pNext = temp;
	length++;
}
template <class T>
T LinkedStack<T>::Top() const
{
	if (this->IsEmpty())
	{
		std::cerr << "Empty stack!" << std::endl;
		exit(-1);
	}
	else
		return headNode->pNext->data;
}
template <class T>
void LinkedStack<T>::Pop()
{
	node<T>* temp;
	temp = headNode->pNext;
	headNode->pNext = headNode->pNext->pNext;
	delete temp;
	length--;
}