#pragma once
#include<iostream>
#include<assert.h>
#include<vector>
#include"iterator.h"
using namespace std;


namespace xdh {

	template<typename T>
	class list;//先声明，防止list_iterator找不到list模板

	template<typename T>
	struct list_node {
		T data;
		list_node* prev;
		list_node* next;

		list_node(const T& x = T(), list_node* PREV = nullptr, list_node* NEXT = nullptr) :data(x), prev(PREV), next(NEXT) {}
	};
	


	template<typename T, class ref, class ptr>
	struct list_iterator {
		typedef list_iterator<T, ref, ptr> self;
		typedef list_node<T> node;

		list_iterator(node* node = nullptr) :_pnode(node) {}
		template<class IT>
		list_iterator(const IT& it) :_pnode(it._pnode) {}//支持iterator类型转换const_iterator
		                                                //支持隐式类型转换，对应的单参数operator=不用写了

		self& operator++() {
			_pnode = _pnode->next;
			return *this;
		}
		self operator++(int) {
			self temp = _pnode;
			_pnode = _pnode->next;
			return temp;
		}
		self& operator--() {
			_pnode = _pnode->prev;
			return *this;
		}
		self operator--(int) {
			self temp = _pnode;
			_pnode = _pnode->prev;
			return temp;
		}

		ref operator*() {
			return _pnode->data;
		}

		ptr operator->() {//返回ptr指针
			return &(operator*());//假设node的data是结构体，有int a1，int a2
		}//it->a1 本质上是 it.operator->() -> a1。所以要返回ptr，只不过编译器为了好看特殊处理了。只用一个 ->

		bool operator==(const self& it) {
			return _pnode == it._pnode;
		}
		bool operator!=(const self& it) {
			return _pnode != it._pnode;
		}

		node* _pnode;
	};



	template<typename T>
	void swap(list<T>& L1, list<T>& L2) {
		L1.swap(L2);
	}

	template<typename T>
	class list {
	public:
		typedef list_node<T> node;
		typedef list_iterator<T, T&, T*> iterator;
		typedef list_iterator<T, const T&, const T*> const_iterator;
		typedef reverseiterator<iterator, T&, T*> reverse_iterator;
		typedef reverseiterator<iterator, const T&, const T*> const_reverse_iterator;


		list() {
			empty_initialize();
		}
		list(const list& L) {
			empty_initialize();
			insert(end(), L.begin(), L.end());
		}
		list(initializer_list<T> L) {//就是用一个数组把{ }内存起来，提供begin和end指针。
			empty_initialize();
			insert(end(), L.begin(), L.end());//单参数构造函数支持隐式类型转换，
		}                                    //支持 list<int> L = {1,2,3,4,5} 的写法

		list& operator=(const list& L) {
			if (L._head != _head) {
				list temp = L;
				swap(*this, temp);
			}
			return *this;
		}

		////////////////////////////////////////////////增删查改///////////////////////////////////////////////////////
		T& front() {
			assert(_size != 0);
			return _head->next->data;
		}
		T& back() {
			assert(_size != 0);
			return _head->prev->data;
		}
		template <class InputIterator>
		void assign(InputIterator first, InputIterator last) {
			clear();
			insert(end(), first, last);
		}
		void assign(size_t n, const T& val) {
			clear();
			insert(end(), n, val);
		}
		void assign(initializer_list<T> L) {
			clear();
			insert(end(), L.begin(), L.end());
		}


		void resize(size_t n) {
			if (n <= _size) {
				iterator del_begin = end();
				size_t cnt = _size - n;
				while (cnt--) {
					del_begin--;
				}
				erase(del_begin, end());
			}
			else {
				insert(end(), n - _size, T());
			}
		}

		void clear() {
			erase(begin(), end());
		}

		iterator insert(iterator pos, const T& x) {
			return insert(pos, 1, x);
		}
		iterator insert(iterator pos, int n, const T& x) {
			assert(n >= 0);
			return insert(pos, (size_t)n, x);
		}
		iterator insert(iterator pos, size_t n, const T& x) {
			node* insert_pos = pos._pnode;
			node* prev = insert_pos->prev;
			node* temp; _size += n;
			while (n--) {
				temp = new node(x);
				link_node(insert_pos->prev, temp);
				link_node(temp, insert_pos);
			}
			return prev->next;
		}
		template<class InputIterator>
		iterator insert(iterator pos, InputIterator first, InputIterator last) {
			node* insert_pos = pos._pnode;
			node* prev = insert_pos->prev;
			node* temp;
			size_t cnt = 0;
			while (first != last) {
				temp = new node(*first);
				link_node(insert_pos->prev, temp);
				link_node(temp, insert_pos);
				first++; cnt++;
			}
			_size += cnt;
			return prev->next;
		}

		template<typename compare>
		iterator insert_ordered(const T& x ,compare) {
			iterator it = begin();
			while (it!= end() && *it <= x) {
				++it;
			}
			insert(it, x);
			return --it;
		}

		iterator erase(iterator pos) {
			iterator end = pos;
			return erase(pos, ++end);
		}
		iterator erase(iterator first, iterator last) {
			if (first == last)return last;
			node* left = first._pnode->prev;
			node* right = last._pnode;

			size_t cnt = 0;
			node* p = first._pnode;
			node* q = p->next;
			while (p != last._pnode) {
				assert(p != _head);
				delete p;  cnt++;
				p = q;
				q = q->next;
			}
			_size -= cnt;
			link_node(left, right);

			return right;
		}

		void push_back(const T& x) {
			insert(end(), x);
		}
		void push_front(const T& x) {
			insert(begin(), x);
		}
		void pop_back(const T& x) {
			erase(--end());
		}
		void pop_front(const T& x) {
			erase(begin());
		}
		void splice(const_iterator position, list& list) {
			splice(position, list, list.cbegin(), list.cend());
		}
		void splice(const_iterator position, list& list, const_iterator i) {
			auto j = i; ++j;
			splice(position, list, i, j);
		}
		void splice(const_iterator position, list& list, const_iterator first, const_iterator last) {
			assert(first != last && first!=position);
			const_iterator pre = position; --pre;
			size_t cnt = 0;
			for (const_iterator it = first; it != last; ++it) {
				assert(it._pnode != list.cend()._pnode);
				cnt++;
			}

			const_iterator L = first--;
			const_iterator R = last; --R;
			link_node(first, last);

			link_node(pre, L);
			link_node(R, position);

			_size += cnt;
		}
		void remove(const T& val) {
			iterator it = begin();
			while (it != end()) {
				if (*it == val) {
					it = erase(it);
				}
				else {
					++it;
				}
			}
		}

		template <class Predicate>
		void remove_if(Predicate pred) {
			iterator it = begin();
			while (it != end()) {
				if (pred(*it)) {
					it = erase(it);
				}
				else {
					++it;
				}
			}
		}

		template<class compare>
		void sort(compare cmp) {
			iterator be = begin();
			mergesort(be, _size, cmp);
		}
		                        //0                   5                   10  11
		template<class compare>//857,521,250,911,361,438,985,211,110,666,369
		void mergesort(iterator& pos ,size_t N ,compare cmp) {//也必须传引用
			if (N < 2)return;
			iterator mid = pos;
			size_t left = N / 2;
			size_t right = N - left;
			for (size_t i = 0; i < left; i++) {
				++mid;
			}
			
			mergesort(pos,left, cmp);
			mergesort(mid, right, cmp);
			merge(pos, left, *this, mid, right, cmp);//指针传引用,保证merge后位序不变
			//由于指针特殊性，在merge后mid指针的位序的可能不是之前的mid的位序
			//print_container(*this);
		}

		template <class Compare>
		void merge(list& x, Compare cmp) {
			merge(begin(), _size, x, x.begin(), x._size, cmp);
		}

		template <class Compare>//merge后为保持位序不变,p指向合并链表第1个元素，q指向第N+1个
		void merge(iterator& P, size_t N,list&  L, iterator& Q, size_t M, Compare cmp) {
			iterator p = P, q = Q;

			size_t n = 0 ,m = 0;//_head  p          q  
			iterator pren = p;  --pren;//2 4 6 8 10 1 3 5 7 9 
			iterator prem = q;  --prem;//1 3 5 7 9  2 4 6 8 10

			list temp;
			iterator last = temp._head;
			while (n != N && m != M) {
				assert(p != end() && q != L.end());
				assert(p != Q && q != P);//防止同一链表合并时前后区间重合
				if ( cmp(*p,*q) ) {//如果区间真的重合，无论P或Q区间,在对应的p、q指针之后的节点的next是没有被修改的。特别的,
					link_node(last, p);//对于区间交汇处节点的next必能到达下一个区间。所以无论P、Q哪个是前一个区间，
					++n; ++p;         //其对应指针都能根据p != Q && q != P条件判断是否重合
				}
				else {
					link_node(last, q);
					++m; ++q;
				}
				++last;
			}
			while (n != N) {
				assert(p != end());
				link_node(last, p);
				++n; ++p;
				++last;
			}
			while (m != M) {
				assert(q != L.end());
				link_node(last, q);
				++m; ++q;
				++last;
			}
			link_node(last, temp._head);

			//排除不同链表和同链表相隔
			if (*this != L ||(p!=Q && q!=P)) {
				link_node(prem, q);
				link_node(pren, p);
				splice(pren, temp);
			}
			else {//只剩下相接情况
				if (p == Q) {//P区间在Q区间前面
					link_node(pren, q);
					splice(++pren, temp);
				}
				if (q == P) {//Q区间在P区间前面
					link_node(prem, p);
					splice(++prem, temp);
				}
			}

			P = *P < *Q ? P : Q;
			Q = P;
			for (size_t i = 0; i < N; i++) {
				++Q;
			}

			_size += N;
			L._size -= M;
		}

		void unique() {
			iterator mom = begin();
			iterator son;

			for (son = mom; son != end(); son++) {
				if (*son != *mom) {
					mom = erase(++mom, son);
				}
			}
			 
			auto& temp = *(mom++);//最后可能有遗留
			if (temp == *mom)erase(mom, son);
		}
		void reverse() {
			node* pre = _head;
			node* reverse = begin()._pnode;
			node* next = reverse;

			while (reverse!=_head) {
				next = reverse->next;
				link_node(reverse ,pre);//注意有先后次序

				pre = reverse; 
				reverse = next;
				next = next->next;
			}
			link_node(_head, pre);
		}
		////////////////////////////////////////////////辅助函数///////////////////////////////////////////////////////
		iterator begin() {
			return _head->next;
		}
		iterator end() {
			return _head;
		}
		iterator begin() const {
			return _head->next;
		}
		iterator end() const {
			return _head;
		}
		const_iterator cbegin() {
			return _head->next;
		}
		const_iterator cend() {
			return _head;
		}
		reverse_iterator rbegin() {
			return end();
		}
		reverse_iterator rend() {
			return begin();
		}
		const_reverse_iterator crbegin()const {
			return end();
		}
		const_reverse_iterator crend() const {
			return begin();
		}

		void swap(list& L) {
			std::swap(_head, L._head);
			std::swap(_size, L._size);
		}

		size_t size() {
			return _size;
		}
		bool empty() {
			return _size == 0;
		}

		bool operator==(const list& L) {
			return _head == L._head;
		}
		bool operator!=(const list& L) {
			return _head != L._head;
		}
	private:
		void link_node(node* first, node* second) {//注意有先后次序
			first->next = second;	second->prev = first;
		}
		void link_node(iterator first, iterator second) {
			link_node(first._pnode, second._pnode);
		}
		void link_node(const_iterator first, const_iterator second) {
			link_node(first._pnode, second._pnode);
		}
		void empty_initialize() {
			_head = new node;
			_head->prev = _head->next = _head;
			_size = 0;
		}
	private:
		node* _head;
		size_t _size;
	};






	template<class container>
	void print_container(const container& v) {
		for (auto& e : v) {
			cout << e << ' ';
		}
		cout << endl;
	}


	void test01() {
		xdh::list<int> L1;
		L1.push_back(1);
		L1.push_back(2);
		L1.push_back(3);
		L1.push_back(4);
		L1.push_back(5);

		print_container(L1);
		L1.clear();
		print_container(L1);
	}
	void test02()
	{
		xdh::list<int> L1;
		std::vector<int> v = { 1,2,3,4,5 };

		list<int>::iterator it = L1.insert(L1.begin(), v.begin(), v.end());
		print_container(L1);
		cout << "size:" << L1.size() << endl;
		it = L1.insert(L1.begin(), 1, 10);
		print_container(L1);
		cout << "size:" << L1.size() << endl;

		it++;
		list<int>::iterator t = it;
		t++; t++;
		it = L1.erase(it, ++t);
		print_container(L1);
		cout << *it << endl;
		cout << "size:" << L1.size() << endl;

		it = L1.erase(it);
		print_container(L1);
		cout << *it << endl;

		cout << "size:" << L1.size() << endl;
	}

	void test03()
	{
		xdh::list<int> L1;
		std::vector<int> v = { 1,2,3,4,5 };
		list<int>::iterator it = L1.insert(L1.begin(), v.begin(), v.end());
		print_container(L1);

		it = L1.insert(L1.end(), v.begin(), v.end());
		print_container(L1);
		cout << L1.size();
	}
	void test04()
	{
		xdh::list<int> L1;
		std::vector<int> v = { 1,2,3,4,5 };
		list<int>::iterator it = L1.insert(L1.begin(), v.begin(), v.end());
		print_container(L1);

		L1.push_back(0);
		L1.push_front(0);
		print_container(L1);
		L1.pop_back(0);
		L1.pop_front(0);
		print_container(L1);

		L1.resize(3);
		print_container(L1);
		cout << "size:" << L1.size() << endl;
		L1.resize(5);
		print_container(L1);
		cout << "size:" << L1.size() << endl;

		L1.clear();
		print_container(L1);
		cout << "size:" << L1.size() << endl;
	}
	void test05() {
		xdh::list<int> L1;
		std::vector<int> v = { 1,2,3,4,5 };
		list<int>::iterator it = L1.insert(L1.begin(), v.begin(), v.end());
		print_container(L1);

		std::vector<int> v2 = { 5,4,3,2,1 };
		xdh::list<int> L2 = L1;
		print_container(L2);

		L2.assign(v2.begin(), v2.end());
		print_container(L2);


	}

	struct A {
		int a;
		int b;
	};

	void test06() {
		xdh::list<int> L1 = { 1,2,3,4,5 };//
		print_container(L1);

		auto it = L1.rbegin();
		while (it != L1.rend()) {
			cout << *it << ' ';
			(*it)++;
			it++;
		}
		cout << endl;

		print_container(L1);

		xdh::list<A> L2 = { {1,2},{2,3 } };
		auto rit = L2.rbegin();
		cout << rit->b;

	}

	void test07() {
		xdh::list<int> L = { 1,2,3,4,5,6 };
		xdh::list<int> R = L;

		auto it = L.cbegin(); ++it; ++it; ++it;
		auto ti = it; ++ti; ++ti; ++ti;
		L.splice(L.cbegin(), L, it, ti);

		print_container(L);
		L.splice(L.cbegin(), L, --L.cend());
		print_container(L);
		print_container(R);
		L.splice(L.cbegin(), R);
		print_container(L);
		print_container(R);

	}

	void test08() {
		xdh::list<int> N = { 7,7,6,6,5,4,3,2,1 };
		N.reverse();
		print_container(N);
		N.unique();
		print_container(N);

		cout << endl;
		
		xdh::list<int> M = { 1,1,2,2,2,3,3,3,4,5,6,6 };
		M.reverse();
		print_container(M);
		M.unique();
		print_container(M);

		cout << endl;

		N.splice(N.cend(), M);
		print_container(N);
		print_container(M);

		N.reverse();
		xdh::list<int>::iterator it = N.begin();
		for( ;*it!=7;it++){}
		it++;
		N.remove(7);
		print_container(N);
		N.insert(it, 2,7);
		print_container(N);

		it--;
		xdh::list<int>::const_iterator ti = it;
		xdh::list<int>::const_iterator itti;
		itti = it;
		xdh::list<int> T = { 8,9,8 };
		N.splice(itti, T);
		print_container(N);
		cout << N.size() << endl;

		xdh::list<int>::reverse_iterator rit = N.rbegin();
		xdh::list<int>::const_reverse_iterator crit = rit;
		xdh::list<int>::const_reverse_iterator ccrrit;
		ccrrit = rit;
		while (crit != N.crend()) {
			cout << *crit << ' ';
			++crit;
		}
		cout << endl;
	}


	template<typename T>
	struct jishu {
		bool operator()(const T& x) {
			return x % 2 == 1;
		}
	};
	template<typename T>
	struct oushu {
		bool operator()(const T& x) {
			return x % 2 == 0;
		}
	};

	void test09() {
		xdh::list<int> L = { 1,2,4,5,6,7,8,9 };
		
		auto it = L.insert_ordered(3, less<int>());
		print_container(L);
		cout << *it << endl;

		it = L.insert_ordered(10, less<int>());
		print_container(L);
		cout << *it;
	}
	void test10() {
		xdh::list<int> L = { 1,2,3,4,5,6,7,8,9,10 };
		xdh::list<int> R = L;

		L.remove_if(oushu<int>());
		print_container(L);
		R.remove_if(jishu<int>());
		print_container(R);

		cout << endl;

		/*L.merge(L.begin(), L.size(), R, R.begin(), R.size(),less<int>());
		print_container(L);
		print_container(R);*/

		size_t n = L.size();
		size_t m = R.size();
		xdh::list<int>::iterator it = L.end(); --it;
		L.splice(L.end(),R);
		print_container(L);
		cout << *it << endl;

		auto be = L.begin();
		L.splice(L.cbegin(), L,++it, L.cend());
		print_container(L);
		L.merge(be , n, L, it, m,less<int>());
		print_container(L);
		cout << *be << ' ' << *it << endl;

	}
	void testX() {
		xdh::list<int> L = { 857,521,250,911,361,438,985,211,110,666,369 };

		/*xdh::list<int>::iterator a = L.begin();
		xdh::list<int>::iterator b = a; ++b;
		L.merge(a, 1, L, b, 1, less<int>());
		print_container(L);*/
		L.sort(less<int>());
		print_container(L);

	}
}