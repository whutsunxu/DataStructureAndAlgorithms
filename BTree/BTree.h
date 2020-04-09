#pragma once
/* reference: https://www.cnblogs.com/kiven-code/archive/2013/03/04/2942679.html */
typedef struct _tagBTreeNode
{
	int key_count; // 已存储的key元素的个数
	int* key;      // 尺寸为2t，从k[1]开始存储
	_tagBTreeNode** child; // 尺寸为2t+1，从child[1]开始存储
	bool leaf;
}BTreeNode, * PBTreeNode;

class BTree
{
public:
	BTree();
	~BTree();

	bool Insert(int key);
	bool Delete(int key);
	void Display() { Print(root); };

private:
	BTreeNode* Search(PBTreeNode pNode, int key);
	PBTreeNode AllocateNode();
	void SplitChild(PBTreeNode pParent, int index, PBTreeNode pChild);
	PBTreeNode UnionChild(PBTreeNode pParent, PBTreeNode pCLeft, PBTreeNode pCRight, int index);
	void InsertNonfull(PBTreeNode pNode, int key);
	int Max(PBTreeNode pNode);
	int Min(PBTreeNode pNode);
	bool DeleteNonHalf(PBTreeNode pNode, int key);
	void DellocateNode(PBTreeNode pNode);
	void DeleteTree(PBTreeNode pNode);
	void Print(PBTreeNode pNode);
private:
	PBTreeNode root;
	int t;//btree's degree
};

