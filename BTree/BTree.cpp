#include <iostream>
#include "BTree.h"
using namespace std;

BTree::BTree() : root(NULL), t(4)
{
};

BTree::~BTree()
{
	DeleteTree(root);
	delete root;
};

PBTreeNode BTree::AllocateNode()
{
	PBTreeNode pTemp = new BTreeNode;
	pTemp->key = new int[2 * t];
	pTemp->child = new PBTreeNode[2 * t + 1];

	for (int i = 0; i < 2 * t; i++)
	{
		pTemp->key[i] = 0;
		pTemp->child[i] = NULL;
	}
	pTemp->child[2 * t] = NULL;

	return pTemp;
}

PBTreeNode BTree::Search(PBTreeNode pNode, int key)
{
	int i = 1;
	while (i <= pNode->key_count && key > pNode->key[i])
		i++;

	if (i < pNode->key_count && key == pNode->key[i])
		return pNode->child[i];

	if (pNode->leaf)
		return NULL;
	else
		return Search(pNode->child[i], key);
}

bool BTree::Insert(int key)
{
	PBTreeNode r = root;
	if (r == NULL)
	{
		r = AllocateNode();
		r->leaf = true;
		r->key_count = 0;

		root = r;
	}

	if (r != NULL && r->key_count == (2 * t - 1)) //�ڵ�����
	{
		PBTreeNode s = AllocateNode();
		root = s;
		s->leaf = false;
		s->key_count = 0;
		s->child[1] = r;
		SplitChild(s, 1, r);
		InsertNonfull(s, key);
	}
	else
	{
		InsertNonfull(r, key);
	}

	return true;
}

void BTree::SplitChild(PBTreeNode pParent, int index, PBTreeNode pChild)
{
	PBTreeNode pChildEx = AllocateNode();
	pChildEx->leaf = pChild->leaf;
	pChildEx->key_count = t - 1;
	// ��������pChild�еĸ�λ���ϴ�ģ�Ԫ�ط���pChildEx��
	for (int j = 1; j < t; j++)
		pChildEx->key[j] = pChild->key[j + t];

	if (!pChild->leaf)
		for (int j = 1; j <= t; j++)
			pChildEx->child[j] = pChild->child[j + t];

	pChild->key_count = t - 1;
	// ��pParent�ĸ�λ���ڵ����ƣ��Ա����pChildEx
	for (int j = pParent->key_count + 1; j > index; j--)
		pParent->child[j + 1] = pParent->child[j];
	pParent->child[index + 1] = pChildEx;

	for (int j = pParent->key_count; j >= index; j--)
		pParent->key[j + 1] = pParent->key[j];
	pParent->key[index] = pChild->key[t]; // ����pParent�е�keyֵ
	pParent->key_count++;
}

void BTree::InsertNonfull(PBTreeNode pNode, int key)
{
	int i = pNode->key_count;

	if (pNode->leaf) //�����Ҷ�ӽڵ�
	{
		while (i >= 1 && key < pNode->key[i]) // ���ϴ��Ԫ�������ƣ�ʹkeyԪ�ز������λ�ã�ƫ��
		{
			pNode->key[i + 1] = pNode->key[i];
			i--;
		}

		pNode->key[i + 1] = key;
		pNode->key_count++;
	}
	else // ������ڲ��ڵ�
	{
		while (i >= 1 && key < pNode->key[i]) // ���ڲ��ڵ�keyֵ��Χ��������Ӧ�ĺ��ӽڵ�
			i--;
		i++;

		if (pNode->child[i]->key_count == (2 * t - 1)) // ������ӽڵ�������
		{
			SplitChild(pNode, i, pNode->child[i]); // ���Ѻ��ӽڵ㣬�����µĴ������

			if (key > pNode->key[i]) //�������ʺϲ���keyֵ�ú��ڵ�:��Ҫi+1����Ϊchild[]Ҫ��key[]��������1
				i++;
		}

		InsertNonfull(pNode->child[i], key); // ���µĽڵ����
	}
}

bool BTree::Delete(int key) /*û����*/
{
	return DeleteNonHalf(root, key);
}

bool BTree::DeleteNonHalf(PBTreeNode pNode, int key)
{
	int i = 1;

	while (i <= pNode->key_count && key > pNode->key[i])
		i++;

	if (pNode->leaf)//case 1���ýڵ�ΪҶ�ӽڵ�
	{
		if (i <= pNode->key_count && key == pNode->key[i]) //ƥ�䵽Ҫɾ��key
		{
			for (int j = i; j < pNode->key_count; j++) //����λ����
				pNode->key[j] = pNode->key[j + 1];
			pNode->key_count--;

			return true;
		}
		else
		{
			return false;//û���ҵ�Ҫɾ���Ĺؼ���
		}
	}

	if (i <= pNode->key_count && key == pNode->key[i])//case 2���ڽڵ�
	{
		if (pNode->child[i]->key_count >= t)//case a
		{
			key = Max(pNode->child[i]);
			pNode->key[i] = key;

			return DeleteNonHalf(pNode->child[i], key);
		}
		else if (pNode->child[i + 1]->key_count >= t)//case b
		{
			key = Min(pNode->child[i + 1]);
			pNode->key[i] = key;

			return DeleteNonHalf(pNode->child[i + 1], key);
		}
		else//case c
		{
			PBTreeNode pChild = UnionChild(pNode, pNode->child[i], pNode->child[i + 1], i);

			return DeleteNonHalf(pChild, key);
		}
	}
	else if (pNode->child[i]->key_count == t - 1)//case 3
	{
		if (i > 1 && pNode->child[i - 1]->key_count >= t)//a_left
		{
			PBTreeNode pMidNode = pNode->child[i];
			PBTreeNode pPreNode = pNode->child[i - 1];

			int nPreNodeKeyCount = pPreNode->key_count;

			for (int j = pMidNode->key_count + 1; j > 1; j--)
				pMidNode->key[j] = pMidNode->key[j - 1];
			pMidNode->key[1] = pNode->key[i - 1];

			for (int j = pMidNode->key_count + 2; j > 1; j--)
				pMidNode->child[j] = pMidNode->child[j - 1];
			pMidNode->child[1] = pPreNode->child[nPreNodeKeyCount + 1];
			pMidNode->key_count++;

			pNode->key[i - 1] = pPreNode->key[nPreNodeKeyCount];

			pPreNode->key[nPreNodeKeyCount] = 0;
			pPreNode->key[nPreNodeKeyCount + 1] = NULL;
			pPreNode->key_count--;

			return DeleteNonHalf(pMidNode, key);
		}
		else if (i <= pNode->key_count && pNode->child[i + 1]->key_count >= t)//a_right
		{
			PBTreeNode pMidNode = pNode->child[i];
			PBTreeNode pNextNode = pNode->child[i + 1];

			int nNextNodeKeyCount = pNextNode->key_count;
			int nMidNodeKeyCount = pMidNode->key_count;

			pMidNode->key[nMidNodeKeyCount + 1] = pNode->key[i];
			pMidNode->child[nMidNodeKeyCount + 2] = pNextNode->child[1];
			pMidNode->key_count++;

			pNode->key[i] = pNextNode->key[1];

			for (int j = 1; j < nNextNodeKeyCount; j++)
				pNextNode->key[j] = pNextNode->key[j + 1];
			for (int j = 1; j <= nNextNodeKeyCount; j++)
				pNextNode->child[j] = pNextNode->child[j + 1];
			pNextNode->key_count--;

			return DeleteNonHalf(pMidNode, key);
		}
		else//b
		{
			if (i > pNode->key_count)//��iָ�����һ���ؼ��ֵ�ʱ�򣬺ϲ���ʱ��Ҫ��ǰ�ƶ�һ��
				i--;

			PBTreeNode pChild = UnionChild(pNode, pNode->child[i], pNode->child[i + 1], i);

			return DeleteNonHalf(pChild, key);
		}
	}

	return DeleteNonHalf(pNode->child[i], key);
}

PBTreeNode BTree::UnionChild(PBTreeNode pParent, PBTreeNode pCLeft, PBTreeNode pCRight, int index)
{
	for (int i = 1; i < t; i++)
		pCLeft->key[t + i] = pCRight->key[i];
	pCLeft->key[t] = pParent->key[index];

	for (int i = 1; i <= t; i++)
		pCLeft->child[t + i] = pCRight->child[i];
	pCLeft->key_count = 2 * t - 1;

	for (int i = index; i < pParent->key_count; i++)
		pParent->key[i] = pParent->key[i + 1];

	for (int i = index + 1; i <= pParent->key_count; i++)
		pParent->child[i] = pParent->child[i + 1];
	pParent->key_count--;

	DellocateNode(pCRight);

	if (pParent->key_count == 0)
	{
		DellocateNode(root);
		root = pCLeft;
	}

	return pCLeft;
}

void BTree::DellocateNode(PBTreeNode pNode)
{
	delete[] pNode->key;
	delete[] pNode->child;
	delete pNode;
}

int BTree::Max(PBTreeNode pNode) // ���Ҹ÷�֧�µ����Ԫ��
{
	while (!pNode->leaf)
	{
		pNode = pNode->child[pNode->key_count + 1];
	}

	return pNode->key[pNode->key_count];
}

int BTree::Min(PBTreeNode pNode)
{
	while (!pNode->leaf) // ���Ҹ÷�֧�µ���СԪ��
	{
		pNode = pNode->child[1];
	}

	return pNode->key[1];
}

void BTree::DeleteTree(PBTreeNode pNode)//���ĸ�Ԫ��û�б�ɾ�� ���Ǹ���Ĺؼ�������ͺ���ָ�������Ѿ�ɾ��
{
	if (pNode->leaf)
	{
		delete[] pNode->key;
		delete[] pNode->child;
	}
	else
	{
		for (int i = 1; i <= pNode->key_count + 1; i++)
		{
			DeleteTree(pNode->child[i]);
			delete pNode->child[i];
		}

		delete[] pNode->key;
		delete[] pNode->child;
	}
}

void BTree::Print(PBTreeNode pNode)
{
	if (pNode->leaf)
	{
		std::cout << "leaf key_count = " << pNode->key_count << " key list :";

		for (int i = 1; i <= pNode->key_count; i++)
		{
			//std::cout << " i = " << i << std::endl;
			std::cout << pNode->key[i] << " , ";
		}

		std::cout << std::endl;
	}
	else
	{
		for (int i = 1; i <= pNode->key_count + 1; i++)
			Print(pNode->child[i]);

		std::cout << "inner node key_count " << pNode->key_count << " key list :";

		for (int i = 1; i <= pNode->key_count; i++)
		{
			//std::cout << " i = " << i << std::endl;
			std::cout << pNode->key[i] << " , ";
		}
		std::cout << std::endl;
	}
}
