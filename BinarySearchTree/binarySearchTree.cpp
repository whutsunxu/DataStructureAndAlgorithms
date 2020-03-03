#include "binarySearchTree.h"
#include <iostream>
#include <exception>

template <class T>
BSTree<T>::BSTree() :mRoot(nullptr)
{

}
template <class T>
BSTree<T>::~BSTree()
{
	destroy();
}
template <class T>
void BSTree<T>::preOrder() const
{
	preOrder(mRoot);
}
template <class T>
void BSTree<T>::preOrder(const BSTNode<T>* tree) const
{
	using namespace std;
	if (tree != nullptr)
	{
		cout << tree->key << " ";
		preOrder(tree->left);
		preOrder(tree->right);
	}
}
template <class T>
void BSTree<T>::inOrder() const
{
	inOrder(mRoot);
}
template <class T>
void BSTree<T>::inOrder(const BSTNode<T>* tree) const
{
	using namespace std;
	if (tree != nullptr)
	{
		inOrder(tree->left);
		cout << tree->key << " ";
		inOrder(tree->right);
	}
}
template <class T>
void BSTree<T>::postOrder() const
{
	postOrder(mRoot);
}
template <class T>
void BSTree<T>::postOrder(const BSTNode<T>* tree) const
{
	using namespace std;
	if (tree != nullptr)
	{
		postOrder(tree->left);
		postOrder(tree->right);
		cout << tree->key << " ";
	}
}
template <class T>
BSTNode<T>* BSTree<T>::search(const T& key) const
{
	BSTNode<T>* p = nullptr;
	p = search(mRoot, key);
	return p;
}
template <class T>
BSTNode<T>* BSTree<T>::search(BSTNode<T>* tree, const T& key) const
{
	if (tree == nullptr || tree->key == key)
		return tree;
	else if (tree->key < key)
		search(tree->right, key);
	else
		search(tree->left, key);
}
template <class T>
BSTNode<T>* BSTree<T>::iterativeSearch(const T& key) const
{
	BSTNode<T>* p = nullptr;
	p = iterativeSearch(mRoot, key);
	return p;
}
template <class T>
BSTNode<T>* BSTree<T>::iterativeSearch(BSTNode<T>* x, const T& key) const
{
	while (x != nullptr && x->key != key)
	{
		if (x->key < key)
			x = x->right;
		else
			x = x->left;
	}
	return x;
}
template <class T>
T BSTree<T>::findMin() const  
{
	BSTNode<T>* p = findMin(mRoot);
	if (p != nullptr)
		return p->key;
	else
		return T(0);
}
template <class T>
BSTNode<T>* BSTree<T>::findMin(BSTNode<T>* x) const 
{
	if (x == nullptr)
		return nullptr;
	while (x->left != nullptr)
		x = x->left;
	return x;
}
template <class T>
T BSTree<T>::findMax() const
{
	BSTNode<T>* p = findMax(mRoot);
	if (p != nullptr)
		return p->key;
	else
		return T(0);
}
template <class T>
BSTNode<T>* BSTree<T>::findMax(BSTNode<T>* x) const
{
	if (x == nullptr)
		return nullptr;
	while (x->right != nullptr)
		x = x->right;
	return x;
}
template <class T>
BSTNode<T>* BSTree<T>::successor(BSTNode<T>* x)
{
	// x 是否具有 右孩点
	if (x->right != nullptr)
		return x->right;
	// 若x 没有右孩点 查找X的父节点：含有左孩点的最低父节点
	BSTNode<T>* y = x->parent;
	while (y != nullptr && x != y->left)
	{
		x = y;
		y = x->parent;
	}
	return y;
}
template <class T>
BSTNode<T>* BSTree<T>::predecessor(BSTNode<T>* x)
{
	// x 是否具有左孩点
	if (x->left != nullptr)
		return x->left;
	// 若x没有左孩点，查找X的父节点：含有右孩点的最低父节点
	BSTNode<T>* y = x->parent;
	while (y != nullptr && x != y->right)
	{
		x = y;
		y = x->parent;
	}
	return y;
}
template <class T>
void BSTree<T>::insert(const T& x)
{
	using namespace std;
	BSTNode<T>* y = nullptr;
	try
	{
		y = new BSTNode<T>(x, nullptr, nullptr, nullptr);
	}
	catch (exception & e)
	{
		cerr << "Standard exception: " << e.what() << endl;
		exit(-1);
	}
	insert(mRoot, y);
}
template <class T>
void BSTree<T>::insert(BSTNode<T>*& tree, BSTNode<T>* y)
{
	BSTNode<T>* p = nullptr;
	BSTNode<T>* q = tree;

	while (q != nullptr)
	{
		p = q;
		if (y->key > q->key)
			q = q->right;
		else
			q = q->left;
	}
	// after search, we can make sure that y is the parent of p
	y->parent = p;
	if (p == nullptr)   // the tree is nullptr
		tree = y;
	else if (p->key > y->key)
		p->left = y;
	else
		p->right = y;
}
template <class T>
void BSTree<T>::iterativeInsert(const T& x)
{
	//using namespace std;
	//BSTNode<T>* y = nullptr;
	//try 
	//{
	//	y = new BSTNode<T>(x, nullptr, nullptr, nullptr, nullptr);
	//}
	//catch (exception & e)
	//{
	//	cerr << "Standard Exception: " << e.what() << endl;
	//	exit(-1);
	//}
	//iterativeInsert(mRoot, y);
}
template <class T>
void BSTree<T>::iterativeInsert(BSTNode<T>*& tree, const BSTNode<T>* y)
{
	//BSTNode<T>* p = tree;
	//if (p == nullptr)
	//{
	//	p = y;
	//}
	//else if (p->key > y->key)
	//{

	//}
}
template <class T>
void BSTree<T>::remove(T x)
{
	BSTNode<T> *y, *z;
	y = search(mRoot, x);
	if (y != nullptr)
	{
		z = remove(mRoot, y);
		if (z != nullptr)
			delete z;
	}
}
template <class T>
BSTNode<T>* BSTree<T>::remove(BSTNode<T>*& tree, BSTNode<T>* z)
{
	BSTNode<T>* x = NULL;
	BSTNode<T>* y = NULL;

	if ((z->left == NULL) || (z->right == NULL))
		y = z;
	else
		y = successor(z);

	if (y->left != NULL)
		x = y->left;
	else
		x = y->right;

	if (x != NULL)
		x->parent = y->parent;

	if (y->parent == NULL)
		tree = x;
	else if (y == y->parent->left)
		y->parent->left = x;
	else
		y->parent->right = x;

	if (y != z)
		z->key = y->key;

	return y;
}
template <class T>
void BSTree<T>::destroy()
{
	destroy(mRoot);
}
template <class T>
void BSTree<T>::destroy(BSTNode<T>*& tree)
{
	if (tree == nullptr)
		return;
	if (tree->left != nullptr)
		destroy(tree->left);
	if (tree->right != nullptr)
		destroy(tree->right);

	delete tree;
	tree = nullptr;
}
template <class T>
void BSTree<T>::print()const
{
	if (mRoot != nullptr)
		print(mRoot, mRoot->key, 0);
}
template <class T>
void BSTree<T>::print(const BSTNode<T>* tree, const T& key, int direction) const
{
	using namespace std;
	if (tree != nullptr)
	{
		if (direction == 0)  // root
			cout << setw(2) << tree -> key << " is root" << endl;
		else
			cout << setw(2) << tree -> key << " is "
			<< (direction == -1 ? "left child" : "right child") << endl;

		print(tree->left, tree->key, -1);
		print(tree->right, tree->key, 1);
	}
}
