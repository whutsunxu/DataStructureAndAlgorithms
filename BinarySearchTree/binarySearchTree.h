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

	// ǰ�����
	void preOrder() const;
	// �������
	void inOrder() const;
	// �������
	void postOrder() const;

	// �ݹ����
	BSTNode<T>* search(const T& key) const;
	// �ǵݹ����
	BSTNode<T>* iterativeSearch(const T& key) const;

	// ������Сֵ�����ؼ�ֵ
	T findMin() const;
	// �������ֵ�����ؼ�ֵ
	T findMax() const;

	// ���ҽڵ�x�ĺ�̽ڵ�
	BSTNode<T>* successor(BSTNode<T>* x);
	// ���ҽڵ�x��ǰ���ڵ�
	BSTNode<T>* predecessor(BSTNode<T>* x);

	// ����ڵ�
	void insert(const T& x);
	// ������������ڵ�
	void iterativeInsert(const T& x);
	// ɾ���ڵ�
	void remove(T x);
	// ���ٶ�����
	void destroy();

	// ��ӡ��
	void print()const;

private:
	// ǰ����� for recursive call
	void preOrder(const BSTNode<T>* tree) const;
	// ������� for recursive call
	void inOrder(const BSTNode<T>* tree) const;
	// ������� for recursive call
	void postOrder(const BSTNode<T>* tree) const;
	// �ݹ����
	BSTNode<T>* search(BSTNode<T>* tree, const T& key) const;
	// �ǵݹ����
	BSTNode<T>* iterativeSearch(BSTNode<T>* x, const T& key) const;
	// ������Сֵ
	BSTNode<T>* findMin(BSTNode<T>* x) const;
	// �������ֵ
	BSTNode<T>* findMax(BSTNode<T>* x) const;
	// ����ڵ�
	void insert(BSTNode<T>*& tree, BSTNode<T>* y);
	// ����������ڵ�
	void iterativeInsert(BSTNode<T>*& tree, const BSTNode<T>* y);
	// ɾ���ڵ�
	BSTNode<T>* remove(BSTNode<T>*& tree, BSTNode<T>* y);
	// ������
	void destroy(BSTNode<T>*& tree);
	// ��ӡ������
	void print(const BSTNode<T>* tree, const T& key, int direction)const;
};

template class BSTree <int>;
template class BSTree <char>;
template class BSTree <double>;
