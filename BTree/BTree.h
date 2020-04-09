#pragma once
/* reference: https://www.cnblogs.com/kiven-code/archive/2013/03/04/2942679.html */
typedef struct _tagBTreeNode
{
	int key_count; // �Ѵ洢��keyԪ�صĸ���
	int* key;      // �ߴ�Ϊ2t����k[1]��ʼ�洢
	_tagBTreeNode** child; // �ߴ�Ϊ2t+1����child[1]��ʼ�洢
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

