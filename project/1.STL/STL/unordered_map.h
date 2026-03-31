#pragma once
#include"HashTable.h"
#include<map>
#include<vector>

namespace STL {

	template<class K, class V, class Code = default_Code<K>, class Equal = default_equal<K>>
	class unordered_map {
	public:
		typedef pair<const K, V> T;

		struct KeyOfData_map {
			const K& operator()(const T& data) {
				return data.first;
			}
		};

		typedef HashTable<K, T, KeyOfData_map, Code, Equal> HT;
		typedef typename HT::Iterator iterator;
		typedef typename HT::ConstIterator const_iterator;

	public:
		size_t count(const K& key) const {
			return  _table.count(key);
		}
		iterator find(const K& key) {
			return _table.find(key);
		}
		iterator insert(const T& data) {
			return _table.insert(data);
		}
		size_t erase(const K& key) {
			return _table.erase(key);
		}
	public:
		iterator begin() {
			return _table.begin();
		}
		iterator end() {
			return _table.end();
		}
		
		const_iterator begin()const {
			return _table.begin();
		}
		const_iterator end()const {
			return _table.end();
		}

		void swap(unordered_map& HT) {
			std::swap(_table, HT._table);
		}

		bool empty() {
			return _table.empty();
		}

		size_t size() {
			return _table.size();
		}

		void clear() {
			_table.clear();
		}

		float load_factor() const noexcept {
			return _table.load_factor();
		}

		float max_load_factor(float fac = 0) {
			return _table.max_load_factor(fac);
		}

		size_t bucket_count() const {
			return _table.bucket_count();
		}

		size_t bucket_size(size_t pos) const {
			return _table.bucket_size(pos);
		}

		size_t bucket(const K& key) const {
			return _table.bucket(key);
		}

		void reserve(size_t n) {
			_table.reserve(n);
		}

		void rehash(size_t n) {
			_table.reserve(n);
		}

	protected:
		HT _table;
	};

	template<class K, class V, class Code = default_Code<K>, class Equal = default_equal<K>>
	void swap(unordered_map<K, V, Code, Equal>& map1, unordered_map<K, V, Code, Equal>& map2) {
		map1.swap(map2);
	}




	void test_unordered_map() {
		srand(time(NULL));
		const int N = 1000000;


		unordered_map<int, int> m;
		std::unordered_map<int, int> m1;
		vector<int> v;
		v.reserve(N);
		/*m.reserve(N);
		m1.reserve(N);
		*/
		
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


		for (auto e : v) {
			size_t n1= m.count(e);
			size_t n2 = m1.count(e);
			cnt1 += n1;
			cnt2 += n2;
			if (n1 != n2)cout << "error ！！！！> data:" << e << endl;
		}
		/*cnt1 = m.size();
		cnt2 = m1.size();*/


		cout << "mymap  find:" << find_end1 - find_begin1 << endl;
		cout << "stdmap find:" << find_end2 - find_begin2 << endl;
		cout << "mymap  cnt:" << cnt1 << endl;
		cout << "stdmap cnt:" << cnt2 << endl;
		cout << "mymap  size:" << m.size() << endl;
		cout << "stdmap size:" << m1.size() << endl;


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

