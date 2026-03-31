#pragma once
#include"RBTree.h"
#include<map>
#include<vector>

namespace STL {

	template<class K, class V, class compare=less<K>>
	class map {
	public:
		typedef pair<const K, V> T;

		struct KeyOfData_map {
			const K& operator()(const T& data) {
				return data.first;
			}
		};
		struct print_KV {
			void operator()(const T& data) {
				cout << data.first << ":" << data.second << " ";
			}
		};

		typedef RBTree<K, T, KeyOfData_map, compare> BBST;//banlanced binary search tree
		typedef typename BBST::Iterator iterator;
		typedef typename BBST::ConstIterator const_iterator;

		

	public:

		map() {
			_tree = new BBST;
		}

		map(const map& map) {
			_tree = new BBST(*map._tree);
		}

		map& operator=(map map) {
			swap(map);
		}
		
		~map() {
			delete _tree;
		}

		iterator begin() {
			return _tree->begin();
		}

		iterator end() {
			return _tree->end();
		}

		const_iterator begin() const{
			return _tree->cbegin();
		}

		const_iterator end() const{
			return _tree->cend();
		}

		const_iterator cbegin() const {
			return _tree->cbegin();
		}

		const_iterator cend() const {
			return _tree->cend();
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

		void swap(map& m) {
			std::swap(_tree, m._tree);
		}

		void clear() {
			_tree->clear();
		}

		V& operator [](const K& key) {
			return (insert(T(key, V())).first)->second;
		}


	private:
		/*void show() {
			_tree->Inorder_Traverse(_tree->_root ,print_KV() );
		}*/

	private:
		 BBST* _tree;
	};

	template<class K, class V, class compare>
	void swap(map<K, V, compare>& map1, map<K, V, compare>& map2) {
		map1.swap(map2);
	}
	





	void test01_m() {
		map<int, char, less<int>> m;

		m.insert(pair<int, char>(5, '5'));
		m.insert(pair<int, char>(3, '3'));
		m.insert(pair<int, char>(4, '4'));
		m.insert(pair<int, char>(2, '2'));
		m.insert(pair<int, char>(1, '1'));
		m.insert(pair<int, char>(8, '8'));
		m.insert(pair<int, char>(6, '6'));
		m.insert(pair<int, char>(7, '7'));
		m.insert(pair<int, char>(9, '9'));
		//m.show();
		//cout << endl;


		//因为end()返回的是临时变量是const的所以!=的参数必须要是const的引用
		map<int, char, less<int>>::iterator it = m.begin();
		while (it != m.end() ) {
			cout << it->first << ':' << it->second << ' ';
			++it;
		}
		cout << endl;

		

		auto copy(m);
		copy.insert(pair<int, char>(0, '0'));
		map<int, char, less<int>>::iterator copy_it = copy.begin();
		while (copy_it != copy.end()) {
			cout << copy_it->first << ':' << copy_it->second << ' ';
			++copy_it;
		}

		cout << endl<< copy[4] << endl;

		copy[10] = 'A';
		cout << copy[10] << endl;
		copy.insert({ 11,'B' });
		copy.insert({ 6,'9' });
		cout << copy[6];

	}


	void test02_m() {
		map<int, string, less<int>> m;

		m.insert({ 1,"A" });
		m.insert({ 2,"2" });
		auto it = m.begin();

		cout << it->first << ":" << it->second; cout << endl;

		//it->first = 11;
		it->second = "22";
		cout << it->first << ":" << it->second; cout<< endl;

		const auto m1(m);

		auto it1 = m1.begin();
		cout << it->first << ":" << it->second;


	}


	void test_map() {
		srand(time(NULL));
		const int N = 1000000;


		map<int, int> m;
		std::map<int, int> m1;
		vector<int> v;
		v.reserve(N);
		


		for (int i = 0; i < N; i++) {
			int ins = rand() + i;
			v.push_back(ins);
		}


		clock_t ins_begin1 = clock();
		for (auto e : v) {
			m.insert({ e,e });
		}
		clock_t ins_end1 = clock();

		clock_t ins_begin2 = clock();
		for (auto e : v) {
			m1.insert({ e,e });
		}
		clock_t ins_end2 = clock();

		cout << "mymap  insert:" << ins_end1 - ins_begin1 << endl;
		cout << "stdmap insert:" << ins_end2 - ins_begin2 << endl;

		size_t cnt1 = 0;
		size_t cnt2 = 0;
		clock_t find_begin1 = clock();
		for (auto e : v) {
			m.find(e);
		}
		clock_t find_end1 = clock();

		clock_t find_begin2 = clock();
		for (auto e : v) {
			(void)m1.find(e);
		}
		clock_t find_end2 = clock();

		cnt1 = m.size();
		cnt2 = m1.size();
		//for (auto e : v) {
		//	size_t n1 = m.count(e);
		//	size_t n2 = m1.count(e);
		//	cnt1 += n1;
		//	cnt2 += n2;
		//	//if (n1 != n2)cout << "error ————> data:" << e << endl;
		//}

		cout << "mymap  find:" << find_end1 - find_begin1 << endl;
		cout << "stdmap find:" << find_end2 - find_begin2 << endl;
		cout << "mymap  cnt:" << cnt1 << endl;
		cout << "stdmap cnt:" << cnt2 << endl;



		clock_t erse_begin1 = clock();
		for (auto e : v) {
			m.erase(e);
		}
		clock_t erse_end1 = clock();

		clock_t erse_begin2 = clock();
		for (auto e : v) {
			m1.erase(e);
		}
		clock_t erse_end2 = clock();

		cout << "mymap  erase:" << erse_end1 - erse_begin1 << endl;
		cout << "stdmap erase:" << erse_end2 - erse_begin2 << endl;


	}


}






