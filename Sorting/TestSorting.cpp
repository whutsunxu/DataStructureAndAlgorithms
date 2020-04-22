#include "insertSorting.h"
#include <iostream>
#include <vector>
#include <cstdlib>
#include <time.h>

const int M = 10000;

int main()
{
	double mt;// time
	clock_t st, et;
	std::less<int> funcLess;
	std::greater<int> funcGreater;
	std::vector<int> A;
	//srand(unsigned(time(nullptr)));
	for (int i = 0; i < M; i++)
	{
		A.push_back(int((rand() % 3*M)));
	}
	std::vector<int> B(A);
	std::vector<int> C(A);
	std::vector<int> D(A);
	std::vector<int> E(A);
	/* insert sort */
	std::cout <<"/--------------------insert sort--------------------/\n";
	//std::cout <<"origin vector A: " << std::endl;
	//for (auto i : A) std::cout << i << " ";
	std::cout << std::endl;
	st = clock();
	//insertSort(A.begin(), A.end(),funcLess);
	et = clock();
	mt = (double)(et - st) / CLOCKS_PER_SEC;
	std::cout << "After Sort\n";
	//for (std::vector<int>::iterator i = A.begin(); i != A.end(); i++)
	//	std::cout << *i << " ";
	std::cout << "Time used: " << mt << " s\n";

	/* shell sort */
	std::cout << "/--------------------shell sort--------------------/\n";
	//std::cout << "origin vector B: " << std::endl;
	//for (auto i : B) std::cout << i << " ";
	std::cout << std::endl;
	st = clock();
	shellSort(B.begin(), B.end(), funcLess);
	et = clock();
	mt = double((et - st)) / CLOCKS_PER_SEC;

	// after sort
	std::cout << "After Sort\n";
	//for (auto i : B)	std::cout << i << " ";
	std::cout << "Time used: " << mt << " s\n" ;

	/* hibbardShell sort */
	std::cout << "/--------------------HibbardShell sort--------------------/\n";
	//std::cout << "origin vector : " << std::endl;
	//for (auto i : C) std::cout << i << " ";
	std::cout << std::endl;
	st = clock();
	hibbardShellSort(C.begin(), C.end(), funcLess);
	et = clock();
	mt = double((et - st)) / CLOCKS_PER_SEC;

	// after sort
	std::cout << "After Sort\n";
	//for (auto i : C)	std::cout << i << " ";
	std::cout << "Time used: " << mt << " s\n";
	
	/* heap sort */
	std::cout << "/--------------------heap sort--------------------/\n";
	std::cout <<"origin vector: " << std::endl;
	//for (auto i : D) std::cout << i << " ";

	st = clock();
	HeapSort(D.begin(), D.end(), funcLess);
	et = clock();
	mt = double((et - st)) / CLOCKS_PER_SEC;

	// after sort
	std::cout << "After Sort\n";
	//for (auto i : D)	std::cout << i << " ";
	std::cout << "Time used: " << mt << " s\n";

	/* merge sort */
	std::cout << "/--------------------merge sort--------------------/\n";
	std::cout << "origin vector: " << std::endl;
	//for (auto i : E) std::cout << i << " ";

	st = clock();
	mergeSort(E, funcLess);
	et = clock();
	mt = double((et - st)) / CLOCKS_PER_SEC;

	// after sort
	std::cout << "\nAfter Sort\n";
	//for (auto i : E)	std::cout << i << " ";
	std::cout << "\nTime used: " << mt << " s\n";
	return 0;
}