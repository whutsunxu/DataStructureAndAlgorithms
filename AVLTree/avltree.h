#pragma once

template <class T>
class AVLNode
{
public:
	T key;
	AVLNode<T>* left;
	AVLNode<T>* right;
	int height;

	AVLNode(int x, AVLNode<T>* l, AVLNode<T>* r, int h) :
		key(x), left(l), right(r), height(h) {};
};
template class AVLNode <int>;
template class AVLNode <char>;
template class AVLNode <double>;

template <class T>
class AVLTree
{
private:
	AVLNode<T>* mRoot;

public:
	AVLTree();
	~AVLTree();


	// ��ȡ���ĸ߶�
	int getHeight() const;
	// ǰ�����
	void preOrder() const;
	// �������
	void inOrder() const;
	// �������
	void postOrder() const;

	// ������Сֵ
	T findMin() const;
	// �������ֵ
	T findMax() const;

	// ���ҽڵ�
	AVLNode<T>* search(const T& x) const;
	// ����ڵ�
	void insert(const T& x);
	// ɾ���ڵ�
	void remove(const T& x);
	// ���ٶ�����
	void destroy();

	// ��ӡ��
	void print() const;

private:
	// ��ȡ���ĸ߶�
	int getHeight(const AVLNode<T>* tree) const;
	// ǰ����� for recursive call
	void preOrder(const AVLNode<T>* tree) const;
	// ������� for recursive call
	void inOrder(const AVLNode<T>* tree) const;
	// ������� for recursive call
	void postOrder(const AVLNode<T>* tree) const;

	// ���ҽڵ�
	AVLNode<T>* search(AVLNode<T>* tree, const T& x) const;
	// ������Сֵ
	AVLNode<T>* findMin(AVLNode<T>* x) const;
	// �������ֵ
	AVLNode<T>* findMax(AVLNode<T>* x) const;

	// ����ת
	AVLNode<T>* LLRotate(AVLNode<T>* tree);
	// �ҵ���ת
	AVLNode<T>* RRRotate(AVLNode<T>* tree);
	// �������˫����ת
	AVLNode<T>* LRRotate(AVLNode<T>* tree);
	// ���Һ���˫����ת
	AVLNode<T>* RLRotate(AVLNode<T>* tree);
	
	// ����ڵ�
	AVLNode<T>* insert(AVLNode<T>* &tree, const T& x);
	// ɾ���ڵ�
	AVLNode<T>* remove(AVLNode<T>*& tree, const AVLNode<T>* p);
	// ������
	void destroy(AVLNode<T>*& tree);
	// ��ӡ��
	void print(AVLNode<T>* tree, const T& x, int direction) const;
};

template class AVLTree <int>;
template class AVLTree <char>;
template class AVLTree <double>;