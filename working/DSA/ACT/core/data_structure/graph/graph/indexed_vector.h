#pragma once
#include<vector>
#include<unordered_map>
#include<assert.h>

namespace xdh {

	template<class T>
	class indexed_code {
	public:
		size_t operator()(const T& data) const {
			return data;
		}
	};

	template<class T>
	class indexed_equal {
	public:
		bool operator()(const T& L,const T& R) const {
			return L == R;
		}
	};

	template<class T, class Code= indexed_code<T>, class Equal= indexed_equal<T>>
	class indexed_vector {
	public:
		class code_ptr {
		public:
			size_t operator()(const T* ptr) const {
				Code code;
				return code(*ptr);
			}
		};
		class equal_ptr {
		public:
			bool operator()(const T* lhs, const T* rhs) const {
				Equal equal;
				return equal(*lhs, *rhs);
			}
		};

		typedef typename std::vector<T*>::iterator iterator;
		typedef typename std::vector<T*>::const_iterator const_iterator;


		indexed_vector() = default;
		indexed_vector(const indexed_vector& iv) {
			_data.reserve(iv._data.size());
			_index.reserve(iv._index.size());

			for (auto ptr : iv._data) {
				_data.push_back(new T(*ptr));
			}
			for (size_t i = 0; i < _data.size(); ++i) {
				//_index[_data[i]] = i;
				_index.insert(std::make_pair(_data[i], i));
			}
		}

		indexed_vector& operator=(indexed_vector temp) {
			if (this != &temp) {
				swap(temp);
			}
			return *this;
		}

		~indexed_vector() {
			for (auto ptr : _data) {
				delete ptr;
			}
		}


	public:
		iterator begin() {
			return _data.begin();
		}
		iterator end() {
			return _data.end();
		}
		const_iterator begin() const {
			return _data.begin();
		}
		const_iterator end() const {
			return _data.end();
		}

		const T& operator[](size_t index) const{
			return data_of(index);
		}
		T& operator[](size_t index) {
			return data_of(index);
		}
		T* at(size_t index) {
			return _data.at(index);
		}
		size_t operator()(const T& data) {
			return index_of(data);
		}
		const size_t operator()(const T& data)const {
			return index_of(data);
		}

		size_t index_of(const T& data) {
			const T* ptr = &data;
			auto it = _index.find(ptr);
			return it != _index.end() ? it->second : -1;
		}

		vector<size_t> indices_of(const T& data) {
			vector<size_t>	ret;
			for (auto it = _index.begin(); it != _index.end(); ++it) {
				if (Equal()(*it->first, data)) {
					ret.push_back(it->second);
				}
			}
			return ret;
		}

		void push_back(const T& data) {
			auto temp = new T(data);
			_data.push_back(temp);
			//_index.insert(_data.back())->second = _data.size() - 1;
			_index.insert(std::make_pair(_data.back(), _data.size() - 1));
		}

		void pop_back() {
			assert(!_data.empty());
			for(auto it = _index.begin(); it != _index.end(); ++it) {
				if (it->second == _data.size() - 1) {
					_index.erase(it);
					break;
				}
			}//注意map内部判断equal使用的是仿函数比较T，但是外部可以直接访问T*比较
			delete _data.back();
			_data.pop_back();
		}

		size_t erase(iterator pos) {
			if(_data.empty() || pos < _data.begin() || pos >= _data.end()) {
				return 0;
			}
			for(auto it=_index.begin(); it != _index.end(); ++it) {
				if(it->first == *pos) {
					_index.erase(it);
					break;
				}
			}
			_data.erase(pos);
			return 1;
		}

		size_t size() const {
			return _data.size();
		}

		bool empty() const {
			return _data.empty();
		}

		void clear() {
			for (auto ptr : _data) {
				delete ptr;
			}
			_data.clear();
			_index.clear();
		}



		void swap(indexed_vector& other) {
			std::swap(_data, other._data);
			std::swap(_index, other._index);
		}

		void shrink_to_fit() {
			_data.shrink_to_fit();
			_index.clear(); // 注意这里清空索引，因为数据可能已经被删除
			for (size_t i = 0; i < _data.size(); ++i) {
				_index.insert(std::make_pair(_data[i], i));
			}
		}	

		void reserve(size_t size) {
			_data.reserve(size);
			_index.reserve(size);
		}
		void resize(size_t size,const T& value=T()) {
			if(size> _data.size()) {
				for (size_t i = _data.size(); i < size; ++i) {
					_data.push_back(new T(value));
					_index.insert(std::make_pair(_data.back(), i));
					//_index.insert(_data.back())->second = i;
					//_index[_data.back()] = i;
				}
			} else if (size < _data.size()) {
				size_t count = _data.size() - size;
				for(auto it = _index.begin(); it != _index.end();) {
					if (it->second >= size) {
						it = _index.erase(it);
						count--;
					}
					if(count == 0) {
						break;
					}
					else {
						++it;
					}
				}
				for (size_t i = size; i < _data.size(); ++i) {
					delete _data[i];
				}
				_data.resize(size);
			}
		}



	private:
		T& data_of(size_t index) {
			assert(index < _data.size());
			return *(_data[index]);
		}
		const T& data_of(size_t index) const{
			assert(index < _data.size());
			return *(_data[index]);
		}
		

	private:
		std::vector<T*> _data;
		std::unordered_multimap<const T*, size_t, code_ptr, equal_ptr> _index;
	};//注意这是一个multimap，允许多个相同的元素,注意erase删除一个元素时，可能会删除多个相同的元素

	template<class T, class Hash = std::hash<T>, class Equal = std::equal_to<T>>
	void swap(indexed_vector<T, Hash, Equal>& lhs, indexed_vector<T, Hash, Equal>& rhs) {
		lhs.swap(rhs);
	}










	

	void test_vector01()
	{
		xdh::indexed_vector<int, std::hash<int>, std::equal_to<int>> arr;

		for (int i = 1; i <= 10; ++i) {
			arr.push_back(i * 10);
		}

		for (int i = 0; i < 10; ++i) {
			std::cout << arr[i] << " ";
		}
		cout << endl;

		for (int i = 1; i <= 10; ++i) {
			std::cout << arr(i * 10) << " ";
		}

		cout << -1;
	}


	
	
}
