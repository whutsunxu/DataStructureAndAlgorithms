#include "StaticList.h"
#include <iostream>

template <class T>
StaticList<T>::StaticList():length(0)
{
	for (int i = 0; i < MAXSIZE - 1; i++)
	{
		StList[i].curse = i + 1;
	}
	StList[MAXSIZE - 1].curse = 0;
}
template <class T>
StaticList<T>::~StaticList()
{

}
template <class T>
bool StaticList<T>::Insert(const T& x, int index /*= 1*/) 
{
	using namespace std;
	if (Full())
	{
		cout << "Cannot insert to a fluu list!" << endl;
		return false;
	}
	else if (index <1 || index > length + 1)
	{
		cout << "The invalid Index" << endl;
		return false;
	}
	else
	{
		int k = NewSpace(); // get the position index for insert operation
		int j = MAXSIZE - 1;
		if (k) // not get zero
		{
			StList[k].data = x;
			for (int i= 1; i <= index - 1; i++) // get the position index before the insert position
			{
				j = StList[j].curse;
			}
				StList[k].curse = StList[j].curse;
				StList[j].curse = k;
			length++;
			return true;
		}
		else
			return false;
	}
}
template <class T>
bool StaticList<T>::Delete(T& x, int index /* =1 */)
{
	using namespace std;
	if (Empty())
	{
		cout << "Cannot delete an element in an empty list." << endl;
		return false;
	}
	else if (index < 1 || index > length)
	{
		cout << "Invalid Index!" << endl;
		return false;
	}
	else
	{
		int k = MAXSIZE - 1;
		for (int i = 1; i <= index - 1; i++)
		{
			k = StList[k].curse;
		}
		int i = StList[k].curse;
		StList[k].curse = StList[i].curse;
		x = StList[i].data;
		DeleteSpace(i);
		length--;
		return true;
	}
}
template <class T>
void StaticList<T>::Show() const
{
	using namespace std;
	if (Empty())
	{
		cout << "The List is Empty!\n";
		return;
	}
	else
	{
		int k = StList[MAXSIZE - 1].curse;
		cout << "---------------%List%----------------:\n";
		for (int i = 1; i <= length; i++)
		{
			cout << StList[k].data << "\t";
			k = StList[k].curse;
			if (!(i % 5)) cout << endl;
		}
		cout << endl;
	}
}
template <class T>
bool StaticList<T>::Full() const
{
	if (length == MAXSIZE - 2) // only #0 and MAXSIZE-1 are left
		return true;
	else
		return false;
}
template <class T>
bool StaticList<T>::Empty() const
{
	return (length == 0);
}
template <class T>
void StaticList<T>::DeleteSpace(int index)
{
	StList[index].curse = StList[0].curse;
	StList[0].curse = index;  // set the index as the first free node
}
template <class T>
int StaticList<T>::NewSpace()
{
	int i = StList[0].curse; // the current curse is always stored in StList[0]
	if (i) // not zero means not full
	{
		StList[0].curse = StList[i].curse;
	}
	return i;
}