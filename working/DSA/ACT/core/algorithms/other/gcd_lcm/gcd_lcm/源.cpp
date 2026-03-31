#include<iostream>
using namespace std;

int gcd(int a, int b) {//欧几里得法
	int c;
	while (c = a % b) {
		a = b;
		b = c;
	}

	return b;
}

int lcm(int a, int b) {//欧几里得法
	return a * b / gcd(a, b);
}

int gcd_CN(int a, int b) {//九章算术的中华更相减损术
	int r = 0;
	while (!(a & 1) || (b & 1)) {
		a >>= 1; b >>= 1; r++;
	}
	while (1) {//没有乘除运算，一般而言效率更高
		while (!(a & 1))a >>= 1;
		while (!(b & 1))b >>= 1;
		(a > b) ? a = a - b : b = b - a;
		if (!a)return b << r;
		if (!b)return a << r;
	}
}


int main()
{
	int a, b;
	a = 36;
	b = 81;

	//int g1 = gcd_CN(a, b);
	int g2 = gcd(a, b);

	return 0;
}
