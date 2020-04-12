#include "LeftistHeap.h"
#include <iostream>

int main()
{
	LeftistHeap<std::string> s1;
	if (s1.isEmpty())
		std::cout << "heap is empty" << std::endl;
	else
		std::cout << "heap is not empty" << std::endl;
	for (int i = 0; i < 10; i++)
		s1.insert(std::to_string(i));

	LeftistHeap<std::string>s2;
	for (int i = 1; i < 30; i += 2)
		s2.insert(std::to_string(i));

	s2.merge(std::move(s1));
	return 0;
}