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
//
//template<typename T>
//void insert_sort(T* arr, int N) {
//
//	for (int i = 1; i < N; i++) {
//		int j;
//		int temp = arr[i];
//		for (j = i; j > 0; j--) {
//			if (arr[j - 1] > temp) {
//				arr[j] = arr[j - 1];
//			}
//			else {
//				break;
//			}
//		}
//		arr[j] = temp;
//	}
//}
//
//template<typename T>
//int get_mid(T* arr, int N) {
//	T l = arr[0];
//	T r = arr[N - 1];
//	T m = arr[N / 2];
//
//	if (r > l) {
//		if (m > r) {
//			return N - 1;
//		}
//		else {
//			if (m > l) {
//				return N / 2;
//			}
//			else {
//				return 0;
//			}
//		}
//	}
//	else {
//		if (m > l) {
//			return 0;
//		}
//		else {
//			if (m > r) {
//				return N / 2;
//			}
//			else {
//				return N - 1;
//			}
//		}
//	}
//
//}
//
//
//
//template<typename T>
//int getP(T* arr, int left, int right) {
//	int mid = left+get_mid(arr + left, right - left + 1);
//	swap(arr[left], arr[mid]);
//
//	int pivot = left;
//	int key = arr[left];
//
//	//int L = left + 1;-->L不能从left+1开始，否则如果left选到的就是最小的值，那么从L到R的闭区间就不可能找到比left位置还小的
//	int L = left, R = right;//值，那么出循环的时候L和R再left+1的位置相遇，这个值不是小于key就不能进行交换。如果从L从left开始
//	while (R > L) {//那么即使left(pivot)位置是最小值最后也只是自己和自己交换。
//		while (R > L && arr[R] >= key) {//R先走保证了出循环的时候一定是小于key的位置和pivot交换
//			R--;
//		}
//		while (R > L && arr[L] <= key) {//必须加上=号，如果不加上等号的话第一轮交换就会把pivot也就是left的值进行交换也就
//			L++;//想要L左边严格小于key，R右边严格大于key，最终L和R中间全是key，此时出大循环不需要交换。但是如果有重复数可能会
//		}//进入死循环，如果LR同时等于key时候break的话，可能L和R中间还有小于或大于key的值，只不过被两个跟key相等的值夹在里面了。
//		Swap(arr[L], arr[R]);
//	}
//	Swap(arr[pivot], arr[L]);
//	return L;
//}
//
//
//template<typename T>
//void quicksort(T* arr, int left,int right,int depth,int dead) {
//	if (left >= right) return;
//
//	if (right - left < 3) {
//		insert_sort(arr + left, right - left + 1);
//	}
//	else if(depth>dead){
//		//mergrsort(arr + left, right - left + 1);//自省，当深度过大时说明选p出现问题，改用堆排
//		insert_sort(arr + left, right - left + 1);
//	}
//	else {
//		int pivot = getP(arr, left, right);
//		quicksort(arr, left, pivot - 1,depth+1,dead);
//		quicksort(arr, pivot + 1, right,depth+1,dead);
//	}
//
//}
//template<typename T>
//void QuickSort(T* arr, int N) {
//	int d = 0;
//	for (int i = 1; i < N; i *= 2) {
//		d++;
//	}
//	quicksort(arr, 0, N - 1,d,2*d);
//}
//
//
//
//
//template<typename T>
//void QuickSort_(T* arr, int N) {//非递归快排，其实优化不大
//	int left = 0;
//	int right = N - 1;//快排递归的核心是不断使用函数栈帧记录左右区间；
//
//	int* stackL = new int[N/2] {0};
//	int* stackR = new int[N/2] {0};
//	int top1 = 0, top2 = 0;
//	stackL[top1++] = left;
//	stackR[top2++] = right;
//	while (top1 > 0 && top2 > 0) {
//		int L = stackL[--top1];
//		int R = stackR[--top2];
//
//		if (R - L < 4) {
//			insert_sort(arr + L, R - L + 1);
//		}
//		else {
//			int pivot = getP(arr, L, R);
//			if (R > L) {
//				stackL[top1++] = pivot + 1; stackR[top2++] = R;
//			}
//			if (R > L) {
//				stackL[top1++] = L; stackR[top2++] = pivot - 1;
//			}
//		}
//	}
//
//	delete[]stackL;
//	delete[]stackR;
//}


template<typename iterator>
size_t get_mid(iterator arr, size_t N) {
	auto l = arr[0];
	auto r = arr[N - 1];
	auto m = arr[N / 2];

	if (r > l) {
		if (m > r) {
			return N - 1;
		}
		else {
			if (m > l) {
				return N / 2;
			}
			else {
				return 0;
			}
		}
	}
	else {
		if (m > l) {
			return 0;
		}
		else {
			if (m > r) {
				return N / 2;
			}
			else {
				return N - 1;
			}
		}
	}

}


template<typename iterator, class compare>
size_t partition(iterator arr, size_t lo, size_t hi, compare cmp) {
	//普遍高效
	size_t  mid = lo + get_mid(arr + lo, hi - lo);
	swap(arr[mid], arr[lo]);

	auto pivot = arr[lo];
	size_t l = lo, r = hi - 1;
	while (r > l) {
		while (r > l && (arr[r] == pivot || cmp(pivot, arr[r]))) {
			r--;
		}
		while (r > l && (arr[l] == pivot || cmp(arr[l], pivot))) {
			l++;
		}
		swap(arr[l], arr[r]);
	}
	swap(arr[l], arr[lo]);

	return l;
}
template<typename iterator, class compare>
void quicksort(iterator arr, size_t lo, size_t hi, size_t depth, compare cmp) {
	static size_t max_dep = hi - lo;
	if (hi - lo < 10) {
		InsertSort(arr + lo, arr + hi, cmp);
	}
	else {
		if (depth > 2 * max_dep) {
			MergeSort(arr + lo, arr + hi, cmp);
		}
		else {
			size_t mi = partition(arr, lo, hi, cmp);
			quicksort(arr, lo, mi, depth + 1, cmp);
			quicksort(arr, mi + 1, hi, depth + 1, cmp);
		}
	}
}
template<typename iterator, class compare>
void QuickSort(iterator first, iterator last, compare cmp) {
	iterator arr = first;
	size_t N = last - first;

	size_t d = 1;
	for (size_t n = N; n != 1; n /= 2) {
		d++;
	}

	quicksort(arr, 0, N, 1, cmp);
}




template<typename iterator, class compare>
xdh::pair partition_(iterator arr, size_t lo, size_t hi, compare cmp) {
	//重复元素多时比hoare高效。优化:java的双轴点三区划分，缓存优化
	auto pivot = arr[lo];
	size_t l = lo, r = hi;
	size_t k = lo;
	while (k < r) {
		if (arr[k] == pivot) {
			k++;
			continue;
		}
		if (cmp(arr[k], pivot)) {
			swap(arr[l++], arr[k]);
		}
		else {
			swap(arr[--r], arr[k]);
		}
	}
	xdh::pair p = { l,k };
	return  p;
}
template<typename iterator, class compare>
void quick_sort(iterator arr, size_t lo, size_t hi, compare cmp) {
	stack<xdh::pair>st;

	st.push(xdh::pair(lo, hi));
	while (!st.empty()) {
		xdh::pair section(st.top().l, st.top().r);
		st.pop();

		lo = section.l; hi = section.r;
		section = partition_(arr, section.l, section.r, cmp);

		if (hi > section.r + 1)st.push(xdh::pair(section.r, hi));
		if (section.l > lo + 1)st.push(xdh::pair(lo, section.l));
	}
}
template<typename iterator, class compare>
void Quick_Sort(iterator first, iterator last, compare cmp) {
	iterator arr = first;
	size_t N = last - first;
	quick_sort(arr, 0, N, cmp);
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

	QuickSort(v.begin(), v.end(), xdh::less<int>());
	print_container(v);

	return 0;
}





