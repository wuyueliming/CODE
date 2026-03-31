#pragma once
#include"RBTree.h"
#include<set>
#include<vector>


namespace STL {

	template<class K,class compare=less<K>>
	class set {
	public:
		typedef const K T;
		typedef K V;

		struct KeyOfData_set {
			const K& operator()(const T& data) {
				return data;
			}
		};
		struct print_T {
			void operator()(const T& data) {
				cout << data<< " ";
			}
		};

		//key值不能修改，这里第二个参数应该是T。但由于treenode的copy函数不能const赋值所以。。。
		typedef RBTree<K,T, KeyOfData_set, compare> BBST;
		typedef typename BBST::Iterator iterator;
		typedef typename BBST::ConstIterator const_iterator;

	public:

		set() {
			_tree = new BBST;
		}

		set(const set& set) {
			_tree = new BBST(*set._tree);
		}

		set& operator=(set set) {
			swap(set);
		}

		~set() {
			delete _tree;
		}

		iterator begin() {
			return _tree->begin();
		}

		iterator end() {
			return _tree->end();
		}

		const_iterator begin() const {
			return _tree->begin();
		}

		const_iterator end() const {
			return _tree->end();
		}

		const_iterator cbegin() const {
			return _tree->begin();
		}

		const_iterator cend() const {
			return _tree->end();
		}

		pair<iterator, bool> insert(const T& data) {
			return _tree->insert(data);
		}

		size_t erase(const K& key) {
			return _tree->erase(key);
		}

		iterator find(const K& key) {
			return _tree->find(key);
		}

		size_t count(const K& key) {
			return _tree->count(key);
		}

		size_t size() {
			return _tree->size();
		}

		bool empty() {
			return _tree->empty();
		}

		void swap(set& s) {
			std::swap(_tree, s._tree);
		}

		void clear() {
			_tree->clear();
		}

		V& operator [](const K& key) {
			return *(insert(T(key, V())).first);
		}


	private:
		/*void show() {
			_tree->InorderTraverse < print_T>();
		}*/

	private:
		BBST* _tree;
	};

	template<class K ,class compare>
	void swap(set<K,compare>& set1, set<K, compare>& set2) {
		set1.swap(set2);
	}







	void testY1() {
		set<int> s;

		s.insert(1);
		s.insert(2);
		s.insert(3);
		s.insert(4);
		s.insert(5);
		s.insert(6);
		s.insert(7);

		auto it = s.begin();
		while (it != s.end()) {
			cout << *it << ' ';
			++it;
		}
		cout << endl;

	}

	void test_set() {
		srand(time(NULL));
		const int N = 1000000;


		set<int> s;
		std::set<int> s1;
		vector<int> v;
		v.reserve(N);
		


		for (int i = 0; i <= N; i++) {
			int ins = rand() + i;
			v.push_back(ins);
		}


		clock_t ins_begin1 = clock();
		for (auto e : v) {
			s.insert(e);
		}
		clock_t ins_end1 = clock();

		clock_t ins_begin2 = clock();
		for (auto e : v) {
			s1.insert(e);
		}
		clock_t ins_end2 = clock();

		cout << "myset  insert:" << ins_end1 - ins_begin1 << endl;
		cout << "stdset insert:" << ins_end2 - ins_begin2 << endl;

		size_t cnt1 = 0;
		size_t cnt2 = 0;
		clock_t find_begin1 = clock();
		for (auto e : v) {
			s.find(e);
		}
		clock_t find_end1 = clock();

		clock_t find_begin2 = clock();
		for (auto e : v) {
			(void)s1.find(e);
		}
		clock_t find_end2 = clock();

		
		cnt1 = s.size();
		cnt2 = s1.size();

		cout << "myset  find:" << find_end1 - find_begin1 << endl;
		cout << "stdset find:" << find_end2 - find_begin2 << endl;
		cout << "myset  cnt:" << cnt1 << endl;
		cout << "stdset cnt:" << cnt2 << endl;



		clock_t erse_begin1 = clock();
		for (auto e : v) {
			s.erase(e);
		}
		clock_t erse_end1 = clock();

		clock_t erse_begin2 = clock();
		for (auto e : v) {
			s1.erase(e);
		}
		clock_t erse_end2 = clock();

		cout << "myset  erase:" << erse_end1 - erse_begin1 << endl;
		cout << "stdset erase:" << erse_end2 - erse_begin2 << endl;


	}

}


