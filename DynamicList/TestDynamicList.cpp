#include "DynamicList.h"
#include <iostream>
int main()
{
	DynamicList<int> link;
	
	for (int i = 10; i > 0; --i)
	{
		link.rearAdd(i);
	}
	link.print();
	std::cout << link.size() << std::endl;
	DynamicList<int> link1(link);
	link1 = link1;
	link1.print();
	link1.deleteElement(100);
	link1.modifyElement(5, 100);
	link1.insertElement(3, 50);
	std::cout <<"Size: "<< link1.size() << std::endl;
	std::cout << "After Insert: " << std::endl;
	link1.print();

	link1.sort();
	std::cout << "After sort: " << std::endl;
	link1.print();
	link1.destroy();
	std::cout << "Size: "<<link1.size() << std::endl;
	system("pause");
	return 0;
}