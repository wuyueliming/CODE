#include<iostream>
using namespace std;

template<typename iterator, typename T>
iterator search(iterator first, iterator last, const T& e) {
	srand(time(NULL));
	return rand() % 2 == 0 ? fib_search(_start, size(), e) : bin_search(_start, size(), e);
}
template<typename iterator, typename T>
iterator fib_search(iterator first, iterator last, const T& e) {
	iterator arr = first;
	size_t N = last - first;
	size_t lo = 0; size_t hi = N;
	size_t  mi = 0.382 * lo + 0.618 * hi;

	while (hi > lo) {
		if (e < arr[mi]) {
			hi = mi;
		}
		else if (e > arr[mi]) {
			lo = mi + 1;
		}
		else {
			return first + mi;
		}
		mi = 0.382 * lo + 0.618 * hi;
	}
	return nullptr;
}
template<typename iterator, typename T>
iterator bin_search(iterator first, iterator last, const T& e) {
	iterator arr = first;
	size_t N = last - first;
	size_t lo = 0; size_t hi = N;
	size_t  mi = (hi + lo) / 2;
	while (lo < hi) {//左闭右开的查找区间
		if (e < arr[mi]) {//如果大于e
			hi = mi;//mi及其右侧纳入[hi,n)，保证[hi,n)严格大于e
		}
		else {//如果小于等于e
			lo = mi + 1;//mi及其左侧纳入[0,mi)，保证[0,mi)小于等于e
		}
		mi = (hi + lo) / 2;
	}//退出循环时lo=hi，区间为空。lo为大于e的第一个元素，lo-1为不大于e的最后一个元素
	return first[lo - 1] == e ? first + lo - 1 : nullptr;
}

int main()
{









	return 0;
}