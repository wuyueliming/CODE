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
//void ShellSort(T* arr, int N) {
//	int gap = N;
//	while (gap != 1){
//		gap = gap / 3 + 1;//放在循环体开头进行gap/3+1，如果等于1了先排序然后出循环，而不是循环体结尾变gap等于1的时候直接出循环了
//		for (int i = gap; i < N; i++) {
//			int temp = arr[i];
//			int pos = i;
//			while (pos - gap >= 0) {
//				if (arr[pos - gap] > temp) {
//					arr[pos] = arr[pos - gap];
//					pos -= gap;
//				}
//				else {
//					break;
//				}
//			}
//			arr[pos] = temp;
//
//		}	
//	}
//	
//	
//}
void get_sequence(vector<size_t>& v, size_t N) {
	v.push_back(1);
	size_t a = 16, b = 4;
	while (v.back() < N) {
		v.push_back(a - 3 * b + 1);
		a *= 4; b *= 2;
	}
	v.pop_back();
	a = 4, b = 2;
	while (v.back() < N) {
		size_t item = 9 * (a - b) + 1;//不会出现重复元素
		v.push_back(item);
		size_t pos;
		for (pos = v.size() - 1; pos > 0 && v[pos - 1] > item; pos--) {
			v[pos] = v[pos - 1];
		}
		v[pos] = item;
		a *= 4; b *= 2;
	}
	v.pop_back();
}
template<typename iterator, class compare>
void ShellSort(iterator first, iterator last, compare cmp) {
	iterator arr = first;
	size_t N = last - first;

	vector<size_t> sequence;
	get_sequence(sequence, N);

	while (!sequence.empty()) {
		size_t gap = sequence.back();
		sequence.pop_back();

		for (size_t i = gap; i < N; i++) {
			size_t pos;
			auto temp = arr[i];
			for (pos = i; pos >= gap && cmp(temp, arr[pos - gap]); pos -= gap) {
				arr[pos] = arr[pos - gap];
			}
			arr[pos] = temp;
		}
	}
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

	ShellSort(v.begin(), v.end(), xdh::less<int>());
	print_container(v);

	return 0;
}



















