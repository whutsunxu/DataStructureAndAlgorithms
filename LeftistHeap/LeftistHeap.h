#pragma once
#include <string>
template <class Comparable>
class LeftistHeap 
{
public:
	LeftistHeap();
	LeftistHeap(const LeftistHeap& rhs);
	LeftistHeap(LeftistHeap&& rhs);
	~LeftistHeap();

	LeftistHeap operator=(const LeftistHeap& rhs);
	LeftistHeap operator=(LeftistHeap&& rhs);

	bool isEmpty() const;
	const Comparable& findMin() const;

	void insert(const Comparable& x);
	//void insert(Comparable&& x);

	void deleteMin();
	void deleteMin(Comparable& item);
	void makeEmpty();
	void merge(LeftistHeap&& rhs);

private:
	struct LeftistNode
	{
		Comparable element;
		LeftistNode* left;
		LeftistNode* right;
		int npl;

		LeftistNode(const Comparable& e, LeftistNode* lt = nullptr,
			LeftistNode* rt = nullptr, int np = 0)
			:element(e), left(lt), right(rt), npl(np) {}
		LeftistNode(Comparable&& e, LeftistNode* lt = nullptr,
			LeftistNode* rt = nullptr, int np = 0)
			:element{ std::move(e) }, left{ lt }, right{ rt }, npl{ np } {}
	};
	LeftistNode* root;
	LeftistNode* merge(LeftistNode* hl, LeftistNode* h2);
	LeftistNode* merge1(LeftistNode* hl, LeftistNode* h2);

	void swapChildren(LeftistNode* t);
	void reclaimMemory(LeftistNode* t);
	LeftistNode* clone(LeftistNode* t) const;
};

template class LeftistHeap<std::string>;
//template class LeftistHeap<int>;
