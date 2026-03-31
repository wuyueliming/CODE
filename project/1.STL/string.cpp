#include "string.h"


void swap(STL::string& s1, STL::string& s2) {
	s1.swap(s2);
}

namespace STL{
	//const size_t string::npos = -1;定义
	
	/////////////////////////////////////////////////////查改////////////////////////////////////////////////////////////////
	size_t  string::strstr_BF1(const char* s2, size_t pos)const {
		size_t m = _size;
		size_t n = strlen(s2);
		size_t i = pos, j = 0;
		while (i != m && j != n) {
			if (_str[i] == s2[j]) {
				i++;
				j++;
			}
			else {
				i -= j;
				j = 0;
				i++;
			}
		}
		return i - j;
	}
	size_t string::strstr_KMP(const char* s2, size_t pos ,size_t sz2)const {
		size_t m = _size;
		size_t n = sz2 == -1 ? strlen(s2) : sz2;
		size_t i = pos, j = 0;

		size_t* next = new size_t[n]{ 0 };
		getnext(next, s2, n);//next数组用int足矣(因为最长匹配前缀长度不太可能超过int)

		while (i != m && j != n) {//int -1和npos等价
			if (j== -1 || _str[i] == s2[j]) {
				i++;
				j++;
			}
			else {
				j = next[j];
			}
		}

		delete[]next;
		return j == n ? i - j : npos;
	}

	size_t  string::strstr_BF2(const char* s2, size_t pos)const {
		size_t m = _size;
		size_t n = strlen(s2);
		size_t i = pos, j = 0;
		while (i != m && j != n) {
			if (_str[i+j] == s2[j]) {
				j++;
			}
			else {
				i++;
				j = 0;
			}
		}
		return i;
	}
	size_t string::strstr_BM(const char* s2, size_t pos,size_t sz2)const {
		size_t m = _size;
		size_t n = sz2 == -1 ? strlen(s2) : sz2;
		size_t i = pos, j = n - 1;

		const int N = 128;//字符集个数
		int* BC = new int[N];
		size_t* GS = new size_t[n];
		getBC(BC,N, s2, n);//bc在j右边:右移一格、在左边或者没有:右移j-bc
		getGS(GS, s2, n);//直接右移gs格

		while (i <= m-n  && j != -1) {//一次跳过很多位置，不要用 i != m-n 来判断
			if (_str[i + j] == s2[j]) {
				j--;
			}
			else {
				size_t bc = BC[_str[i+j]];
				size_t gs = GS[j];
				
				if (bc!=-1 && bc > j) {
					i += gs;
				}
				else {
					size_t shift = std::max(j - bc, gs);
					i += shift;
				}
				j = n - 1;
			}
		}
		delete[]BC;
		delete[]GS;//越界访问后无法删除
		return j == -1 ? i : npos;
	}

	void string::getnext(size_t* next, const char* s, size_t size)const {
		next[0] = -1;//不过还是用了size_t，因为npos + 1 = 0是一个循环，可以直接替代int中的-1来使用
		if (size == 1)return;

		//pos:当前求next位置，pre:前一个位置对应next值—>next[pos-1]
		size_t pre = next[0], pos = 1;
		while (pos != size) {
			if ( pre == -1 || s[pos-1] == s[pre]) {
				++pre;//对比字符1: pos-1 pre   对比字符2: pos  pre+1
				next[pos] = (s[pre] == s[pos] ? next[pre] : pre);//提前比较下一位置的字符，如果一样，那换不换没区别
				pos++;//如果成功进入对比1，就提前进行下次循环的对比2。如果三目结果是pre,那么pos位置的next值就是正常的
			}         //pos-1的next值加1,相当于next[pos] =next[pos-1]+1 ,++pre=next[pos-1]+1，next[pos] = ++pre。
			else {    //如果结果是next[pre]，说明对比2失败，下个循环一定进入else后
				pre = next[pre];//相当于next[pos]=next[next[pos-1]+1] ,++pre=next[next[pos-1]+1]。这样，pre始终
			}                   //保证是pos前一个位置对应next值。(递推思想)
		}                       //如此就保证了next[pos] = ++pre始终符合求next数组的算法的要求


	}
	void string::getBC(int* BC,int N, const char* s2, size_t size)const {
		for (size_t i = 0; i < N; i++) {
			BC[i] = -1;
		}
		for (size_t i = 0; i < size; i++) {
			BC[s2[i]] = i;
		}
	}
	void string::getss(size_t* SS, const char* s2, size_t size)const {
		for (size_t i = 0; i < size; i++) {
			SS[i] = 0;
		}
		SS[size - 1] = size;

		size_t hi,lo;// 子串(lo,hi]是已知的一个与整串某个后缀匹配的一个子串
		hi = lo = size - 2;
		for (size_t i = size - 2; i != -1; i--) {
			size_t offset = size - 1 - hi;
			size_t mirror = i + offset;//mirror在后缀中位置 对应于 i在(lo,hi]中位置。
			if ( lo < i && SS[mirror] < i - lo ) {
				SS[i] = SS[mirror];
			}
			else {
				hi = i;
				offset= size - 1 - hi;
				for (lo = std::min(hi, lo); lo != -1; lo--) {
					if (s2[lo] != s2[lo + offset]) {
						break;
					}
				}
				SS[i] = hi - lo;
			}
		}

	}
	void string::getGS(size_t* GS, const char* s2, size_t size)const {
		size_t* ss = new size_t[size];
		getss(ss, s2, size);
		
		for (size_t i = 0; i < size; i++) {
			GS[i] = size;
		}
		size_t pos = 0;
		for (size_t i = size-1; i !=-1 ; i--) {
			if (ss[i] == i + 1) {
				GS[pos++] = size - ss[i];
				/*for (size_t j = size - 1 - ss[i]; j != -1; j--) {
					GS[j] = size - ss[i];
				}*/
			}
		}
		pos = 0;
		for (size_t i = 0; i < size-1; i++) {//小于size-1，也就是只对真子串更新
			pos = size - ss[i] - 1;//i=size-1时发生越界访问，在-1处写入
			GS[pos] = size - 1 - i;
		}

		delete[]ss;
	}
	
	size_t  string::find(char ch, size_t pos) const {
		size_t i;
		for ( i = pos; i < _size; i++) {
			if (_str[i] == ch)break;
		}
		return i < _size ? i : npos;
	}
	size_t  string::find(const char* str, size_t  pos,size_t sz2)const {
		
		return strstr_KMP(str, 0, sz2);
	}
	string string::substr(size_t pos, size_t len) {
		if (len > _size - pos)
		{
			len = _size - pos;
		}

		string sub;
		sub.reserve(len);
		for (size_t i = 0; i < len; i++)
		{
			sub += _str[pos + i];
		}
		sub[len] = '\0';

		return sub;
	}

	/////////////////////////////////////////////////////增删//////////////////////////////////////////////////////////////

	void string::insert(size_t pos, const char* str) {
		assert(pos != -1 && pos <= _size);
		size_t len = strlen(str);
		size_t new_cap = _size + len;
		reserve(new_cap);

		for (size_t i = _size+len; i >= pos+len;i--) {//注意size_t变成-1其实是极大的正数
			_str[i] = _str[i - len];
		}
		_size += len;
		memcpy(_str + pos, str, sizeof(char) * len);
	}
	void string::erase(size_t pos, size_t len ) {
		assert(pos != -1 && pos < _size);
		if (len > _size - pos) len = _size - pos;
		for (size_t i = pos + len; i <= _size; i++) {
			_str[i - len] = _str[i];
		}
		_size -= len;
	}


	void string::insert(size_t pos, char ch) {
		char temp[2];
		temp[0] = ch; temp[1] = '\0';
		insert(pos, temp);
	}
	void string::push_back(char ch) {
		insert(_size, ch);
	}
	void string::append(const char* str) {
		insert(_size, str);
	}
	string& string::operator+=(char ch) {
		push_back(ch);
		return *this;
	}
	string& string::operator+=(const char* str) {
		append(str);
		return *this;
	}
	void string::pop_back() {
		assert(_size >= 1);
		_str[--_size] = '\0';
	}


	//////////////////////////////////////////////////////辅助函数/////////////////////////////////////////////////////////
	void string::reserve(size_t sz) {
		assert(_str != nullptr);
		if (sz > _capcity) {// 大于2倍，需要多少开多少，小于2倍按2倍扩
			size_t new_cap = 2 * _capcity >= sz ? 2 * _capcity : sz;

			char* new_str = new char[new_cap + 1];
			strcpy(new_str, _str);
			std::swap(_str, new_str);
			_capcity = new_cap;

			delete[] new_str;
		}
	}

	bool operator==(const string& s1, const string& s2) {
		return (strcmp(s1.c_str(), s2.c_str()) == 0);
	}
	bool operator!=(const string& s1, const string& s2) {
		return !(s1 == s2);
	}
	bool operator<(const string& s1, const string& s2) {
		return (strcmp(s1.c_str(), s2.c_str()) < 0);
	}
	bool operator<=(const string& s1, const string& s2) {
		return s1 < s2 || s1 == s2;
	}
	bool operator>(const string& s1, const string& s2) {
		return !(s1 <= s2);
	}
	bool operator>=(const string& s1, const string& s2) {
		return !(s1 < s2);
	}
	
	std::ostream& operator<<(std::ostream& out, const string& s) {
		for (auto&  e : s) {
			std::cout << e;
		}
		return out;
	}
	std::istream& operator>>(std::istream& in, string& s) {
		for (auto& e : s) {
			std::cin >> e;
		}
		return in;
	}
}


























