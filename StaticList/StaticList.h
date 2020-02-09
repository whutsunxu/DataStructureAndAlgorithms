#pragma once
const int MAXSIZE = 10000;

template <class T>
class StaticList
{
public:
	struct node
	{
		T data;
		int curse;
	};
	StaticList();
	~StaticList();
	bool Insert(const T &x, int index= 1);
	bool Delete(T &x, int index= 1);
	void Show() const;
private:
	int NewSpace(); // return the curse for new element
	void DeleteSpace(int index); // delete the element at position "index"
	bool Empty() const;
	bool Full() const;
	node StList[MAXSIZE]; // the container
	int length;
};
template class StaticList <int>; // explicit instantiation
template class StaticList <double>;
