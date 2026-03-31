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
//void insert_sort(T* arr, int N) {
//
//	for (int i = 1; i < N; i++) {
//		int j;
//		int temp = arr[i];
//		for (j = i; j > 0; j--) {
//			if (arr[j - 1] >temp) {
//				arr[j] = arr[j - 1];
//			}
//			else {
//				break;
//			}
//		}
//		arr[j] = temp;
//	}
//
//}
//
//
//
//
//
//template<typename T>
//void Merge(T* arr,T* temp ,int left1,int right1,int left2,int right2) {
//	int p1 = left1;
//	int p2 = left2;
//	int p = left1;
//	while (p1 <= right1 && p2 <= right2) {
//		if (arr[p1] < arr[p2]) {
//			temp[p++] = arr[p1++];
//		}
//		else {
//			temp[p++] = arr[p2++];
//		}
//	}
//	while (p1 <= right1 ) {
//		temp[p++] = arr[p1++];
//	}
//	while (p2 <= right2) {
//		temp[p++] = arr[p2++];
//	}
//
//	for (int i = left1; i <= right2; i++) {
//		arr[i] = temp[i];
//	}
//}
//
//
//template<typename T>
//void mergrsort(T* arr, T* temp , int left, int right) {
//	if (right <= left)return;
//
//	if (right - left < 3) {
//		insert_sort(arr+left,right-left+1);
//	}
//	else {
//		int mid = (left + right) >> 1;
//		mergrsort(arr, temp, left, mid);//不能是mid-1，比如left是0，right是1的两个元素区间[45,21]还没排好序，mid等于0
//		mergrsort(arr, temp, mid + 1, right);//将mid-1进行递归的时候还没排序就直接退出了。(因为cpp整数向下取整)
//		Merge(arr, temp, left, mid, mid + 1, right);
//	}
//	int x = 0;
//}
//template<typename T>
//void MergeSort(T* arr, int N) {
//	T* temp = new T[N];
//	mergrsort(arr,temp , 0, N-1);
//	delete[] temp;
//}
//
//
//
//
//template<typename T>
//void MergeSort_(T* arr, int N) {//归并排序非递归版
//	T* temp = new T[N];
//	int cnt = 1;//cnt是每个区间的元素个数
//
//	while (cnt < N) {
//		for (int i = 0; i < N; i += 2 * cnt) {
//			int left1 = i, right1 = i + cnt - 1;
//			int left2 = i + cnt, right2 = i + 2 * cnt - 1;
//			if (right2 >= N ) {//每两个区间进行merge，如果最后剩下的元素只有一个区间就留着下一轮尝试排序
//				if (left2 < N) {//如果剩下的元素是一个完整区间和一个不完整区间就收缩right2(右区间)并merge，保证了下一轮cnt*2
//					right2 = N - 1;//后，最后一个区间剩下的元素是有序的
//				}
//				else {
//					break;
//				}
//			}//只要两个区间都是有序的，就算长度不一样也可以merge
//			Merge(arr, temp, left1, right1, left2, right2);
//		}
//		cnt += cnt;
//	}
//
//	delete[] temp;
//}

template<typename iterator, typename T, class compare>
void merge(vector<T>& temp, iterator arr, size_t lo, size_t mi, size_t hi, compare cmp) {
	temp.clear();
	size_t i = lo, j = mi;
	while (i < mi && j < hi) {
		if (cmp(arr[i], arr[j])) {
			temp.push_back(arr[i++]);
		}
		else {
			temp.push_back(arr[j++]);
		}
	}
	while (i < mi) {
		temp.push_back(arr[i++]);
	}
	while (j < hi) {
		temp.push_back(arr[j++]);
	}
	for (size_t k = 0; k < hi - lo; k++) {
		arr[lo + k] = temp[k];
	}
}
template<typename iterator, typename T, class compare>
void mergesort(vector<T>& temp, iterator arr, size_t lo, size_t hi, compare cmp) {
	if (hi - lo < 2)return;

	size_t mi = (lo + hi) / 2;
	mergesort(temp, arr, lo, mi, cmp);
	mergesort(temp, arr, mi, hi, cmp);
	if (cmp(arr[mi], arr[mi - 1])) merge(temp, arr, lo, mi, hi, cmp);
}
template<typename iterator, class compare>
void Merge_Sort(iterator first, iterator last, compare cmp) {
	iterator arr = first;
	size_t N = last - first;
	using v_type = typename std::decay<decltype(*first)>::type;
	vector<v_type> temp;
	temp.reserve(N);

	size_t len = 1;
	while (len < N) {
		size_t L1 = 0, L2 = len;
		size_t R1, R2;
		size_t shift = len + len;
		for (R1 = L1 + len, R2 = L2 + len; R2 <= N; L1 += shift, R1 += shift, L2 += shift, R2 += shift) {
			merge(temp, arr, L1, L2, R2, cmp);
		}
		if (N > R1) {//剩下一个有序区间不用管，剩一个半区间可以继续merge
			R2 = N;
			merge(temp, arr, L1, L2, R2, cmp);
		}
		len += len;
	}
}
template<typename iterator, class compare>
void MergeSort(iterator first, iterator last, compare cmp) {
	iterator arr = first;
	size_t N = last - first;

	using v_type = typename std::decay<decltype(*first)>::type;
	vector<v_type> temp;
	temp.reserve(N);

	mergesort(temp, first, 0, N, cmp);
	temp.~vector();
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

	MergeSort(v.begin(), v.end(), xdh::less<int>());
	print_container(v);
	
	return 0;
}







































