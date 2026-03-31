#include<iostream>
using namespace std;
#include<unordered_map>
#include<unordered_set>

#include"HashTable.h"

#include"unordered_map.h"
#include"unordered_set.h"


void test() {
	unordered_set<int> s;

	cout << s.max_load_factor() << endl;
	cout << s.bucket_count() << endl;

	for (int i = 0; i <50; i++) {
		s.insert(i);
	}

	
	s.rehash(64);
	//s.reserve(64);
	cout << s.bucket_count();


}

int main()
{
	//test();

	
	//xdh::test01();

	xdh::testX1();

	return 0;
}





