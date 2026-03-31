#include"string.h"
using namespace std;

namespace xdh{
	void test1() {
		string s1("hello world");
		s1.reserve(41);
		cout << s1.c_str();
		///cout << s1.size();
		cout << s1.capcity();
	}
	void test2() {
		string s1("hello world");
		string s2(s1);
		cout << s2.c_str() << endl;
		cout << s2.capcity();
	}
	void test3() {
		string s1("hello world");
		string s2("s2");
		/*s2 += ' ';
		s2 += "wc";*/
		if (s1> s2) {
			cout << 1;
		}
		else {
			cout << 0;
		}
		
	}
	void test4() {
		string s1("hello world");
		string s2("s2");
		s1.insert(11, s2.c_str());
		cout << s1 << endl;
		s1.erase(0);
		cout << s1 << endl;
		
	}
	void test5() {
		string s1("hello world");
		s1 += '1';
		s1 += "234";
		cout << s1 << endl;
	}
	void test6() {
		string s1("ICED RICE PHILADELPHIA  ICED RICE PRICE");

		cout << s1.strstr_BM("ICED RICE PRICE");

	}
}


int main()
{

	xdh::test6();

	/*size_t* arr = new size_t[10];
	arr[-1] = 1;
	delete[] arr;*/

	return 0;
}

























