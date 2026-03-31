#include<iostream>
using namespace std;
#include"queue.h"

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


    //xdh::priority_queue<int> heap(v.begin(), v.end());

    xdh::priority_queue<int>::sort(v, less<int>());
    print_container(v);




    return 0;
}