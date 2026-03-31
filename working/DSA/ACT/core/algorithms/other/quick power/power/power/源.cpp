#include<iostream>
using namespace std;

int power(int a, int n) {
	int pow = 1;//累积
	int p = a;//累乘项

	while (n > 0) {//最后一定是n=1，pow*p。
		if (n & 1)//奇数
			pow *= p;//拿出一个p进行累积，n需要减1.(可以省略，n/2 自动取下整)
		n >>= 1;//指数减半
		p *= p;//底数翻倍
	}

	return pow;
}

int main() {
	int a, n;
	cin >> a >> n;
	power(a, n);

	return 0;
}













