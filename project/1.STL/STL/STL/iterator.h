#pragma once

template<class iterator, class ref, class ptr>
struct  reverseiterator {
	typedef reverseiterator<iterator, ref, ptr> self;

	reverseiterator(iterator it=iterator()) :_rit(it) {}
	template<class RIT>
	reverseiterator(const RIT& rit) :_rit(rit._rit){}//支持iterator类型转换const_iterator
		                                            //支持隐式类型转换，对应的单参数operator=不用写了



	bool operator !=(const self& it) {
		return _rit != it._rit;
	}
	bool operator ==(const self& it) {
		return _rit == it._rit;
	}

	ref operator*() {
		self temp = *this;
		--(temp._rit);
		return *(temp._rit);
	}

	ptr operator->() {
		return &(operator*());
	}

	self operator++(int) {
		self temp = *this;
		--_rit;
		return temp;
	}
	self& operator++() {
		--_rit;
		return *this;
	}
	self operator--(int) {
		self temp = *this;
		++_rit;
		return temp;
	}
	self& operator--() {
		++_rit;
		return *this;
	}



	iterator _rit;
};
