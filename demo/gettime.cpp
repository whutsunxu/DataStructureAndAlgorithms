/*
#include <time.h>　　　//引入头文件
#include <iostream>
const long long M = 1000000000;
int main()
{
	clock_t start, end;//定义clock_t变量
	start = clock(); //开始时间
	long long  i = 0;

	while (i < M) i++;  //需计时的函数

	end = clock();   //结束时间
	std::cout << "time = " << double(end - start) / CLOCKS_PER_SEC << "s" << std::endl;  //输出时间（单位：ｓ）
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