#pragma once
#include<vector>
#include<cmath>


namespace xdh {

	template<class Key>
	struct default_Code {
		size_t operator()(const Key& key) {
			return (size_t)key;
		}
	};

	template<>//string常用，特化string版本
	struct default_Code<string> {
		size_t operator()(const string& str) {
			size_t ret = 0;
			int i = 0;
			for (auto c : str) {
				ret += ++i * str[i];
			}
			return ret;
		}
	};

	template<class Key>
	struct default_equal {
		bool operator()(const Key& k1, const Key& k2) {
			return k1 == k2;
		}
	};

	template<class T>
	struct hash_node {
		T data;
		hash_node* next;

		hash_node(const T& Data = T(), hash_node* Next = nullptr)
			:data(Data)
			,next(Next){ }

	};


	template<class T,class ref ,class ptr,class Table>
	class HT_iterator {
	public:
		typedef hash_node<T> node;
		typedef HT_iterator<T, ref, ptr, Table> self;

		HT_iterator(node* pn = nullptr, Table* pt = nullptr,size_t pos=0)
			:_pnode(pn)
			, _ptable(pt)
			, _pos(pos){ }
		
		bool operator==(const self& HT_it) {
			return _pnode == HT_it._pnode;
		}
		bool operator!=(const self& HT_it) {
			return !operator==(HT_it);
		}

		ref operator* () {
			return _pnode->data;
		}
		ptr operator->() {
			return &(_pnode->data);
		}

		self& operator++() {
			Table _table = *_ptable;

			if (_pnode->next) {
				_pnode = _pnode->next;
			}
			else {
				++_pos;
				_pnode = _table[_pos];
			}
			return *this;
		}
		self operator++(int) {
			self temp(*this);
			++(*this);
			return temp;
		}

		explicit operator bool()const {
			return _pnode;
		}

	public:
		node* _pnode;
		Table* _ptable;
		size_t _pos;
	};



	template<class Key,class T,class KeyOfData,class Code = default_Code<Key>,class Equal= default_equal<Key>>
	class HashTable {
	public:
		typedef size_t HashCode;
		typedef hash_node<T> node;
		typedef HT_iterator<T, T&, T*, vector<node*>> Iterator;
		typedef HT_iterator<T, const T&, const T*, vector<node*>> ConstIterator;



	public:
		HashTable(size_t table_size=8)
			:_table(table_size)
			,_size(0){ }

		HashTable(const HashTable& HT) {
			_table.resize(HT._table.size());
			_size = HT._size;
			_factor = HT._factor;

			for (size_t i = 0; i < HT._table.size(); i++) {
				if (HT._table[i]) {
					node* cur = _table[i];
					node* next;

					while (cur) {
						next = cur->next;
						insert(cur->data);
						cur = next;
					}
				}
			}
		}

		HashTable& operator=(HashTable temp) {
			swap(temp);
			return *this;
		}

		~HashTable() {
			clear();
		}

	public:

		//Iterator insert(ConstIterator pos,const T& data);
		Iterator insert(const T& data) {
			KeyOfData KOD; Code code;
			Iterator ret = find(KOD(data));
			if (ret)return ret;
			
			_size++;
			if ( load_factor() > max_load_factor()) {
				rehash(_table.size() * 2);
			}

			HashCode pos = hash(code(KOD(data)));
			node* newnode = new node(data);
			newnode->next = _table[pos];
			_table[pos] = newnode;
			
			return { newnode,&_table,pos };
		}

		//Iterator erase(ConstIterator position);
		size_t erase(const Key& key) {
			auto p = search(key);
			if (!p.first)return 0;

			KeyOfData KOD; Code code; Equal equal;
			node* del = p.first;
			
			if (!p.second) {
				HashCode pos = hash(code(key));
				_table[pos]= del->next;
				delete del;
			}
			else {
				node* pre = p.second;
				pre->next = del->next;

				delete del;
			}
			
			return 1;
		}

		Iterator find(const Key& key) {
			Code code;
			HashCode pos = hash(code(key));
			return { search(key).first,&_table,pos };
		}

		size_t count(const Key& key) const {
			KeyOfData KOD; Code code;
			HashCode pos = hash(code(key));
			Equal equal;

			node* cur = _table[pos];
			size_t size = 0;

			while (cur) {
				if (equal(KOD(cur->data), key))size++;
				cur = cur->next;
			}
			return size;
		}


	public:
		Iterator begin() {
			if (!_size)return end();
			for (size_t i = 0; i < _table.size(); i++) {
				if (_table[i])
					return{ _table[i],&_table ,i};
			}
			return end();
		}
		Iterator end() {
			return { nullptr,&_table,_table.size()};
		}

		ConstIterator begin() const{
			if (!_size)return end();
			for (size_t i = 0; i < _table.size(); i++) {
				if (_table[i])
					return{ _table[i],&_table,i };
			}
			return end();
		}
		ConstIterator end() const {
			return { nullptr,&_table ,_table.size()};
		}

		void swap(HashTable& HT) {
			std::swap(_table, HT._table);
			std::swap(_size, HT._size);
			std::swap(_factor, HT._factor);
		}

		bool empty() {
			return _size == 0;
		}

		size_t size() {
			return _size;
		}

		void clear() {
			for (size_t i = 0; i < _table.size(); i++) {
				if (_table[i]) {
					node* cur = _table[i];
					node* next;

					while (cur) {
						next = cur->next;
						delete cur;
						cur = next;
					}
				}
			}
			_size = 0;
		}

		float load_factor() const noexcept {
			return ((float)_size / (float)_table.size());
		}

		float max_load_factor(float fac=0){
			if (fac) _factor = fac;
			return _factor;
		}

		size_t bucket_count() const {
			return _table.size();
		}

		size_t bucket_size(size_t pos) const {
			size_t size = 0;
			node* cur = _table[pos];
			node* next;

			while (cur) {
				next = cur->next;
				size++;
				cur = next;
			}
		}

		size_t bucket(const Key& key) const {
			Code code;
			return hash(code(key));
		}

		void reserve(size_t n) {
			if (n <= _size)return;

			size_t sz = _table.size();
			while (sz <= n) {
				sz *= 2;
			}
			rehash(sz);
		}

	private:
		HashCode hash(const HashCode& code) const {
			static double gold_partion = (sqrt(5) - 1) / 2;
			double intpart;

			return modf(code * gold_partion ,&intpart) * _table.size();
			//return code % _table.size();//最基本的除数留余法
		}

		pair<node*, node*> search(const Key& key) {
			KeyOfData KOD; Code code;
			HashCode pos = hash(code(key));

			if (!_table[pos]) return pair<node*, node*>(nullptr,nullptr);

			Equal equal;
			node* pre = nullptr;
			node* cur = _table[pos];
			while (cur) {
				if (equal(KOD(cur->data), key)) {
					return pair<node*, node*>( cur,pre );
				}
				pre = cur;
				cur = cur->next;
			}
			return pair<node*, node*>(nullptr, pre);
		}

		void rehash(size_t n) {
			if (n <= _size)return;

			KeyOfData KOD; Code code;
			HashTable<Key, T, KeyOfData, Code, Equal> temp(n);
			temp._size = _size;

			//这里不能用this的hash，要用temp的hash。因为this的_table的大小还是 没更新的大小
			for (size_t i = 0; i < _table.size(); i++) {
				if (_table[i]) {
					node* cur = _table[i];
					node* next;
					
					while (cur) {
						next = cur->next;

						HashCode newpos = temp.hash(code(KOD(cur->data)));
						cur->next = temp._table[newpos];
						temp._table[newpos] = cur;

						cur = next;
					}
					_table[i] = nullptr;
				}
			}
			swap(temp);
		}

	private:
		vector<node*> _table;
		size_t _size;
		float _factor = 1;
	};

	template<class Key, class T, class KeyOfData, class Code = default_Code<Key>, class equal = default_equal<Key>>
	void swap(HashTable<Key, T, KeyOfData, Code, equal>& HT1, HashTable<Key, T, KeyOfData, Code, equal>& HT2) {
		HT1.swap(HT2);
	}


	template<class T>
	struct KOD1 {
		const T& operator()(const T& data) {
			return data;
		}
	};

	void test01() {
		HashTable<int, int, KOD1<int>> ht;
		const int N = 1000;
		ht.reserve(N);

		for (int i = 0; i < N; i++) {
			ht.insert(i);
		}

		for (int i = 0; i < N; i++) {
			cout << i << ":";
			auto ret =ht.find(i)!=nullptr ? 1 : 0;
			cout << ret << endl;
		}



	}






}













