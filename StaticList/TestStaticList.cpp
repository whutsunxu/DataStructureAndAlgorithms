#include <iostream>
#include "StaticList.h"
using namespace std;

int main()
{
	StaticList<int> TestList;
	TestList.Insert(12);
	TestList.Insert(13);
	TestList.Insert(14);
	TestList.Insert(15);
	TestList.Insert(16);
	cout << "Initial List:" << endl;
	TestList.Show();

	cout << "After insert at position 4th" << endl;
	TestList.Insert(17, 3);
	TestList.Show();

	int m = 0;
	TestList.Delete(m, 7);
	cout << "____________" << m << "_______________\n";
	TestList.Show();
	return 0;
}