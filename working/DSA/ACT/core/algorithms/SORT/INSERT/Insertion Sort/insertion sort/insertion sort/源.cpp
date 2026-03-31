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
template<typename container>
void print_container(const container& c) {
	for (auto& e : c) {
		cout << e << " ";
	}
	cout << endl;
}

//template<typename T>
//void insertion_sort(T* arr, int N) {
//	
//	for (int i = 1; i < N; i++) {
//		int pos = i;
//		T temp = arr[pos];
//		while (pos >= 1) {
//			if (arr[pos - 1] > temp) {
//				arr[pos] = arr[pos - 1];
//				pos--;
//			}
//			else {
//				break;
//			}
//		}
//		arr[pos] = temp;
//	}
//
//}
template<typename iterator, class compare>
void InsertSort(iterator first, iterator last, compare cmp) {
	iterator arr = first;
	size_t N = last - first;
	if (N == 0)return;


	for (size_t cnt = 1; cnt <= N - 1; cnt++) {//一共N-1次插入
		size_t temp = arr[cnt];
		size_t pos;
		for (pos = cnt; pos > 0 && cmp(temp, arr[pos - 1]); pos--) {
			arr[pos] = arr[pos - 1];//如果插入位置pos的前一个更大，pos就前移一格
		}
		arr[pos] = temp;
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

	InsertSort(v.begin(), v.end(), xdh::less<int>());
	print_container(v);

	return 0;
}




















