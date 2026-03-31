#include<iostream>
using namespace std;
#include<vector>
#include<assert.h>

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
//void AdjustDown_max(T* heap, int N, int index) {//本质是一个节点左子树和右子树都是一个最大堆，现在
//	int parent, child, temp;//将这个节点和两个子树合成一个最大堆
//
//	temp = heap[index];
//	for (parent = index, child = parent * 2 + 1; child < N; parent = child, child = child * 2 + 1) {
//		if (child + 1 < N && heap[child + 1] > heap[child]) {
//			child++;
//		}
//		if (heap[child] > temp) {
//			heap[parent] = heap[child];
//		}
//		else {
//			break;
//		}
//	}
//	heap[parent] = temp;
//
//}
//
//template<typename T>
//void Insert_max(T* heap, int& N,int X) {
//	heap[N++] = X; //每次插入一个值向上调整建堆(时间复杂度高，堆是上尖下宽，最后一层占总节点的一半。向上调整是上面节点调整层数少，下面调整的层数多)        
//	
//	int child = N - 1;     //以1为根节点的二叉树的左右孩子是2*parent、2*parent+1，求父亲公式是child/2
//	int temp = heap[child];//以0为根节点的二叉树的左右孩子是2*parent+1、2*parent+2，求父亲是(child-1)/2 
//
//	for (int parent = (child-1) / 2; child > 0 && temp > heap[parent] ;child=parent,parent=(parent-1)/2) {
//		heap[child] = heap[parent];
//	}
//	heap[child] = temp;
//}
//template<typename T>
//void Insert_min(T* heap, int& N, int X) {
//	heap[N++] = X;
//
//	int child = N - 1;     //以1为根节点的二叉树的左右孩子是2*parent、2*parent+1，求父亲公式是child/2
//	int temp = heap[child];//以0为根节点的二叉树的左右孩子是2*parent+1、2*parent+2，求父亲是(child-1)/2 
//
//	for (int parent = (child - 1) / 2; child > 0 && temp < heap[parent]; child = parent, parent = (parent - 1) / 2) {
//		heap[child] = heap[parent];
//	}
//	heap[child] = temp;
//}
//
//
//template<typename T>
//T Delete_max(T* heap, int& N) {
//	T ret = heap[0];
//	heap[0] = heap[--N];
//
//	int temp = heap[0];
//	int parent = 0;
//	int child;
//	for (child = parent * 2 + 1; child < N; parent = child, child = child * 2 + 1) {
//		if (child + 1 < N && heap[child + 1] > heap[child]) {
//			child++;
//		}
//		if (heap[child] > temp) {
//			heap[parent] = heap[child];
//		}
//		else {
//			break;
//		}
//	}
//	heap[parent] = temp;
//
//	return ret;
//}
//template<typename T>
//T Delete_min(T* heap, int& N) {
//	T ret = heap[0];
//	heap[0] = heap[--N];
//
//	int temp = heap[0];
//	int parent = 0;
//	int child;
//	for (child = parent * 2 + 1; child < N; parent = child, child = child * 2 + 1) {
//		if (child + 1 < N && heap[child + 1] < heap[child]) {
//			child++;
//		}
//		if (heap[child] < temp) {
//			heap[parent] = heap[child];
//		}
//		else {
//			break;
//		}
//	}
//	heap[parent] = temp;
//
//	return ret;
//}
//
//
//template<typename T>
//void BuildHeap_max(T* heap, int N) {
//	
//	int last_leaf = N - 1;
//	int last_UNleaf;
//	int parent, child, temp;
//	for (last_UNleaf = (last_leaf - 1) / 2; last_UNleaf >= 0;last_UNleaf--) {
//		/*temp = heap[last_UNleaf];
//		for (parent = last_UNleaf,child=parent*2+1 ; child < N; parent = child, child = child * 2 + 1) {
//			if (child + 1 < N && heap[child + 1] > heap[child]) {
//				child++;
//			}
//			if (heap[child] > temp) {
//				heap[parent] = heap[child];
//			}
//			else {
//				break;
//			}
//		}
//		heap[parent] = temp;*/
//		AdjustDown_max(heap, N, last_UNleaf);
//	}
//
//
//}
//
//template<typename T>
//void HeapSort(T* arr,int N) {
//	//int heapsize = 1;
//	//for (int i = 1; i < N; i++) {
//	//	Insert_max(arr, heapsize,arr[i]);
//	//	//Insert_min(arr, heapsize, arr[i]);
//	//}
//	BuildHeap_max(arr, N);
//	int heapsize = N;
//
//	for (int i = 0; i < heapsize; i++) {
//		int ret = Delete_max(arr, N);
//		//int ret = Delete_min(arr, N);
//		arr[N] = ret;
//	}
//
//	//int x = 0;
//}



template<typename iterator, class compare>
void filter_up(iterator arr, size_t N, size_t pos, compare cmp) {
    auto temp = arr[pos];

    size_t parent, child;
    for (child = pos, parent = (pos - 1) / 2; child != 0 && cmp(arr[parent] , temp); child = parent, parent = (parent - 1) / 2) {
        arr[child] = arr[parent];
    }
    arr[child] = temp;
}

template<typename iterator, class compare>
void filter_down(iterator arr, size_t N,size_t pos, compare cmp) {
    auto temp = arr[pos];

    size_t child, parent;
    for (parent = pos, child = pos * 2 + 1; child < N; parent=child,child= child *2+1) {
        if (child < N - 1 && cmp(arr[child ] , arr[child+1])) {
            child++;
        }
        if (arr[child] == temp || cmp(arr[child],temp)) {
            break;
        }
        arr[parent] = arr[child];
    }
    arr[parent] = temp;
}

template<typename iterator, class compare>
void delete_max(iterator first, iterator& last, compare cmp) {
    //assert
    if (last == first )return;
    swap(*first, *(--last));
    filter_down(first, last - first  , 0, cmp);
}

template<typename iterator, class compare>
void build_heap(iterator arr, size_t N, compare cmp) {
    /*for (size_t pos = 1; pos <N; pos++) {
        filter_up(arr, N, pos, cmp);//从上往下进行上滤，效率低
    }*/
    for (size_t pos = (N - 1) / 2; pos != -1; pos--) {
        filter_down(arr, N, pos, cmp);//从下往上下滤，效率高
    }
}

template<typename iterator ,class compare>
void HeapSort(iterator first, iterator last, compare cmp) {
    iterator arr = first;
    size_t size = last - first;
    

    build_heap(arr, size, cmp);
    size_t n = size;
    while (n--) {
        delete_max(first , last , cmp);
    }

}




int main()
{
    int arr[] = { 857,521,250,911,361,438,985,211,110,666,369 };
    size_t  len = sizeof(arr) / sizeof(int);

    vector<int> v;
    v.reserve(len);
    for (int i = 0; i < len; i++) {
        v.push_back(arr[i]);
    }
    print_container(v);

    HeapSort(v.begin(), v.end(), xdh::less<int>());
    //delete_max(v.begin(), len, xdh::less<int>());
    print_container(v);


	return 0;
}














