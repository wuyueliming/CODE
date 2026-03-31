#include<iostream>
using namespace std;


void reverse(int* arr, int beg, int end) {
	int l = beg;
	int r = end - 1;
	while (r > l) {
		int t = arr[l];
		arr[l] = arr[r];
		arr[r] = t;
		r--; l++;
	}
}

void shift_L(int* arr, int N, int k) {
	k %= N;
	reverse(arr, 0, k);
	reverse(arr, k, N);
	reverse(arr, 0, N);
}

void shift_R(int* arr, int N, int k) {
	k %= N;
	reverse(arr, 0, N - k);
	reverse(arr, N - k, N);
	reverse(arr, 0, N);
}

bool shift(int* arr, int N, int k, char way) {
	if (way == 'L') {
		shift_L(arr,N,k);
	}
	else if (way == 'R') {
		shift_R(arr, N, k);
	}
	else {
		return false;
	}
	return true;
}


int main()
{
	int n = 10;
	int arr[10] = { 0,1,2,3,4,5,6,7,8,9 };
	 

	return 0;
}


















