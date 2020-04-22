/*
#include <time.h>������//����ͷ�ļ�
#include <iostream>
const long long M = 1000000000;
int main()
{
	clock_t start, end;//����clock_t����
	start = clock(); //��ʼʱ��
	long long  i = 0;

	while (i < M) i++;  //���ʱ�ĺ���

	end = clock();   //����ʱ��
	std::cout << "time = " << double(end - start) / CLOCKS_PER_SEC << "s" << std::endl;  //���ʱ�䣨��λ����
}
*/
#include <iostream>
#include <iterator>
#include <vector>

int main()
{
	std::vector<int> v{ 3, 1, 4 };

	auto it = v.begin();

	auto pv = std::next(it, 2);

	std::cout << "it: "<<*it<<"pv: "<<*pv << '\n';
	std::cout << "length: " << std::distance(v.begin(), v.end());
	std::cout << " " << *(std::prev(v.end(), std::distance(v.begin(), v.end()) / 2));
}