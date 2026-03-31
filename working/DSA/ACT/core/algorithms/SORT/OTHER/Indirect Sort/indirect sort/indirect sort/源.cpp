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
















//表排序:对指向数据的指针排序，这里使用特殊数据直接排
void TableSort(int* data, int* index, int N) {
    for (int i = 0; i < N; i++) {
        index[data[i]] = i;                                                                              
    }
}

void sort(int* data, int* index, int N) {
    for (int i = 0; i < N; i++) {
        if (index[i] == i) {
            continue;
        }
        else {
            int j = i;//i是这个环的起点
            int temp = data[j];
            while (index[j] != i) {
                data[j] = data[index[j]];
                int t = j;
                j = index[j];
                index[t] = t;
            }
            data[j] = temp;
            index[j] = j;
        }
    }
}

int main()
{
    /*int arr[] = { 857,521,250,911,361,438,985,211,110,666,369 };
    int len = sizeof(arr) / sizeof(int);

    vector<int> v;
    v.reserve(len);
    for (int i = 0; i < len; i++) {
        v.push_back(arr[i]);
    }
    print_container(v);*/

    //InsertSort(v.begin(), v.end(), xdh::less<int>());
    //print_container(v);
    //3,5,7,2,6,4,9,0,8,1
    int data[10] = { 3,5,7,2,6,4,9,0,8,1 };
    int index[10] = { 0 };//正常来说，得到index需要用排序算法对index中的指针进行排序
    TableSort(data, index, 10);//但是这里的数据是特殊的从0到9顺序的，所以由数字本身就能得出该数字在序列中的位置。
    sort(data, index, 10);

    for (int i = 0; i < 10; i++) {
        printf("%d ", data[i]);
    }
    printf("\nhello\n");
    return 0;
}
