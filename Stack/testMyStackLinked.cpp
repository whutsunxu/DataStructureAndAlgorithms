#include <iostream>
#include "LinkedStack.h"

int main()
{
	using namespace std;
	cout << "Test:" << endl;
	int a = 8;
	int b = 9;
	LinkedStack<int> s;
	s.Push(a);
	s.Push(b);
	cout << "Top: " << s.Top() << endl;
	cout << "Length: " << s.GetLength() << endl;
	s.Pop();
	cout << "After Pop" << endl;
	cout << "Top: " << s.Top() << endl;
	cout << "Length: " << s.GetLength() << endl;
	return 0;
}
