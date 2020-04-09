#include "avltree.h"
#include <iostream>
#include <iomanip>
#include <algorithm>

template <class T>
AVLTree<T>::AVLTree():mRoot(nullptr)
{

}
template <class T>
AVLTree<T>::~AVLTree()
{
	destroy();
}
template <class T>
int AVLTree<T>::getHeight() const
{
	return getHeight(mRoot);
}
template <class T>
int AVLTree<T>::getHeight(const AVLNode<T>* tree) const
{
	if (tree != nullptr)
		return tree->height;
	else
		return 0;
}
template <class T>
void AVLTree<T>::preOrder() const
{
	preOrder(mRoot);
}
template <class T>
void AVLTree<T>::preOrder(const AVLNode<T>* tree) const
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
void AVLTree<T>::inOrder() const
{
	inOrder(mRoot);
}
template <class T>
void AVLTree<T>::inOrder(const AVLNode<T>* tree) const
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
void AVLTree<T>::postOrder() const
{
	postOrder(mRoot);
}
template <class T>
void AVLTree<T>::postOrder(const AVLNode<T>* tree) const
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
T AVLTree<T>::findMin() const
{
	AVLNode<T>* p = findMin(mRoot);
	if (p != nullptr)
		return p->key;
	else
		return T(0);
}
template <class T>
T AVLTree<T>::findMax() const
{
	AVLNode<T>* p = findMax(mRoot);
	if (p != nullptr)
		return p->key;
	else
		return T(0);
}
template <class T>
AVLNode<T>* AVLTree<T>::search(const T& key) const
{
	AVLNode<T>* p = nullptr;
	p = search(mRoot, key);
	return p;
}
template <class T>
AVLNode<T>* AVLTree<T>::search(AVLNode<T>* tree, const T& key) const
{
	if (tree == nullptr || tree->key == key)
		return tree;
	else if (tree->key < key)
		search(tree->right, key);
	else
		search(tree->left, key);
}
template <class T>
AVLNode<T>* AVLTree<T>::findMin(AVLNode<T>* x) const
{
	if (x == nullptr)
		return nullptr;
	while (x->left != nullptr)
		x = x->left;
	return x;
}
template <class T>
AVLNode<T>* AVLTree<T>::findMax(AVLNode<T>* x) const
{
	if (x == nullptr)
		return nullptr;
	while (x->right != nullptr)
		x = x->right;
	return x;
}
template <class T>
void AVLTree<T>::insert(const T& x)
{
	insert(mRoot, x);
}
template <class T>
AVLNode<T>* AVLTree<T>::insert(AVLNode<T>*& tree, const T& key)
{
	using namespace std;
	if (tree == nullptr)
	{
		tree = new AVLNode<T>(key, nullptr, nullptr,0);
		if (tree == nullptr)
		{
			cerr << "Failure in memory allocation" << endl;
			exit(-1);
		}
	}
	else if (key < tree->key)
	{
		tree->left = insert(tree->left, key);
		if (getHeight(tree->left) - getHeight(tree->right) == 2)
		{
			if (key < tree->left->key)
				tree = LLRotate(tree);
			else
				tree = LRRotate(tree);
		}
	}
	else if (key > tree->key)
	{
		tree->right = insert(tree->right, key);
		if (getHeight(tree->right) - getHeight(tree->left) == 2)
		{
			if (key > tree->right->key)
				tree = RRRotate(tree);
			else
				tree = RLRotate(tree);
		}
	}
	else
	{
		cerr << "存在键值相同节点，添加失败！" << endl;
		exit(-1);
	}
	tree->height = max(getHeight(tree->left), getHeight(tree->right)) + 1;
	return tree;
}
template <class T>
void AVLTree<T>::remove(const T& x)
{
	AVLNode<T>* p;
	p = search(mRoot, x);
	if (p != nullptr)
		mRoot = remove(mRoot, p);
}
template <class T>
AVLNode<T>* AVLTree<T>::remove(AVLNode<T>*& tree, const AVLNode<T>* z)
{
	// 根为空 或者 没有要删除的节点，直接返回NULL。
	if (tree == nullptr || z == nullptr)
		return nullptr;

	if (z->key < tree->key)        // 待删除的节点在"tree的左子树"中
	{
		tree->left = remove(tree->left, z);
		// 删除节点后，若AVL树失去平衡，则进行相应的调节。
		if (getHeight(tree->right) - getHeight(tree->left) == 2)
		{
			AVLNode<T>* r = tree->right;
			if (getHeight(r->left) > getHeight(r->right))
				tree = LRRotate(tree);
			else
				tree = RRRotate(tree);
		}
	}
	else if (z->key > tree->key)// 待删除的节点在"tree的右子树"中
	{
		tree->right = remove(tree->right, z);
		// 删除节点后，若AVL树失去平衡，则进行相应的调节。
		if (getHeight(tree->left) - getHeight(tree->right) == 2)
		{
			AVLNode<T>* l = tree->left;
			if (getHeight(l->right) > getHeight(l->left))
				tree = RLRotate(tree);
			else
				tree = LLRotate(tree);
		}
	}
	else    // tree是对应要删除的节点。
	{
		// tree的左右孩子都非空
		if ((tree->left != nullptr) && (tree->right != nullptr))
		{
			if (getHeight(tree->left) > getHeight(tree->right))
			{
				// 如果tree的左子树比右子树高；
				// 则(01)找出tree的左子树中的最大节点
				//   (02)将该最大节点的值赋值给tree。
				//   (03)删除该最大节点。
				// 这类似于用"tree的左子树中最大节点"做"tree"的替身；
				// 采用这种方式的好处是：删除"tree的左子树中最大节点"之后，AVL树仍然是平衡的。
				AVLNode<T>* max = findMax(tree->left);
				tree->key = max->key;
				tree->left = remove(tree->left, max);
			}
			else
			{
				// 如果tree的左子树不比右子树高(即它们相等，或右子树比左子树高1)
				// 则(01)找出tree的右子树中的最小节点
				//   (02)将该最小节点的值赋值给tree。
				//   (03)删除该最小节点。
				// 这类似于用"tree的右子树中最小节点"做"tree"的替身；
				// 采用这种方式的好处是：删除"tree的右子树中最小节点"之后，AVL树仍然是平衡的。
				AVLNode<T>* min = findMin(tree->right);
				tree->key = min->key;
				tree->right = remove(tree->right, min);
			}
		}
		else
		{
			AVLNode<T>* tmp = tree;
			tree = (tree->left != nullptr) ? tree->left : tree->right;
			delete tmp;
		}
	}
	return tree;
}
template <class T>
AVLNode<T>* AVLTree<T>::LLRotate(AVLNode<T>* k2)
{
	using namespace std;
	AVLNode<T>* k1;

	k1 = k2->left;
	k2->left = k1->right;
	k1->right = k2;

	k2->height = max(getHeight(k2->left), getHeight(k2->right)) + 1;
	k1->height = max(getHeight(k1->left), k2->height) + 1;

	return k1;
}

template <class T>
AVLNode<T>* AVLTree<T>::RRRotate(AVLNode<T>* k1)
{
	using namespace std;
	AVLNode<T>* k2;

	k2 = k1->right;
	k1->right = k2->left;
	k2->left = k1;

	k1->height = max(getHeight(k1->left), getHeight(k1->right)) + 1;
	k2->height = max(getHeight(k2->right), k1->height) + 1;

	return k2;
}

template <class T>
AVLNode<T>* AVLTree<T>::LRRotate(AVLNode<T>* k3)
{
	k3->left = RRRotate(k3->left);

	return LLRotate(k3);
}

template <class T>
AVLNode<T>* AVLTree<T>::RLRotate(AVLNode<T>* k1)
{
	k1->right = LLRotate(k1->right);

	return RRRotate(k1);
}

template <class T>
void AVLTree<T>::destroy()
{
	destroy(mRoot);
}
template <class T>
void AVLTree<T>::destroy(AVLNode<T>*& tree)
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
void AVLTree<T>::print()const
{
	if (mRoot != nullptr)
		print(mRoot, mRoot->key, 0);
}
template <class T>
void AVLTree<T>::print(AVLNode<T>* tree, const T& x, int direction) const
{
	using namespace std;
	if (tree != nullptr)
	{
		if (direction == 0)  // root
			cout << setw(2) << tree->key << " is root" << endl;
		else
			cout << setw(2) << tree->key << " is "
			<< (direction == -1 ? "left child" : "right child") << endl;

		print(tree->left, tree->key, -1);
		print(tree->right, tree->key, 1);
	}
}

