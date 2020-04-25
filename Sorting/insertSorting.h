#pragma once
#include <utility>
#include <vector>
#include <functional>
#include <cmath>

/*insert sort algorithm
  athr:sunxu
  reference:
  */
const int quickSortLimit = 10;
template <class Iterator, class Comparator>
void insertSort(const Iterator& begin, const Iterator& end, Comparator func = std::less<decltype(*begin)>)
{
	if (begin == end)
		return;
	for (Iterator i = begin + 1; i != end; i++)
	{
		auto tmp = std::move(*i);
		Iterator j;
		for ( j= i; j !=begin && func(tmp,*(j-1)); j--)
		{
			*j = std::move(*(j - 1));
		}
		*j = std::move(tmp);
	}
}
/*shell sort algorithm(shell increment)
  athr:sunxu
  reference:
  */
template <class Iterator, class Comparator>
void shellSort(const Iterator& begin, const Iterator& end, Comparator func = std::less<decltype(*begin)>)
{
	if (begin == end)
		return;
	for (int gap = int(std::distance(begin, end)); gap > 0; gap /= 2)
	{
		for (Iterator i = begin + gap; i != end; i++)
		{
			auto tmp = std::move(*i);
			Iterator j = i;
			for (; j >= begin + gap && func(tmp, *(j - gap)); j -= gap)
				*j = *(j - gap);
			*j = std::move(tmp);
		}
	}
}
template <class Iterator, class Comparator>
void hibbardShellSort(const Iterator& begin, const Iterator& end, Comparator func = std::less<decltype(*begin)>)
{
	if (begin == end)
		return;
	int length = int(std::distance(begin, end));
	int k = int(std::log(length) / std::log(2));
	for (; k > 0; k--)
	{
		int gap = int(std::pow(2, k)) - 1;
		for (Iterator i = begin + gap; i != end; i++)
		{
			auto tmp = std::move(*i);
			Iterator j = i;
			for (; j >= begin + gap && func(tmp, *(j - gap)); j -= gap)
				*j = *(j - gap);
			*j = std::move(tmp);
		}
	}
}
//template void insertSort<std::vector<int>::iterator, std::less<int>>(
	//std::vector<int>::iterator, std::vector<int>::iterator, std::less<int>);
template <class Iterator, class Comparator>
void percDown(Iterator begin, int i, int length, Comparator func)
{
	auto tmp = std::move(*(begin+i));
	int child;
	for (;2 * i + 1 < length;i=child)
	{
		child = 2 * i;
		if (child != length - 1 && func(*(begin + child), *(begin + child + 1)))
			child++;
		if (func(tmp, *(begin + child)))
			*(begin + i) = std::move(*(begin + child));
		else
			break;
	}
	*(begin + i) = std::move(tmp);
}
template <class Iterator>
void swap(Iterator A, Iterator B)
{
	auto tmp = std::move(*A);
	*A = std::move(*B);
	*B = std::move(tmp);
}
template <class Iterator, class Comparator>
void HeapSort(Iterator begin, Iterator end, Comparator func)
{
	int length = int(std::distance(begin, end));
	int i = length / 2 - 1;
	for (; i >= 0; i--)
		percDown(begin, i, length, func);
	int j = length - 1;
	for (; j > 0; j--)
	{
		swap(begin, begin + j);
		percDown(begin, 0, j, func);
	}
}
template <class Comparable, class Comparator>
void merge(std::vector<Comparable>& A, std::vector<Comparable>& tmpA, int leftPos, 
	int rightPos, int rightEnd, Comparator func)
{
	int leftEnd = rightPos - 1;
	int tmpPos = leftPos;
	int numElement = rightEnd - leftPos + 1;

	while (leftPos <= leftEnd && rightPos <= rightEnd) // compare the common index part of two halves
	{
		if (func(A[leftPos], A[rightPos]))
			tmpA[tmpPos++] = std::move(A[leftPos++]);
		else
			tmpA[tmpPos++] = std::move(A[rightPos++]);
	}
	while (leftPos <= leftEnd)
		tmpA[tmpPos++] = std::move(A[leftPos++]); // copy the rest elements
	while (rightPos <= rightEnd)
		tmpA[tmpPos++] = std::move(A[rightPos++]); // copy the rest elements
	for (int i = 0; i < numElement; i++, rightEnd--)
		A[rightEnd] = std::move(tmpA[rightEnd]);
}
template <class Comparable, class Comparator>
void mergeSort1(std::vector<Comparable>& A, std::vector<Comparable>& tmpA,
	int left, int right, Comparator func)
{
	if (left < right)
	{
		int center = (left + right) / 2;
		mergeSort1(A, tmpA, left, center, func);
		mergeSort1(A, tmpA, center + 1, right, func);
		merge(A, tmpA, left, center + 1, right, func);
	}
}

template <class Comparable,class Comparator>
void mergeSort(std::vector<Comparable>& A, Comparator func)
{
	std::vector<Comparable> tmpA(A.size());     // can it be replaced?
	mergeSort1(A, tmpA, 0, int(A.size() - 1), func);
}

template<class Comparable,class Comparator>
const Comparable& media3(std::vector<Comparable>& A, 
						 const int left, const int right, const Comparator func)
{
	int center = (left + right) / 2;
	if (func(A[center], A[left]))
		std::swap(A[center], A[left]);
	if (func(A[right], A[left]))
		std::swap(A[right], A[left]);
	if (func(A[right], A[center]))
		std::swap(A[center], A[right]);
	
	std::swap(A[center], A[right - 1]);  // move the pivot to index [right-1]
	return A[right - 1];
}
template <class Comparable,class Comparator>
void quickSort1(std::vector<Comparable>&A, const int left, const int right, Comparator func)
{
	if(left + quickSortLimit < right+1)
	{
		const Comparable& pivot = media3(A, left, right, func);

		int i = left;
		int j = right - 1;

		while (true)
		{
			while (func(A[++i] ,pivot)) {}
			while (func(pivot, A[--j])) {}
			if (i < j)
				std::swap(A[i], A[j]);
			else
				break;
		}

		std::swap(A[i], A[right - 1]);
		quickSort1(A, left, i - 1, func);  //the pivot is not in the following sort precess
		quickSort1(A, i + 1, right, func);
	}
	else
	{
		insertSort(std::next(A.begin(),left), std::next(A.begin() ,(right+1)), func);
	}
}
template <class Comparable, class Comparator>
void quickSort(std::vector<Comparable>& A, const int left, const int right, Comparator func)
{
	quickSort1(A, left, right-1, func);
}
