#pragma once
#include<iostream>
#include<algorithm>
#include<assert.h>
#include<stack>
using namespace std;

namespace xdh {

	template<typename T>
	class vector {
	public:
		typedef T* iterator;
		typedef const T* const_iterator;
		typedef size_t Rank;
		//////////////////////////////////////////////////构造函数
		vector() = default;
		vector(int sz, const T& val = T())
		{ //通过函数重载，让第一个元素类型就匹配上，避免两个参数一样时调用迭代器初始化函数
			if (sz > 0) {
				reserve(sz);
				_finish = _start + sz;
				for (auto& e : *this) {
					e = val;
				}
			}
		}
		vector(size_t sz, const T& val = T()) {
			reserve(sz);
			_finish = _start + sz;
			for (auto& e : *this) {
				e = val;
			}
		}
		
		vector(const vector<T>& v) {
			reserve(v.capacity());
			for (int i = 0; i < v.size(); i++) {
				push_back(v[i]);
			}
		}
		template<typename InputIterator>//因为这个模板两个参数一样的，所以初始化的时候如果给了两个整数，不会调用默认构造函数
		vector(InputIterator begin, InputIterator end) {//会调用该函数，把元素个数和元素值当作地址就会出错。
			while (begin != end) {
				push_back(*begin++);
			}

		}

		~vector()
		{
			delete[] _start;
			_start = nullptr;
			_finish = nullptr;
			_end_of_storage = nullptr;
		}
		vector& operator=(vector<T> v) {//现代写法:用构造的v(要用传值传递)与*this交换
			swap(v);
			return *this;
		}
		//////////////////////////////////////////////////辅助函数/////////////////////////////////////////////////////////////////
		iterator begin() {
			return _start;
		}
		iterator end() {
			return _finish;
		}
		const_iterator begin()const {
			return _start;
		}
		const_iterator end()const {
			return _finish;
		}
		const_iterator cbegin()const {
			return _start;
		}
		const_iterator cend()const {
			return _finish;
		}
		size_t size()const {
			return _finish - _start;
		}
		size_t capacity() const{
			return _end_of_storage - _start;
		}
		bool empty() {
			return size() == 0;
		}
		
		void resize(size_t n, const T& val = T()) {
			if (n <= size()) {
				_finish = _start + n;
			}
			else {
				reserve(n);
				while (_finish != _start + n) {
					*_finish = val;
					_finish++;
				}
			}
		}

		
		void change_cap(size_t n);
		void shrink(size_t n= -1) {
			if (n == -1)n = size();
			if (n < capacity()) {
				change_cap(n);
			}
		}
		void reserve(size_t n) {
			if (n > capacity()) {
				change_cap(n);
			}
		}

		template<typename T>
		void swap(vector<T>& v) {
			std::swap(_start, v._start);
			std::swap(_finish, v._finish);
			std::swap(_end_of_storage, v._end_of_storage);
		}

		/////////////////////////////////////////////////增删改查//////////////////////////////////////////////////////////////////
		T& operator [](Rank i) {
			return _start[i];
		}
		const T& operator [](Rank i)const {
			return _start[i];
		}
		T& front() {
			return *(_start);
		}
		T& back() {
			return *(_finish - 1);
		}
		const T& front() const{
			return *(_start);
		}
		const T& back() const{
			return *(_finish - 1);
		}
		void clear() {
			_finish = _start;
		}
		void push_back(const T& val) {
			if (_finish == _end_of_storage) {
				reserve(capacity() == 0 ? 4 : capacity() * 2);
			}
			*_finish++ = val;
		}
		void pop_back() {
			assert(!empty());
			_finish--;
		}
		template <class InputIterator>
		iterator insert(const_iterator pos, InputIterator first, InputIterator last);
		iterator insert(const_iterator pos, size_t n, const T& val);
		iterator insert(const_iterator pos, const T& val) {
			return insert(pos, 1, val);
		}
		iterator insert(const_iterator pos, int n, const T& val) {
			return insert(pos, (size_t)n, val);//如果用户传入n为int型，正好T也是int型，那么模板insert两个参数一样更符合，
		}                                      //所以会进入模板insert，把int当作迭代器解引用，就会报错。

		iterator erase(const_iterator first, const_iterator last);
		iterator erase(const_iterator pos, size_t n = 1) {
			return erase(pos, pos + n);
		}
		
		

		

	private:
		iterator _start = nullptr;
		iterator _finish = nullptr;
		iterator _end_of_storage = nullptr;
	};
	/////////////////////////////////////////////////end of class//////////////////////////////////////////////////////

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
		
	

	template<typename T>
	void swap(vector<T>& v1, vector<T>& v2) {
		v1.swap(v2);
	}
	
	template<typename T>
	void vector<T>::change_cap(size_t n) {
		assert(n >= size());

		T* tmp = new T[n];
		size_t old_size = size();
		for (Rank i = 0; i < old_size; i++) {
			tmp[i] = _start[i];//不能用memcpy，是浅拷贝
		}
		delete[] _start;
		_start = tmp;//_start更新后原来的size()就失效了
		_finish = tmp + old_size;
		_end_of_storage = tmp + n;
	}

	template <typename T>
	template <class InputIterator>
	typename vector<T>::iterator vector<T>::insert(const_iterator pos, InputIterator first, InputIterator last) {
		assert(_start <= pos && pos <= _finish);
		size_t cnt = 0;
		InputIterator it = first;
		while (it != last) {
			cnt++;
			it++;
		}

		if (_finish + cnt > _end_of_storage) {
			size_t new_size = size() + cnt;
			size_t len = _finish - pos;
			reserve(new_size > 2 * capacity() ? new_size : 2 * capacity());
			pos = _finish - len;
		}

		iterator p;
		for (p = _finish - 1; p >= pos; p--) {
			*(p + cnt) = *p;
		}
		_finish += cnt;
		++p;

		while (first != last) {
			*p = *first;
			first++;
			p++;
		}
		return p - cnt;
	}

	template<typename T>
	typename vector<T>::iterator vector<T>::insert(const_iterator pos, size_t n, const T& val) {
		assert(_start <= pos && pos <= _finish);

		if (_finish + n > _end_of_storage) {
			size_t new_size = size() + n;
			size_t len = _finish - pos;
			reserve(new_size > 2 * capacity() ? new_size : 2 * capacity());
			pos = _finish - len;
		}
		iterator it;
		for (it = _finish - 1; it >= pos; it--) {
			*(it + n) = *it;
		}
		_finish += n;
		it += n;
		while (n--) {
			*(it--) = val;
		}
		return it + 1;
	}

	
	template<typename T>
	typename vector<T>::iterator vector<T>::erase(const_iterator first, const_iterator last) {
		assert(_start <= first && first < _finish);
		assert(_start <= last && first <= _finish);

		size_t ft = first - _start;
		size_t lt = last - _start;
		iterator p1 = _start + ft;
		iterator p2 = _start + lt;
		while (p2 != _finish) {
			*(p1++) = *(p2++);
		}
		_finish -= last - first;
		return _start + ft;
	}







	/// <summary>
	/// /////////////////////////////测试函数
	/// </summary>
	/// 
	
	template<typename container>
	void print_container(const container& c) {
		for (auto& e : c) {
			cout << e << " ";
		}
		cout << endl;
	}
	void test01() {
		vector<int> v(10, 2);
		print_container(v);
		v.reserve(20);
		for (auto& e : v) {
			cout << e << ' ';
		}
		cout << endl;
		v.shrink();
		print_container(v);

		cout << v.capacity();

	}
	void test02() {
		vector<int> v(10, 2);
		for (int i = 0; i < v.size(); i++) {
			v[i] = i;
		}
		print_container(v);

		cout << v.front() << ' ' << v.back();
	}
	void test03() {
		vector<int> v(10);
		for (int i = 0; i < v.size(); i++) {
			v[i] = i;
		}
		print_container(v);

		auto it = v.insert(v.begin() + 3, 3, 3);
		print_container(v);

		
		it = v.insert(v.end(), 3, 0);
		print_container(v);


	}
	void test04() {
		vector<int> v(10);
		for (int i = 0; i < v.size(); i++) {
			v[i] = i;
		}

		auto it = v.erase(v.end()-5,3);
		print_container(v);

		cout << *it;
	}
	void test05() {
		vector<int> v;
		for (int i = 0; i < 10; i++) {
			v.push_back(i);
		}
		print_container(v);

		vector<int> v1(v);
		print_container(v1);

		vector<int> v2;
		v2 = v1;
		print_container(v2);

		vector<int>v3(v2.begin()+1, v2.end()-1);
		print_container(v3);
	}
	void test06() {
		vector<int> v;
		for (int i = 0; i < 10; i++) {
			v.push_back(i);
		}
		print_container(v);

		vector<int> v1 = v;
		auto it = v1.begin()+1;
		auto ti = v1.insert(it,20,-1);
		print_container(v1);
		cout << *(it);

		//it = v1.erase(it, it + 4);
		print_container(v1);

	}
	void test07() {//   l  k                            r        
		int arr[] = { 857,521,250,911,361,438,985,211,110,666,369 };
		int arr2[] = { 250,521,101,99,250,250,985,250,110,666,369 };//增加重复元素

		int len = sizeof(arr) / sizeof(int);

		vector<int> v;
		v.reserve(len);
		for (int i = 0; i < len; i++) {
			v.push_back(arr2[i]);
		}
		print_container(v);


		//sort(v.begin(),v.end());
		print_container(v);
		/*auto pos = v.bin_search(v.begin(), v.end(), 361);
		cout << *pos;*/
		
	}

	void test08() {
		srand(time(NULL));
		const int N = 100000;

		vector<int> arr;
		arr.reserve(N);
		for (int i = 0; i < N; i++) {
			arr.push_back(rand() + i);
		}
		clock_t begin = clock();
		
		




	}
	
}






















