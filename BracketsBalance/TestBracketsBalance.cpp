#include <iostream>
#include "BracketsBalance.h"

using namespace std;
const int M = 10;
int main()
{
	
	char a[M] = "{([])}";
	BracketsBalance(a, 6);
	return 0;
}