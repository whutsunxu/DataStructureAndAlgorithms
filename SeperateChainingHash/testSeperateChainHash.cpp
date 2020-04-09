#include <iostream>
#include "SPHash.h"
#include <string>

int main()
{
	HashTable<std::string> a(77);
	for (int i = 0; i < 50; i++)
	{
		a.insert(std::to_string(i));
	}
	if (a.contain("10"))
	{
		std::cout << "a has 10" << std::endl;
		a.remove("10");
	}
	if (a.contain("10"))
	{
		std::cout << "a has 10" << std::endl;
	}
	else
		std::cout << "a doesnot has 10" << std::endl;

	return 0;	
}