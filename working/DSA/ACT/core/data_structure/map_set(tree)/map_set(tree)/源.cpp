#include<iostream>
using namespace std;
#include"BinTree.h"
#include"BSTree.h"
#include"SplayTree.h"

#include"LeftHeap.h"
#include"AVLTree.h"
#include"RBTree.h"

#include"map.h"
#include"set.h"

#include<string>
#include<map>
#include<set>

void test() {
	map<int, string> m;
	m.insert({ 1,"1" });

	map<int, string>::iterator it = m.begin();
	map<int, string>::const_iterator cit = it;
	//仅限debug版本
	//cout << it._Myproxy;//stl可以const转成普通 iterator，也能取内部变量，和我的实现类型转化的方式一样。
}

int main()
{

	//xdh::testA2();//bintree

	//xdh::testB3();//BSTree

	//xdh::testC2();//LeftHeap

	//xdh::testD3();//AVLTree

	//xdh::testE3();//RBTree

	//xdh::testX2();//map

	//xdh::testY1();//set

	//xdh::testZ2();//SplayTree

	
	xdh::testX3();//map性能测试

	//xdh::testY2();//set性能测试

	
	return 0;
}