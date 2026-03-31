#pragma once
#include<iostream>
using namespace std;
#include<vector>
#include<list>
#include"deque.h"

namespace xdh {

    template<typename T, class container = std::list<T>>
    class queue {
        queue() = default;

        size_t size() {
            return _quen.size();
        }
        bool empty() {
            _quen.empty();
        }

        void push(const T& x) {
            _quen.push_back();
        }
        void pop() {
            _quen.pop_front();
        }

        T& front() {
            return _quen.front();
        }

        T& back() {
            return _quen.back();
        }

        void swap(queue& quen) {
            std::swap(_quen, quen._quen);
        }

    private:
        container _quen;
    };




    template <typename T, class compare = std::less<T>, class container = std::vector<T> >
    class priority_queue {
    private:
        template<typename iterator, class compare>
        static void filter_up(iterator arr, size_t N, size_t pos, compare cmp) {
            auto temp = arr[pos];

            size_t parent, child;
            for (child = pos, parent = (pos - 1) / 2; child != 0 && cmp(arr[parent], temp); child = parent, parent = (parent - 1) / 2) {
                arr[child] = arr[parent];
            }
            arr[child] = temp;
        }

        template<typename iterator, class compare>
        static void filter_down(iterator arr, size_t N, size_t pos, compare cmp) {
            auto temp = arr[pos];

            size_t child, parent;
            for (parent = pos, child = pos * 2 + 1; child < N; parent = child, child = child * 2 + 1) {
                if (child < N - 1 && cmp(arr[child], arr[child + 1])) {
                    child++;
                }
                if (arr[child] == temp || cmp(arr[child], temp)) {
                    break;
                }
                arr[parent] = arr[child];
            }
            arr[parent] = temp;
        }
        template<typename iterator, class compare>
        static void build_heap(iterator arr, size_t N, compare cmp) {
            /*for (size_t pos = 1; pos <N; pos++) {
                filter_up(arr, N, pos, cmp);//从上往下进行上滤，效率低
            }*/
            for (size_t pos = (N - 1) / 2; pos != -1; pos--) {
                filter_down(arr, N, pos, cmp);//从下往上下滤，效率高
            }
        }
    public:
        priority_queue(compare cmp = std::less<T>()) :cmp(cmp) {};

        template<class iterator>
        priority_queue(iterator first, iterator last, compare cmp = std::less<T>()) :cmp(cmp) {
            while (first != last) {
                heap.push_back(data[*first]);
            }
            build_heap(heap.begin(), heap.size(), cmp);
        }

        void push(const T& e) {
            heap.push_back(e);
            filter_up(heap.begin(), heap.size(), heap.size() - 1, cmp);
        }
        void pop() {
            if (heap.size() == 0)return;
            std::swap(heap[0], heap[heap.size() - 1]);
            heap.pop_back();
            filter_down(heap.begin(), heap.size(), 0, cmp);
        }
        const T& top() const {
            return heap[0];
        }
        T& top() {
            return heap[0];
        }
        bool empty()const {
            return heap.empty();
        }

        size_t size()const {
            return heap.size();
        }

        void swap(const priority_queue& queue) {
            std::swap(heap, queue.heap);
            std::swap(cmp, queue.cmp);
        }

        static void sort(container& arr, compare cmp) {
            build_heap(arr.begin(), arr.size(), cmp);

            size_t N = arr.size();
            while (N) {
                std::swap(arr[0], arr[N - 1]);
                filter_down(arr.begin(), N - 1, 0, cmp);
                N--;
            }
        }

    private:
        container heap;
        compare cmp;
    };

    template <typename T >
    void swap(const queue<T>& q1, const queue<T>& q2) {
        q1.swap(q2);
    }

    template <typename T >
    void swap(const priority_queue<T>& h1, const priority_queue<T>& h2) {
        h1.swap(h2);
    }


}