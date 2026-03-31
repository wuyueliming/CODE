#pragma once
#define _CRT_SECURE_NO_WARNINGS 1
#include<string.h>
#include<assert.h>
#include<iostream>
//////#include"CMalloc.h"


namespace STL {
	using namespace std;

	class string {
	public:
		typedef char* iterator;
		typedef const char* const_iterator;
		//默认构造函数
		string(const char* s="") :_str(nullptr), _size(0), _capcity(0) {
			if (s != nullptr) {
				_size = strlen(s);
				_str = new char[_size + 1];
				_capcity = _size;
				//strcpy(_str, s);
				string_copy(s);
			}
		}
		//复制构造函数
		string(const string& s)  {
			string temp(s.c_str());
			swap(temp);
		}
		//赋值重载(构造)函数
		string& operator =(string temp) {
			if (this == &temp)return *this;
			swap(temp);
			return *this;
		}
		//析构函数
		~string() {
			if (_str) {
				delete[] _str;
				_str = nullptr;
			}
			_size = 0;
			_capcity = 0;
		}

		//增删
		void insert(size_t pos, const char* str);//可复用
		void erase(size_t pos, size_t len = npos);
		
		void insert(size_t pos, char ch);
		void push_back(char ch);
		void append(const char* str);
		string& operator+=(char ch);
		string& operator+=(const char* str);
		void pop_back();
		

		//查改
		void getBC(int* BC, int N, const char* s2, size_t size)const;
		void getss(size_t* ss, const char* s2, size_t size)const;
		void getGS(size_t* GS, const char* s2, size_t size)const;
		void getnext(size_t* next, const char* s2, size_t size)const;
		size_t  strstr_BF1(const char* s0, size_t pos = 0)const;
		size_t strstr_KMP(const char* s0, size_t pos = 0, size_t sz2 = -1)const;
		size_t  strstr_BF2(const char* s0, size_t pos = 0)const;
		size_t  strstr_BM(const char* s0, size_t pos = 0,size_t sz2=-1)const;
		size_t strstr_RabinKarp();
		size_t  find(char ch, size_t pos = 0)const;
		size_t  find(const char* str, size_t  pos = 0, size_t sz = -1)const;
		string substr(size_t pos = 0, size_t len = npos);
		char& operator[](size_t pos) {
			return _str[pos];
		}
		const char& operator[](size_t pos)const {
			return _str[pos];
		}
		
	////////////////////////////////////////////////////辅助函数//////////////////////////////////////////////////////////////
		void swap(string& s) {
			std::swap(_str, s._str);
			std::swap(_size, s._size);
			std::swap(_capcity, s._capcity);
		}
		iterator begin() {
			return _str;
		}
		const_iterator begin()const {
			return _str;
		}
		iterator end() {
			return _str+_size;
		}
		const_iterator end()const {
			return _str+_size;
		}
		char* c_str() {
			return _str;
		}
		const char* c_str() const {
			return _str;
		}
		size_t size()const {
			return _size;
		}
		size_t capcity()const {
			return _capcity;
		}
		void reserve(size_t N);
		

	private:
		void string_copy(const char* s) {
			const char* p1 = s;
			char* p2 = _str;
			while (*p1) {
				*p2 = *p1;
				p1++;
				p2++;
			}
			*p2 = '\0';
		}

	private:
		char* _str = nullptr;
		size_t _size = 0;//在任意构造函数中，如果没有使用初始化列表初始化，就会使用这里的缺省值初始化(如复制构造函数)
		size_t _capcity = 0;

		static const size_t npos=-1;//只有静态整形常量可以直接给缺省值(特殊处理,方便一些写法)
		//static const size_t npos;正常是声明和定义分离，如果定义在.h文件中就会重定义出现链接问题
	};
	bool operator<(const string& s1, const string& s2);
	bool operator<=(const string& s1, const string& s2);
	bool operator>(const string& s1, const string& s2);
	bool operator>=(const string& s1, const string& s2);
	bool operator==(const string& s1, const string& s2);
	bool operator!=(const string& s1, const string& s2);

	std::ostream& operator<<(std::ostream& out, const string& s);
	std::istream& operator>>(std::istream& in, string& s);//设置全局函数，保证顺序
}

void swap(STL::string& s1, STL::string& s2);//显式重载swap直接交换内部数据提升效率，避免进行多次深拷贝










