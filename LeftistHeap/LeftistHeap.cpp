#include "LeftistHeap.h"
#include <iostream>

template <class Comparable>
LeftistHeap<Comparable>::LeftistHeap():root(nullptr)
{
}
template <class Comparable>
LeftistHeap<Comparable>::LeftistHeap(const LeftistHeap& rhs)
{
	this->root = clone(rhs.root);
}
template <class Comparable>
LeftistHeap<Comparable>::LeftistHeap(LeftistHeap&& rhs)
{
	this->root = clone(rhs.root);
	rhs.root = nullptr;
}
template <class Comparable>
LeftistHeap<Comparable>::~LeftistHeap()
{
	makeEmpty();
}
template<class Comparable>
LeftistHeap<Comparable> LeftistHeap<Comparable>::operator=(const LeftistHeap<Comparable>& rhs)
{
	if (!rhs.isEmpty())
	{
		LeftistHeap<Comparable>* tmp = new LeftistHeap<Comparable>();
		tmp->root = clone(rhs.root);
		return *tmp;
	}	
}
template<class Comparable>
LeftistHeap<Comparable> LeftistHeap<Comparable>::operator=(LeftistHeap<Comparable>&& rhs)
{
	if (!rhs.isEmpty())
	{
		LeftistHeap<Comparable>* tmp = new LeftistHeap<Comparable>();
		tmp->root = clone(rhs.root);
		rhs.root = nullptr;
		return *tmp;
	}
}
template<class Comparable>
bool LeftistHeap<Comparable>::isEmpty() const
{
	return this->root == nullptr;
}
template <class Comparable>
const Comparable& LeftistHeap<Comparable>::findMin() const
{
	if (isEmpty())
		throw UNDERFLOW;
	else
		return this->root->element;
}
template <class Comparable>
void LeftistHeap<Comparable>::insert(const Comparable& x)
{
	root = merge(new LeftistNode(x), root);
}
/*
template <class Comparable>
void LeftistHeap<Comparable>::insert(Comparable&& x)
{
	root = merge(new LeftistNode(x), root);
	//free(x);
}
*/
template <class Comparable>
void LeftistHeap<Comparable>::deleteMin()
{
	if (isEmpty())
		throw UNDERFLOW;
	else
	{
		LeftistHeap<Comparable>::LeftistNode* oldRoot = root;
		root = merge(root->left, root->right);
		delete oldRoot;
	}
}
template <class Comparable>
void LeftistHeap<Comparable>::deleteMin(Comparable& item)
{
	item = findMin();
	deleteMin();
}
template <class Comparable>
void LeftistHeap<Comparable>::makeEmpty()
{
	reclaimMemory(root);
	root = nullptr;
}
template <class Comparable>
void LeftistHeap<Comparable>::merge(LeftistHeap<Comparable>&& rhs) //problem
{
	if (this->root == rhs.root)
		return;
	root = merge(root, rhs.root);
	rhs.root = nullptr;
}
template <class Comparable>
typename LeftistHeap<Comparable>::LeftistNode* LeftistHeap<Comparable>::merge(LeftistNode* h1, LeftistNode* h2)
{
	if (h1 == nullptr)
		return h2;
	if (h2 == nullptr)
		return h1;
	if (h1->element < h2->element)
		return merge1(h1, h2);
	else
		return merge1(h2, h1);
}
template <class Comparable>
typename LeftistHeap<Comparable>::LeftistNode* LeftistHeap<Comparable>::merge1(LeftistNode* h1, LeftistNode* h2)
{
	if (h1->left == nullptr)
		h1->left = h2;
	else
	{
		h1->right = merge(h1->right, h2);
		if (h1->left-> npl < h1->right->npl)
			swapChildren(h1);
		h1->npl = h1->right->npl + 1;
	}
	return h1;
}
template <class Comparable>
void LeftistHeap<Comparable>::swapChildren(LeftistNode*t)
{
	LeftistNode* tmp = t->left;
	t->left = t->right;
	t->right = tmp;
}
template <class Comparable>
void LeftistHeap<Comparable>::reclaimMemory(LeftistNode* t)
{
	if (t != nullptr)
	{
		reclaimMemory(t->left);
		reclaimMemory(t->right);
		delete t;
	}
}
template <class Comparable>
typename LeftistHeap<Comparable>::LeftistNode* LeftistHeap<Comparable>::clone(LeftistNode* t) const
{
	if (t == nullptr)
		return nullptr;
	else
		return new LeftistNode(t->element, clone(t->left), clone(t->right), t->npl);
}
