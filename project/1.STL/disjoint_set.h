#pragma once
#include"union_find.h"



//union_find是内存由用户管理的类，数据不会保存在类中
//disjoint_set是数据由类来管理的类，通过复用union_find来实现
namespace xdh {

	template<typename T>
	class disjoint_set {
	public:
		 



		//目前没有很好的解决数据重复储存的问题
	private:
		std::vector<T> _data;
		std::unordered_map<T, int> _index;//需要注意T的类型必须是可哈希问题
		union_find _set;
	};

}








