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


	// 获取树的高度
	int getHeight() const;
	// 前序遍历
	void preOrder() const;
	// 中序遍历
	void inOrder() const;
	// 后序遍历
	void postOrder() const;

	// 查找最小值
	T findMin() const;
	// 查找最大值
	T findMax() const;

	// 查找节点
	AVLNode<T>* search(const T& x) const;
	// 插入节点
	void insert(const T& x);
	// 删除节点
	void remove(const T& x);
	// 销毁二叉树
	void destroy();

	// 打印树
	void print() const;

private:
	// 获取树的高度
	int getHeight(const AVLNode<T>* tree) const;
	// 前序遍历 for recursive call
	void preOrder(const AVLNode<T>* tree) const;
	// 中序遍历 for recursive call
	void inOrder(const AVLNode<T>* tree) const;
	// 后序遍历 for recursive call
	void postOrder(const AVLNode<T>* tree) const;

	// 查找节点
	AVLNode<T>* search(AVLNode<T>* tree, const T& x) const;
	// 查找最小值
	AVLNode<T>* findMin(AVLNode<T>* x) const;
	// 查找最大值
	AVLNode<T>* findMax(AVLNode<T>* x) const;

	// 左单旋转
	AVLNode<T>* LLRotate(AVLNode<T>* tree);
	// 右单旋转
	AVLNode<T>* RRRotate(AVLNode<T>* tree);
	// 先左后右双次旋转
	AVLNode<T>* LRRotate(AVLNode<T>* tree);
	// 先右后左双次旋转
	AVLNode<T>* RLRotate(AVLNode<T>* tree);
	
	// 插入节点
	AVLNode<T>* insert(AVLNode<T>* &tree, const T& x);
	// 删除节点
	AVLNode<T>* remove(AVLNode<T>*& tree, const AVLNode<T>* p);
	// 销毁树
	void destroy(AVLNode<T>*& tree);
	// 打印树
	void print(AVLNode<T>* tree, const T& x, int direction) const;
};

template class AVLTree <int>;
template class AVLTree <char>;
template class AVLTree <double>;