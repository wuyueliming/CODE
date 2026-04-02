#pragma once
#include"HashTable.h"


namespace STL {

	template<class K, class Code = default_Code<K>,class Equal =default_equal<K>>
	class unordered_set {
	public:
		typedef const K T;
		typedef K V;

		struct KeyOfData_set {
			const K& operator()(const T& data) {
				return data;
			}
		};

		typedef HashTable<K, T, KeyOfData_set, Code, Equal> HT;
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

		void swap(unordered_set& HT) {
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

	template<class K,class Code = default_Code<K>, class Equal = default_equal<K>>
	void swap(unordered_set<K, Code, Equal>& set1, unordered_set<K,Code, Equal>& set2) {
		set1.swap(set2);
	}





	void test_unordered_set() {
		srand(time(NULL));
		const int N = 1000000;


		unordered_set<int> s;
		std::unordered_set<int> s1;
		vector<int> v;
		v.reserve(N);
		s.reserve(N);
		s1.reserve(N);


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

		/*for (auto e : v) {
			cnt1 += s.count(e);
			cnt2 += s1.count(e);
		}*/
		

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