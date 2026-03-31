#include<iostream>
using namespace std;
#include<vector>

namespace xdh {
	template<typename T>
	class less {
	public:
		bool operator ()(const T& a, const T& b) {
			return a < b;
		}
	};

	template<typename T>
	class greater {
	public:
		bool operator ()(const T& a, const T& b) {
			return a > b;
		}
	};
}


//template<typename T>
//void bubble(T* arr, int& lo, int& hi) {
//	int first = lo;
//	int last = lo;
//	bool exchanged = false;
//
//	while (lo < hi - 1) {
//		if (arr[lo] > arr[lo + 1]) {
//			T t = arr[lo];
//			arr[lo] = arr[lo + 1];
//			arr[lo + 1] = t;
//
//			last = lo + 1;
//		}
//		lo++;
//	}
//	lo = first; hi = last;
//	while (lo < hi - 1) {
//		hi--;
//		if (arr[hi] < arr[hi - 1]) {
//			T t = arr[hi - 1];
//			arr[hi - 1] = arr[hi];
//			arr[hi] = t;
//
//			first = hi -1 ;
//		}
//	}
//
//	lo = first;
//	hi = last;
//}
//
//
//template<typename T>
//void bubble_sort(T* arr, int lo, int hi) {
//	while (hi > lo + 1)
//		bubble(arr, lo, hi);
//}
//
//
//template<typename T>
//void bubble_sort(T* arr, int N) {
//	bubble_sort(arr, 0, N);//Çø¼ä×ó±ÕÓÒ¿ª
//}

template<typename iterator, class compare>
void Scan(iterator arr, size_t& lo, size_t& hi, compare cmp) {
	size_t first = lo;
	size_t last = lo;

	while (lo < hi - 1) {
		if (cmp(arr[lo + 1], arr[lo])) {
			swap(arr[lo], arr[lo + 1]);
			last = lo + 1;
		}
		lo++;
	}
	lo = first; hi = last;
	while (lo < hi - 1) {
		hi--;
		if (cmp(arr[hi], arr[hi - 1])) {
			swap(arr[hi], arr[hi - 1]);
			first = hi - 1;
		}
	}

	lo = first; hi = last;
}
template<typename iterator, class compare>
void BubbleSort(iterator first, iterator last, compare cmp) {
	size_t N = last - first;
	size_t lo = 0, hi = N;
	while (hi > lo + 1)
		Scan(first, lo, hi, cmp);
}

template<typename container>
void print_container(const container& c) {
	for (auto& e : c) {
		cout << e << " ";
	}
	cout << endl;
}

int main() 
{

	int arr[] = { 857,521,250,911,361,438,985,211,110,666,369 };
	int len = sizeof(arr) / sizeof(int);

	vector<int> v;
	v.reserve(len);
	for (int i = 0; i < len; i++) {
		v.push_back(arr[i]);
	}
	print_container(v);
	
	BubbleSort(v.begin(), v.end(),xdh::less<int>());
	print_container(v);

	return 0;
}





