#pragma once
#include <iomanip>
#include <iostream>

template <class T>
class BSTNode
{
public:
	T key;
	BSTNode* left;
	BSTNode* right;
	BSTNode* parent;

	BSTNode(const T& x,  BSTNode<T>* l,  BSTNode<T>* r, BSTNode<T>* p) :
		key(x), left(l), right(r), parent(p) {};
};
template class BSTNode <int>;
template class BSTNode <double>;
template class BSTNode <char>;

template <class T>
class BSTree
{
private:
	BSTNode<T>* mRoot;
public:
	BSTree();
	~BSTree();

	// 前序遍历
	void preOrder() const;
	// 中序遍历
	void inOrder() const;
	// 后序遍历
	void postOrder() const;

	// 递归查找
	BSTNode<T>* search(const T& key) const;
	// 非递归查找
	BSTNode<T>* iterativeSearch(const T& key) const;

	// 查找最小值，返回键值
	T findMin() const;
	// 查找最大值，返回键值
	T findMax() const;

	// 查找节点x的后继节点
	BSTNode<T>* successor(BSTNode<T>* x);
	// 查找节点x的前驱节点
	BSTNode<T>* predecessor(BSTNode<T>* x);

	// 插入节点
	void insert(const T& x);
	// 迭代方法插入节点
	void iterativeInsert(const T& x);
	// 删除节点
	void remove(T x);
	// 销毁二叉树
	void destroy();

	// 打印树
	void print()const;

private:
	// 前序遍历 for recursive call
	void preOrder(const BSTNode<T>* tree) const;
	// 中序遍历 for recursive call
	void inOrder(const BSTNode<T>* tree) const;
	// 后序遍历 for recursive call
	void postOrder(const BSTNode<T>* tree) const;
	// 递归查找
	BSTNode<T>* search(BSTNode<T>* tree, const T& key) const;
	// 非递归查找
	BSTNode<T>* iterativeSearch(BSTNode<T>* x, const T& key) const;
	// 查找最小值
	BSTNode<T>* findMin(BSTNode<T>* x) const;
	// 查找最大值
	BSTNode<T>* findMax(BSTNode<T>* x) const;
	// 插入节点
	void insert(BSTNode<T>*& tree, BSTNode<T>* y);
	// 迭代法插入节点
	void iterativeInsert(BSTNode<T>*& tree, const BSTNode<T>* y);
	// 删除节点
	BSTNode<T>* remove(BSTNode<T>*& tree, BSTNode<T>* y);
	// 销毁树
	void destroy(BSTNode<T>*& tree);
	// 打印二叉树
	void print(const BSTNode<T>* tree, const T& key, int direction)const;
};

template class BSTree <int>;
template class BSTree <char>;
template class BSTree <double>;
