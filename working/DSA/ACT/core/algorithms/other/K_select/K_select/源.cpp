#include<iostream>
#include<vector>
#include<queue>
using namespace std;


/////////////////////////////////////////////////// 特殊值k = n/2 /////////////////////////////////////////////////////////
												  // 中位数选取	
//一、有众数时，众数==中位数(出现次数大于一半的数为众数)
template<class array>
bool checkmode(array arr, size_t n,int mode) {
	size_t cnt = 0;
	for (size_t i = 0; i < n; i++) {
		if (arr[i] == mode)cnt++;
	}

	return cnt > n / 2;
}

template<class array,class T>
bool getmode(array arr, size_t n,T& val) {
	int mode ;
	int differ;
	
	size_t  left = 0;
	size_t right = n;
	for (mode = arr[0],differ =0 ; right > left; left++) {
		if (differ == 0) {
			mode = arr[left];
			differ = 1;
		}
		arr[left] == mode ? differ++ : differ--;
		
	}

	
	val = mode;
	return checkmode(arr, n, mode);
}

//已有两个有序数组，得到合并后的中位数
//数组等长
template<class array>
int median(array arr1, size_t lo1, size_t n1, array arr2, size_t lo2,size_t n2) {
	vector<typeid(arr1[0]).name()> v;


}

template<class array>
int  getmedian(array arr1, size_t lo1, array arr2, size_t lo2, size_t n) {
	if(n<3)return median




}




//数组不等长





///////////////////////////////////////////////////// 第K大数选取 /////////////////////////////////////////////////////////




int main()
{
	int arr[] = { 0,1,1,1,0 };

	int mode = -1;
	getmode(arr, 5, mode);
	cout << mode;

	return 0;
}
