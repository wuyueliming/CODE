////#define _CRT_SECURE_NO_WARNINGS
#include<iostream>
using namespace std;

/*
词法记号：
	关键字：c++预定义的单词
	标识符：程序员定义的单词
	文字：直接表示的数据
	分隔符： （） {}  ， :  ;用于分割各个词法记号或程序
	空白符： 空格、制表符、垂直制表符、换行、回车、注释的总称

标识符命名规则：
	以大小写字母或者下划线开头
	后面可以由大小写字母、下划线、数字组成
	标识符的名字不能和关键字或者操作符相同

基本数据类型
	整数类型
	浮点类型
	字符类型
	布尔类型

变量
	变量的初始化：(使用大括号进行初始化称为列表初始化，不允许信息的丢失。例如把一个小数初始化给一个整数变量时就会发生数据的丢失)
	int a = 0;
	int a(0);
	int a = {0};
	int a{0};


常量
	字面常量：直接给出的数据如：1、3.14、‘a’、“abc”
	符号常量：符号常量定义时必须初始化，使用constexpr关键字要求编译器验证初始值是否为常量表达式。
		const 数据类型 常量名 = 常量值
		constexpr 数据类型 常量名 = 常量表达式



整数类型
	按符号分：signed、unsigned
	按大小分：short、int、long、long long
	char型：本质上存储的是ASCII码值，可以对字符进行加减乘除等运算
整数文字常量
	十进制：数字0—9，不能以0开头，正号可以省略
	八进制：前导0 + 数字0—7。
	十六进制：前导0x + 数字0—9及字母A—F（大小写均可）
	后缀：L表示long型，LL表示long long型，U表示unsigned。默认int


浮点型
	单精度：float
	双精度：double
	扩展精度：long double
浮点数文字常量
	一般形式：1.25、3.14等
	指数形式：35E+2、-3.14E-2。整数部分和小数部分可以省略其一。
	后缀：F/f表示float。默认是double

字符类型
	char型：容纳一个字符的编码值
	字符串类型
		c语言风格：字符数组
		c++风格：类库中的string类
	布尔类型：只有两个值，true和false


类型别名：
	c语言：typedef 已有类型名 新类型名
	c++：using 新类型名 = 已有类型名

auto对于任意的给定c、n、d，其中n小于等于c。如果等式中所有数都是正整数，是否都存在i、j使等式成立？与decltype
	auto：根据初识值自动判断变量类型
	decltype：让一个变量与某一表达式的类型相同，但并不用该表达式初始化这个变量
		如：auto a = 3.14
			decltype(i) b = 2


算数运算符
	+	加号
	-	减号
	*	乘号
	/	除号
	%	取余
	++  自加一     前置：先使用后加减。
	--  自减一     后置：先加减完了，将原来的值暂时备份。然后实际参与运算的值是备份的那个值

赋值运算符与赋值表达式：=
	表达式类型：赋值运算符左边对象的类型
	表达式的值：赋值运算符左边对象被赋值后的值

逗号运算符与逗号表达式：，
	格式：表达式1，表达式2
	求解顺序及结果：先求表达式1，再求表达式2。最终结果为表达式2的值

关系运算与关系表达式
	< <= >= > ==  !=
	结果类型为bool，值为true或者false

逻辑运算与逻辑表达式
	!(逻辑非)	表达式为真，则结果为假
	&&(逻辑与)	全真为真，一假则假
	||(逻辑或)	一真则真，全假为假
	结果类型为bool，值为true或者false
	短路：左式能确定结果则不在判断右式

条件运算符
	格式：表达式1？表达式2：表达式3
	若表达式1为真则结果为表达式2的值，否则为表达式3的值

按位运算：^ & | ~ << >>
	^:不同为1，相同为0
	&:全为1则为1，否则为0
	|:一个是1就是1，全0为0
	~:所有的0和1取反
	<<:左移后低位补0，高位舍弃
	>>:右移后低位舍弃，高位无符号补0有符号补符号位

显示类型转换
	类型说明符（表达式）
	（类型说明符）表达式
	类型转换操作符<类型说明符>(表达式)
		类型转换操作符：const_cast、dynamic_cast、reinterpret_cast、static_cast


分支语句
	if...else...
	switch...case
循环语句
	while
	do...while    ——————和c语言一样
	for
控制语句
	break
	continue
	goto

*/

/*
————————————————————————————————————————————————————————————————————————————————
引用类型
	引用符&在初始化时和*号类似，表示引用。
	例如：int a1=0；
		  int& a2=a1；这个a2就是啊a1的别名，相当于一个地址有了两个名字
		  void swap(int& a,int& b);作为形参是就可以像指针一样在函数内部改变main函数中的实参。
	注意：在定义一个引用变量时，必须对他进行初始化，明确指出是哪一个变量的别名。一旦初始化就不能再改成别的变量的别名



函数默认参数值：如果不给参数就使用预先给定的参数运算，也可以给一个自己的参数，剩下的参数使用默认值。
	如果一个函数有声明且声明在定义之前，则默认值必须在声明中给出；如果只有定义或者定义在前，则默认参数必须在函数定义中给出。
	注意：在声明中设置默认参数值后就不能在定义中设置默认参数值了。否则会被认为是重定义。



内联函数：在声明函数时使用关键字inline
	有些函数经常用，但很简单，反复调用这个函数就会产生额外的开销。使用inline关键字定义函数就能使编译器在二进制层面将函数嵌进使用函数的地方，从而省去了额外的开销
	注意：inline修饰的函数中不能使用switch和循环语句。如果使用了，那么编译器也不会报错，但是函数就不是内联函数了，而被看作是普通函数。
		  内联函数的定义必须在函数使用之前，不能先声明后定义。



函数的重载：允许功能相近的函数在相同的作用域内以相同的函数名来声明，从而形成函数的重载，方便使用，便于记忆。这样使用函数的时候就会根据给的参数来选择用哪一个函数
	注意：1、重载函数时必须是参数表中有不同（参数类型或参数个数），跟返回值的类型无关。如果只有返回值不同，那么认为这两个函数是同一个函数。
		  2、注意形参的名字不同也算作是同一个函数，声明函数时本来就可以不写形参名，即使写了编译器也不会看。
		  3、注意不要把功能差的有点大的或者相反的一对函数重载了。比如把减法的函数重载了一个add的函数名。



————————————————————————————————————————————————————————————————————————————————


*/

#if 0
int fac(int n) {//计算n的阶乘
	if (n == 0) {
		return 1;
	}
	else {
		return n * fac(n - 1);
	}
}

int com(int n, int k) {//高中的组合数，求C n k是多少，在n个数中选k个数右多少中组合
	if (n == k || k == 0) {
		return 1;
	}
	else {
		return com(n - 1, k) + com(n - 1, k - 1);
	}
}


void move(char left, char right, int* a) {//汉诺塔问题，n是代表A中的盘子个数
	*a += 1;
	cout << left << "-->" << right << endl;
}
void hanno(int n, char left, char mid, char right, int* a) {
	if (n == 1) {
		move(left, right, a);
	}
	else {
		hanno(n - 1, left, right, mid, a);
		move(left, right, a);
		hanno(n - 1, mid, left, right, a);
	}
}


void MOVE(char left, char right, int& a) {//————>引用传递，不是使用指针！！！！！！相当于给传过去的实参起一个别名，函数中使用形参会改变主函数中的实参
	a += 1;                                       //形参和实参的地址是一样的！！！！！！！！！！！
	cout << left << "-->" << right << endl;
}
void HANNO(int n, char left, char mid, char right, int& a) {
	if (n == 1) {
		MOVE(left, right, a);
	}
	else {
		HANNO(n - 1, left, right, mid, a);
		MOVE(left, right, a);
		HANNO(n - 1, mid, left, right, a);
	}
}

int main()
{
	char A = 'A';
	char B = 'B';
	char C = 'C';
	int cnt = 0;
	hanno(7, A, B, C, &cnt);//目前来说，两套函数是等效的。
	HANNO(7, A, B, C, cnt);
	cout << "一共移动了" << cnt << "次" << endl;

	return 0;
}
#endif



#if 0
--------------------------------------------------------------------------------------------------------------------------------------------------------------
//类与对象                                                      
class Clock {
public:
	int b;
	//对象对于外部的接口：
	void settime(int hour, int minute, int second);
	void showtime();//如果在类定义中直接写出函数题则认为是一个内联函数
	//构造函数
		//默认构造函数
	//Clock(){};//这个直接写成内联和default有什么区别呢？default只在需要的时候生成，不需要就不生成，节省了消耗
	//Clock() = default;//如果自定义了构造函数，编译器默认不会再生成默认构造函数，如果想要生成就可以=default
	Clock(int h = 0, int m = 0, int s = 0);//自定义构造函数重复，可使用委托构造函数
	//委托构造函数

	//自定义构造函数
	Clock(int hour, int minute, int second);
	//复制构造函数
	Clock(const Clock& copy);
	//Clock(const Clock& copy) = delete;如果不希望对象被复制可以使用delete
	//移动构造函数
	Clock(Clock&& a)noexcept :b(std::move(a.b)) {

	}
	//析构函数
		//~Clock();
private:
	//只在当前对象的内部被使用
	int Hour = 0;
	int Minute = 0;
	int Second = 0;
protected:
	//被保护的成员，除多态继承外和private成员等效
	int order = 0;
};
//------------------------------------------------------------------
Clock::Clock(int hour, int minute, int second) {//自定义构造函数
	//不允许返回值
	//函数名必须是类型名
	Hour = hour;
	Minute = minute;//在类的函数中可以直接使用该类的成员
	Second = second;//进入类内函数的时候会有this指针指向调用函数的对象，本质上是
	this->Hour = hour;//没有报错
}

Clock::Clock() : Clock(0, 0, 0) {
	// 委托构造函数的实现，调用参数为默认值的构造函数
}


Clock::Clock(int h = 0, int m = 0, int s = 0) {//默认构造函数
	//两种默认的只能有一个，因为两个函数的调用都不需要参数，所以编译器不知道该用哪一个
	//在创建对象的时候就对它进行初始化

	//该构造函数和下面那个函数不构成重载函数，会报错，有时类中会出现很多构造函数内部一样，只是参数不一样，可以使用委托构造函数
}



Clock::~Clock() {//析构函数
	//不允许有返回值、参数
	//函数名必须是类型名前加一个~
	//用来完成对象被销毁前的一些准备工作：比如malloc的空间要释放
}

Clock::Clock(const Clock& copy) {//复制构造函数
	//不允许返回值
	//函数名必须是类型名
	//1.在定义对象时用另一个对象初始化时会调用复制构造函数
	//2.在调用函数时将实参的值复制给形参时
	//3.在函数返回一个对象时 --> 生成一个临时对象将数据复制进去(可优化成移动复制构造)
	Hour = copy.Hour;
	Minute = copy.Minute;
	Second = copy.Second;
}


//-----------------------------------------------------------------------
int main()
{
	Clock x();//在类中没有构造函数的时候，如果创建了对象，那么编译器就会自动生成默认构造函数来满足语法要求
	//创建对象时会默认调用构造函数，所以必须要有一个构造函数。默认构造函数只是满足语法要求，初始值是随机值。


	Clock y(1, 2, 3);//使用了自定义构造函数——注意：当类中自定义了构造函数后，如果创建对象还是像x那样初始化就会报错，编译器不会再生成默认构造函数了
	//所以还需要自己定义一个默认构造函数。

	Clock z = y;

	return 0;
}
--------------------------------------------------------------------------------------------------------------------------------------------------------------
#endif






















//--------------------------------------------------------------------------------------------------------------------------------------------------------------
#if 0                                                              //数据的共享与保护与组合类                                                    
class Point {
public:
	friend class Line;//右元声明，表示在Line中可以访问本类的私有、保护成员。
	static int p_count();
	void show()const;
	//构造函数
	Point() = default;
	Point(int x, int y);

	//析构函数
	~Point();
private:
	int X, Y;
protected:
	static int count;//static是类的成员，所以可以直接通过Point::作用域进行访问、调用
};
int Point::count = 0;




class Line {
public:

private:
	Point p1, p2;
protected:

};


//------------------------------------------------------------------
Point::Point(int x, int y) {//构造函数
	X = x;
	Y = y;
	Point::count += 1;
}
Point::~Point() {//析构函数
	Point::count -= 1;
}

int Point::p_count() {
	return Point::count;//static静态成员是类的成员不是对象的成员。所有对象共用这一个count.
}

void Point::show()const {
	cout << '(' << X << ',' << Y << ')' << endl;
}


//-----------------------------------------------------------------------
int main()
{
	{
		Point p(3, 5);
		Point p2;
	}


	int cnt = Point::p_count();//cnt = -1，因为调用默认构造函数时count不会+1；
	cout << cnt << endl;


	const Point p0(9, 1);//const创建的成员只能使用const修饰的函数，并且不能通过任意形式改变初始值。
	p0.show();//反过来，普通对象也可以调用const修饰的函数




	return 0;
}
//--------------------------------------------------------------------------------------------------------------------------------------------------------------
#endif




//------------------------------------------------------------------------------------------------------------------------------------------------------------
															  //动态申请内存与vector动态数组容器
#if 0
#include<vector>
class Point {
public:
	Point() = default;
	Point(int x, int y);
	~Point();

private:
	int x, y;
	static int count;
};
int Point::count = 0;


Point::Point(int x, int) :x(x), y(y) {//构造函数
	Point::count += 1;
}

Point::~Point() {//复制构造函数
	Point::count -= 1;
}


int main()
{

	Point p1;

	Point* pp = new Point();//使用new动态申请一个对象，自动调用构造函数。如果( )给参数就初始化,如果不给参数或者不给( )就调用默认构造函数
	delete pp;//delete 指针pp指向的空间，自动调用析构函数。


	int size = 5;
	pp = new Point[size]();// ( )中不能有参数，是随机值不能进行初始化，( )可以省略。（对于基本数据类型，给括号就初始化为0，不给就随机）；
	delete[] pp;//不管申请的是几维的数组，都可以一个[]全部释放；（像c语言中申请一个int**后对每个int*单独申请的情况有待商榷）


	vector<int> arr(size);//vector是一个封装起来的动态数组，< >中是类型，( )中是大小，arr是数组名
	//遍历1：
	for (auto i = arr.begin(); i < arr.end(); ++i) {
		cout << *i << endl;// i可以看作是一个泛型指针，初始化得到地址
	}
	//遍历2：
	for (auto i : arr) {
		cout << i << endl;// i相当于arr中的每一个元素
	}


	return 0;
}
#endif
//------------------------------------------------------------------------------------------------------------------------------------------------------------



































#if 0
//------------------------------------------------------------------------------------------------------------------------------------------------------------
																  //类的继承与派生
class Point {
public:
	int getX()const;
	int getY()const;
	//构造函数
	Point() = default;
	Point(int x, int y);
	//析构函数
	~Point();
private:
	int x, y;
protected:

};


class rec :public Point {//继承方式有三种：public、private、protected，继承后基类的public和protected成员会变成派生类的(继承方式)成员
public:                 //无论是什么继承方式，派生类都无法访问派生过来的private成员，在类内也不能访问，只能通过基类中的函数成员来对private成员进行控制。
	int get_area() const;     //所以说protected在自己的类中和private没区别，但是如果要继承就有区别了。
	int getL() const;
	int getW() const;
	//构造函数(默认继承时不会继承基类的构造函数，除非派生类真的不需要添加什么别的东西。可以使用 using base::base  来继承基类的构造函数)
	rec() = default;
	rec(int x, int y, int w, int l);
	//析构函数(先调用基类的析构函数在调用派生类的析构函数，简单来说就是  各管各的 )
	~rec();
	//复制构造函数
	rec(rec& src);//派生类的对象可以转化成基类的成员，基类的引用。(派生类是对基类的补充，基类是派生类的子集)
private:
	int w, l;//派生类中可以直接写新加的成员，基类的成员不用重复写。
protected:

};


class cube :public rec, private Point {//可以同时对两个类进行继承
public:
	int get_volume();
	int getI() const;
	int getJ() const;
	int getK() const;
	//构造函数
	cube() = default;
	cube(int x, int y, int w, int l, int h);
	//析构函数
	~cube();
private:
	int i, j, k;//当本类中创建的成员和基类的名字重叠时会将基类成员隐藏，只能通过在成员名前加Point::、rec::表示访问哪一个类的成员
	Point o;
	rec front;
	rec side;
	rec top;
protected:

};

int main()
{

	Point p(1, 2);





	return 0;
}
//-----
int Point::getX() const {
	return x;
}
int Point::getY() const {
	return y;
}
Point::Point(int x, int y) :x(x), y(y) {}
Point::~Point() {

}
//-----
int rec::getW()const {
	return w;
}
int rec::getL()const {
	return l;
}
rec::rec(int x, int y, int w, int l) :Point(x, y), w(w), l(l) {
}//创建派生类的对象时会掉用构造函数，首先调用基类的构造函数，然后其余新加的成员按声明的顺序初始化(与初始化列表的顺序无关)
rec::~rec() {

}
//-----
int cube::getI()const {
	return i;
}
int cube::getJ()const {
	return j;
}
int cube::getK()const {
	return k;
}
cube::cube(int x, int y, int i, int j, int k) :Point(x, y), i(i), j(j), k(k) {//不调用rec的自定义构造函数时会调用rec的默认构造函数
	//对正面、侧面。顶面进行初始化--这里就偷个懒不写了
	// 
	// 
	//对正面、侧面。顶面进行初始化--这里就偷个懒不写了
}
//---------------------------------------------------------------------
/*
	有时一个派生类（研究生助教）继承了基类（研究生）和基类（老师），而这两个基类又继承了一个基类（人类）。

	一个人有姓名、身份证号等。所以(研究生助教)就会从(研究生)和(老师)那里各得到一个人类的信息，这就会造成信息的重复，可能会导致信息的错误。

	这时就需要（研究生）和（老师）在继承（人类）的时候在继承方式前加一个关键字 ：virtu  表示虚继承，以此类推一直虚继承到当前类。

	这个（人类）的类叫做最远派生类，（这时候，研究生助教的构造函数就不知要研究生和老师的初始化列表，还需要人类这个类的初始化列表）

	虚继承之后：研究生助教中只会出现一个人类的信息，无论是通过   p->研究生::name、p->老师::name、p->name都访问的是同一个name信息，他们的地址是一样的。
*/
//------------------------------------------------------------------------------------------------------------------------------------------------------------
#endif































//--------------------------------------------------------------------------------------------------------------------------------------------------------------
																//多态性(虚函数与运算符重载)
//--------------------------------------------------------------------虚函数
#if 0
class base {
public:
	virtual void display();//虚函数不能为内联函数，因为内联函数在编译前确定的。
	int val1;
	base();
	~base();              //类中只要有一个纯虚函数，那么这个类就是一个抽象类，不能用该类创建对象。
	virtual int get_area() = 0;//假如base是一个几何图形，想要规范家族 要求所有派生类都有一个求面积的函数，但是几何图形太抽象了无法得到一个统一的面积公式
};                                                                                              //所以定义为纯虚函数，然派生类进行覆盖得到具体的面积函数


class son :public base {
public:                   //override表示就是要进行覆盖，如果因为参数，返回类型不一样造成 没有覆盖 会报错警告
	virtual void display() override;//从基类继承来的虚函数不用加virtual也是虚函数，加了提高可读性。
	int val2;             //在派生类中声明相同的函数叫 覆盖(虚函数) 不叫 隐藏(普通函数) 。
	int* p;
	son();
	~son();//所以如果需要多态性就最好吧析构函数也写成虚函数。
	int get_area()final;//final 表示这个函数很重要，不希望被派生类进行覆盖、修改。
};


int main()
{
	base* arr[10];
	for (int i = 0; i < 10; i++) {
		arr[i] = new son;//利用数组对base继承出来的各种派生类批量操作(向上提升)
	}

	for (int i = 0; i < 10; i++) {
		arr[i]->display();//而只要将需要多种类的对象同时使用的函数声明为虚函数就能在每个类的对象中加一个 虚表指针 ，能保证什么类的对象就调用对应类的函数。

		delete arr[i];//释放时调用析构函数，对于普通函数来说是编译时确定的，也就是说不管什么类型的对象，只要是用base*的指针，那么调用的就是base的析构函数
	}                                                                                                           //那么son对象中的p就没法释放造成内存泄露。



	return 0;
}

base::base() {
	val1 = 666;
}
base::~base() {

}
void base::display() {
	cout << "val1 = " << val1;
}

son::son() {
	val2 = 999;
	p = new int(369);
}
son::~son() {
	delete p;
}
void son::display() {
	cout << "val2 = " << val2;
}
int son::get_area()
{
	return 521;
}
#endif
//-----------------------------------------------------------------------
//-----------------------------------------------------------------------运算符重载
#if 0
class complex {
public:
	complex(double real = 0.0, double imag = 0.0) :real(real), imag(imag) {}
	complex operator +(const complex& right);
	friend complex operator -(const complex& left, const complex& right);

	complex& operator ++();
	complex  operator ++(int);//用int区分前置++和后置++。有int的是后置++。
	friend ostream& operator << (ostream& out, const complex& c);
private:
	double real;
	double imag;
};


int main()
{
	complex a(1, 2);
	complex b(3, 4);
	complex c = a + b;

	cout << a << b;

	return 0;
}
complex complex::operator +(const complex& right) {//c=a+b本质上是c=a.operator +(b)，所以左操作数必须是复数
	return complex(real + right.real, imag + right.imag);
}
complex operator -(const complex& left, const complex& right) {//如果想要一个int + complex就只能声明为普通全局函数了。
	return complex(left.real + right.real, left.imag + right.imag);
}
complex& complex::operator ++() {
	real++;
	imag++;
	return *this;
}
complex  complex::operator ++(int) {
	complex old = *this;//使用默认的复制构造函数
	++*this;
	return old;
}

ostream& operator << (ostream& out, const complex& c) {
	out << '(' << c.real << ',' << c.imag << ')';
	return out;
}
#endif
//-----------------------------------------------------------------------
//------------------------------------------------------------------------------------------------------------------------------------------------------------
























