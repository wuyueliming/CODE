#pragma once
#include<vector>
#include"deque.h"
namespace STL {

	template<typename T, class container = STL:: vector<T >>
	class stack {

		stack(size_t max_size = 0) {
			_stk.reserve(max_size);
		}

		void push(const T& x) {
			_stk.push_back(x);
		}
		void  pop() {
			_stk.pop_back();
		}
		T& top() {
			return _stk.back();
		}

		void swap(stack& stk) {
			std::swap(_stk, stk._stk);
		}

		size_t size() {
			return _stk.size();
		}

		bool empty() {
			return _stk.empty();
		}

	private:
		container _stk;
	};



	template<typename T>
	void swap(stack<T>& stk1, stack<T>& stk2) {
		stk1.swap(stk2);
	}

}