#include<iostream>
using namespace std;
#include<vector>
#include<stack>

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

	struct pair
	{
		size_t l;
		size_t r;
		pair(size_t L = 0, size_t R = 0) :l(L), r(R) {}
	};
}
template<typename container>
void print_container(const container& c) {
	for (auto& e : c) {
		cout << e << " ";
	}
	cout << endl;
}





//template<typename T>
//void Swap(T& a, T& b) {
//	T temp = a;
//	a = b;
//	b = temp;
//}
//
//template<typename T>
//void selection_sort(T* arr, int N) {
//	for (int i = 0; i < N - 1; i++) {
//		int max = 0;
//		int last = N - 1 - i;
//		for (int j = 1; j <= last; j++) {
//			if (arr[j] > arr[max]) {
//				max = j;
//			}
//		}
//		Swap(arr[max], arr[last]);
//	}
//
//}


//void Swap(int* a, int* b) {
//	int temp = *a;
//	*a = *b;
//	*b = temp;
//}
//
//void selection_sort(int* arr, int N) {//性能优化，一次性选一个最大值和一个最小值
//	int begin = 0, end = N - 1;
//	while(end>begin) {
//		int max = begin , min = begin;
//		for (int j = begin; j <= end; j++) {
//			if (arr[j] > arr[max]) {
//				max = j;
//			}
//			if (arr[j] < arr[min]) {
//				min = j;
//			}
//		}
//		Swap(&arr[max], &arr[end]);//有可能最大的一个跟最后一个交换，换的正好的最小的那个，原来的min标记的就不是最小的数了
//		if (min == end)min = max;
//		Swap(&arr[min], &arr[begin]);
//		end--;
//		begin++;
//	}
//
//}

template<typename iterator, class compare>
void SelectSort(iterator first, iterator last, compare cmp = std::less<typename iterator::value_type>()) {
	iterator arr = first;
	size_t N = last - first;

	size_t begin = 0, end = N - 1;
	while (end > begin) {
		size_t  max = begin, min = begin;
		for (size_t j = begin; j <= end; j++) {
			if (arr[j] > arr[max]) {
				max = j;
			}
			if (arr[j] < arr[min]) {
				min = j;
			}
		}
		swap(arr[max], arr[end]);//有可能最大的一个跟最后一个交换，换的正好的最小的那个，原来的min标记的就不是最小的数了
		if (min == end)min = max;
		swap(arr[min], arr[begin]);
		end--;
		begin++;
	}
}




int main() {
	int arr[] = { 857,521,250,911,361,438,985,211,110,666,369 };
	int len = sizeof(arr) / sizeof(int);

	vector<int> v;
	v.reserve(len);
	for (int i = 0; i < len; i++) {
		v.push_back(arr[i]);
	}
	print_container(v);

	SelectSort(v.begin(), v.end(), xdh::less<int>());
	print_container(v);

	return 0;
}



















