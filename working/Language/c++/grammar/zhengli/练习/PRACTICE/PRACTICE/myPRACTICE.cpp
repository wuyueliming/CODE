



#include <iostream>
using namespace std;

int main() {

    int n;
    cin >> n;
    int sum = 0;

    // write your code here......
    for (int i = 2; i <= n; i += 2) {
        sum += i;
    }

    cout << sum << endl;

    return 0;
}






#include <iostream>
using namespace std;

int main() {

    int n;
    cin >> n;
    long long factorial = 1;

    // write your code here......
    for (int i = 1; i <= n; i++) {
        factorial *= i;
    }

    cout << factorial << endl;

    return 0;
}



#include <iostream>
using namespace std;


int  is_water(int num) {
    int x = num;
    int sum = 0;
    int d;
    do {
        d = x % 10;
        x /= 10;
        sum += d * d * d;
    } while (x);
    return sum == num ? 1 : 0;
}

int main() {

    // write your code here......
    for (int i = 100; i < 1000; i++) {
        if (is_water(i)) {
            cout << i << endl;
        }
    }


    return 0;
}





#include <iostream>
using namespace std;

int main() {

    int n;
    cin >> n;

    // write your code here......
    for (int i = 1; i <= n; i++) {
        printf("%d * %d = %d", 1, i, i);
        for (int j = 2; j <= i; j++) {
            printf("    %d * %d = %d", j, i, i * j);
        }
        printf("\n");
    }



    return 0;
}






#include <iostream>
using namespace std;

int main() {

    // write your code here......
    long d = 0;
    long sum = 0;
    for (int i = 0; i < 10; i++) {
        d *= 10;
        d += 9;
        sum += d;
    }
    cout << sum;

    return 0;
}






#include <iostream>
#include <iomanip>
using namespace std;

int main() {

    // 下落的高度和落地的次数
    double h;
    int n;

    cin >> h;
    cin >> n;

    // write your code here......
    float dist = h;
    h /= 2;
    for (int i = 1; i < n; i++) {
        dist += 2 * h;
        h /= 2;
    }
    printf("%.1f %.1f", dist, h);

    return 0;
}







#include <iostream>
using namespace std;
#include<cmath>

int is_prime(int x) {
    if (x == 2) {
        return 1;
    }
    else {
        for (int i = 2; i <= sqrt(x); i++) {
            if (x % i == 0)return 0;
        }
    }
    return 1;
}

int main() {

    // write your code here......
    int num;
    cin >> num;
    if (is_prime(num)) {
        cout << "是质数";
    }
    else {
        cout << "不是质数";
    }

    return 0;
}




#include <iostream>
using namespace std;

int main() {

    int arr[6] = { 0 };
    int len = sizeof(arr) / sizeof(int);

    for (int i = 0; i < len; i++) {
        cin >> arr[i];
    }

    // write your code here......
    int max = arr[0];
    int min = arr[0];
    for (int i : arr) {
        if (i > max)max = i;
        if (i < min)min = i;
    }
    cout << min << ' ' << max;

    return 0;
}






#include <iostream>
using namespace std;

int main() {

    int arr[6] = { 0 };

    int len = sizeof(arr) / sizeof(int);

    for (int i = 0; i < len; i++) {
        cin >> arr[i];
    }

    cout << "[";
    for (int i = 0; i < len; i++) {
        if (i == len - 1) {
            cout << arr[i] << "]" << endl;
            break;
        }
        cout << arr[i] << ", ";
    }

    // write your code here......
    int L = 0;
    int R = len - 1;
    while (R > L) {
        int t = arr[R];
        arr[R] = arr[L];
        arr[L] = t;
        R--;
        L++;
    }



    cout << "[";
    for (int i = 0; i < len; i++) {
        if (i == len - 1) {
            cout << arr[i] << "]" << endl;
            break;
        }
        cout << arr[i] << ", ";
    }

    return 0;
}





#include <iostream>
using namespace std;

int main() {

    int arr[6] = { 0 };
    int len = sizeof(arr) / sizeof(int);

    for (int i = 0; i < len; i++) {
        cin >> arr[i];
    }

    // write your code here......
    for (int i = 0; i < len - 1; i++) {
        for (int j = 0; j < len - 1 - i; j++) {
            if (arr[j] > arr[j + 1]) {
                int t = arr[j];
                arr[j] = arr[j + 1];
                arr[j + 1] = t;
            }
        }
    }

    for (int i = 0; i < len; i++) {
        cout << arr[i] << ' ';
    }


    return 0;
}






#include <iostream>
using namespace std;

int main() {

    int arr[6] = { 0 };
    int len = sizeof(arr) / sizeof(int);

    for (int i = 0; i < len; i++) {
        cin >> arr[i];
    }

    // write your code here......
    int max;
    for (int i = 0; i < len - 1; i++) {
        int j;
        max = 0;
        for (j = 0; j < len - i; j++) {
            if (arr[j] > arr[max]) {
                max = j;
            }
        }
        int t = arr[max];
        arr[max] = arr[len - 1 - i];
        arr[len - 1 - i] = t;
    }


    for (int i = 0; i < len; i++) {
        cout << arr[i] << ' ';
    }

    return 0;
}




#include <iostream>
using namespace std;

int main() {

    int arr[4][3] = {
        // write your code here......
        {22,66,44},{77,33,88},{25,45,65},{11,66,99}
    };

    int sum = 0;

    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 3; j++) {
            sum += arr[i][j];
        }
    }

    cout << sum << endl;

    return 0;
}





#include <iostream>
#include <string>
using namespace std;

int main() {

    string s1, s2;
    getline(cin, s1);
    getline(cin, s2);

    // write your code here......
    cout << s1 + s2;

    return 0;
}







#include <iostream>
#include <string>
using namespace std;

struct student {
    // write your code here......
    string name;
    int age;
    double height;
};

int main() {

    // write your code here......
    student st;
    cin >> st.name >> st.age >> st.height;
    cout << st.name << " " << st.age << " " << st.height << endl;

    return 0;
}







#include <iostream>
using namespace std;

int main() {

    int arr[6] = { 0 };
    int* ptr = arr;

    int len = sizeof(arr) / sizeof(int);

    for (int i = 0; i < len; i++) {
        cin >> arr[i];
    }

    // write your code here......
    for (int i = 0; i < len; i++) {
        cout << ptr[i] << ' ';
    }

    return 0;
}




#include <iostream>
using namespace std;

int main() {

    char str[100] = { 0 };
    cin.getline(str, sizeof(str));

    // write your code here......
    char* ch = str;
    int cnt = 0;
    while ((*ch) != '\0') {
        cnt++;
        ch++;
    }
    cout << cnt;

    return 0;
}






#include <iostream>
using namespace std;

int main() {

    char str[30] = { 0 };
    cin.getline(str, sizeof(str));

    int m;
    cin >> m;

    // write your code here......
    char copy[30];
    int j = 0;
    for (int i = m - 1; str[i] != '\0'; i++) {
        copy[j++] = str[i];
    }
    copy[j] = '\0';

    cout << copy;

    return 0;
}




#include <iostream>
using namespace std;

int main() {

    int n;
    cin >> n;

    // write your code here......
    int* arr = new int[n];
    for (int i = 0; i < n; i++) {
        arr[i] = n + i;
    }
    for (int i = 0; i < n; i++) {
        cout << arr[i] << ' ';
    }

    return 0;
}



#include <iostream>
using namespace std;

void func(int* p, int n);

int main() {

    int arr[6] = { 0 };
    for (int i = 0; i < 6; i++) {
        cin >> arr[i];
    }

    func(arr, 6);

    for (int i = 0; i < 6; i++) {
        if (i == 5) {
            cout << arr[i] << endl;
        }
        else {
            cout << arr[i] << " ";
        }
    }

    return 0;
}

void func(int* p, int n) {

    // write your code here......
    for (int i = 0; i < n - 1; i++) {
        int j;
        for (j = 0; j < n - 1 - i; j++) {
            if (p[j] == 0) {
                int t = p[j];
                p[j] = p[j + 1];
                p[j + 1] = t;
            }
        }
    }

}







#include <iostream>
using namespace std;

int mystrcmp(const char* src, const char* dst);

int main() {

    char s1[100] = { 0 };
    char s2[100] = { 0 };

    cin.getline(s1, sizeof(s1));
    cin.getline(s2, sizeof(s2));

    int ret = mystrcmp(s1, s2);

    cout << ret << endl;

    return 0;
}

int mystrcmp(const char* src, const char* dst) {
    const char* p1 = src;
    const char* p2 = dst;
    // write your code here......
    while (*p1 == *p2 && *p1 != '\0' && *p2 != '\0') {
        p1++;
        p2++;
    }
    if (*p1 == '\0' && *p2 == '\0') {
        return 0;
    }
    return *p1 - *p2 > 0 ? 1 : -1;

}








#include <iostream>
using namespace std;

// write your code here......


int main() {

    int m, n;
    cin >> m;
    cin >> n;

    // write your code here......
    int* pm = &m;
    int* pn = &n;
    int t = *pm;
    *pm = *pn;
    *pn = t;

    cout << m << " " << n << endl;

    return 0;
}








#include <iostream>
#include <cstring>
using namespace std;

int main() {

    char str[100] = { 0 };
    char substr[100] = { 0 };

    cin.getline(str, sizeof(str));
    cin.getline(substr, sizeof(substr));

    int count = 0;
    int len = strlen(substr);
    char* t = str;
    // write your code here......
    while (t = strstr(t, substr)) {
        if (t)t += 1;
        count++;
    }

    cout << count << endl;

    return 0;
}




#include <iostream>
#include <string>
#include <cctype>
using namespace std;

int main() {

    string str;
    getline(cin, str);


    int whitespace = 0;
    int digits = 0;
    int chars = 0;
    int others = 0;

    // write your code here......
    for (int i = 0; i < str.size(); i++) {
        if (isspace(str[i]))whitespace++;
        else if (isdigit(str[i]))digits++;
        else if (isupper(str[i]) || islower(str[i]))chars++;
        else others++;
    }

    cout << "chars : " << chars
        << " whitespace : " << whitespace
        << " digits : " << digits
        << " others : " << others << endl;

    return 0;
}






#include <iostream>
using namespace std;

long long factorial(int n);

int main() {

    int n;
    cin >> n;

    cout << factorial(n) << endl;

    return 0;
}

long long factorial(int n) {

    // write your code here......
    if (n == 1) {
        return 1;
    }
    else {
        return factorial(n - 1) * n;
    }

}




#include <iostream>
using namespace std;

int getSum(int n);

int main() {

    int n;
    cin >> n;

    cout << getSum(n) << endl;

    return 0;
}

int getSum(int n) {

    // write your code here......
    if (n == 1 || n == 2) {
        return 1;
    }
    else {
        return getSum(n - 1) + getSum(n - 2);
    }

}





#include <iostream>
using namespace std;

// write your code here......
void swap(int& a, int& b) {
    int t = a;
    a = b;
    b = t;
}


int main() {

    int m, n;
    cin >> m;
    cin >> n;

    // write your code here......
    swap(m, n);

    cout << m << " " << n << endl;

    return 0;
}








#include <iostream>
using namespace std;

class Cube {

    //定义属性
private:
    int length, width, height;

    //定义方法
public:
    //构造方法
    Cube() {}

    //设置长、宽、高
    void setLength(int l) {
        length = l;
    }

    void setWidth(int w) {
        width = w;
    }

    void setHeight(int h) {
        height = h;
    }

    //获取长、宽、高
    int getLength() {
        return length;
    }

    int getWidth() {
        return width;
    }

    int getHeight() {
        return height;
    }

    //计算表面积（6个面的面积之和）
    int getArea() {
        return 2 * (length * width + length * height + width * height);
    }

    //计算体积（长*宽*高）
    int getVolume() {
        return length * width * height;
    }

};

int main() {

    int length, width, height;
    cin >> length;
    cin >> width;
    cin >> height;

    Cube c;
    c.setLength(length);
    c.setWidth(width);
    c.setHeight(height);

    cout << c.getLength() << " "
        << c.getWidth() << " "
        << c.getHeight() << " "
        << c.getArea() << " "
        << c.getVolume() << endl;

    return 0;
}








#include <iostream>
using namespace std;
#include<cmath>
// 点类
class Pointer {

private:
    int x;  // x 坐标
    int y;  // y 坐标

public:
    void setX(int x) {
        this->x = x;
    }

    int getX() {
        return x;
    }

    void setY(int y) {
        this->y = y;
    }

    int getY() {
        return y;
    }

};

// 圆类
class Circle {

private:
    Pointer center; // 圆心
    int radius; // 半径

public:
    void setCenter(int x, int y) {
        center.setX(x);
        center.setY(y);
    }

    void setRadius(int radius) {
        this->radius = radius;
    }

    // write your code here......
    void isPointerInCircle(Pointer p) {
        int dx = p.getX() - center.getX();
        int dy = p.getY() - center.getY();
        int d = sqrt(dx * dx + dy * dy);
        int sign = d - radius;
        if (sign == 0) {
            cout << "on";
        }
        else if (sign > 0) {
            cout << "out";
        }
        else if (sign < 0) {
            cout << "in";
        }
    }

};

int main() {

    // 键盘输入点的坐标
    int x, y;
    cin >> x;
    cin >> y;

    // 创建一个点
    Pointer p;
    p.setX(x);
    p.setY(y);

    // 创建一个圆
    Circle c;
    c.setCenter(5, 0);
    c.setRadius(5);

    // 判断点和圆的关系
    c.isPointerInCircle(p);

    return 0;
}





#include <iostream>
#include <string>

using namespace std;

// Person类
class Person {
public:
    string name;    // 姓名
    int age;    // 年龄

    // write your code here......
    Person(string name, int age) :name(name), age(age) {};

    void showPerson() {
        cout << name << " " << age << endl;
    }
};

int main() {

    string name;
    int age;

    cin >> name;
    cin >> age;

    Person p(name, age);
    p.showPerson();

    return 0;
}







#include <iostream>
#include <cstring>
#pragma warning(disable : 4996)
using namespace std;

class Person {

public:
    char* name; // 姓名
    int age;    // 年龄

    Person(const char* name, int age) {
        this->name = new char[strlen(name) + 1];
        strcpy(this->name, name);
        this->age = age;
    }

    // write your code here......
    Person(const Person& src) {
        int len = strlen(src.name);
        name = new char[len + 1];
        strcpy(name, src.name);
        age = src.age;
    }

    void showPerson() {
        cout << name << " " << age << endl;
    }

    ~Person() {
        if (name != nullptr) {
            delete[] name;
            name = nullptr;
        }
    }

};

int main() {

    char name[100] = { 0 };
    int age;

    cin >> name;
    cin >> age;

    Person p1(name, age);
    Person p2 = p1;

    p2.showPerson();

    return 0;
}






#include <iostream>
using namespace std;

class Person {
    // write your code here......
    friend void showAge(Person& p);

public:
    Person(int age) {
        this->age = age;
    }

private:
    int age;
};

void showAge(Person& p) {
    cout << p.age << endl;
}

int main() {

    Person p(10);
    showAge(p);

    return 0;
}




#include <iostream>
using namespace std;

class Time {

public:
    int hours;      // 小时
    int minutes;    // 分钟

    Time() {
        hours = 0;
        minutes = 0;
    }

    Time(int h, int m) {
        this->hours = h;
        this->minutes = m;
    }

    void show() {
        cout << hours << " " << minutes << endl;
    }

    // write your code here......
    Time operator +(const Time& R) {
        Time t;
        t.minutes = (minutes + R.minutes);
        t.hours = hours + R.hours;
        if (t.minutes >= 60) {
            t.minutes %= 60;
            t.hours++;
            if (t.hours >= 24) {
                t.hours %= 24;
            }
        }
        return t;
    }

};

int main() {

    int h, m;
    cin >> h;
    cin >> m;

    Time t1(h, m);
    Time t2(2, 20);

    Time t3 = t1 + t2;
    t3.show();

    return 0;
}




#include <iostream>
using namespace std;

class Base {

private:
    int x;
    int y;

public:
    Base(int x, int y) {
        this->x = x;
        this->y = y;
    }

    int getX() {
        return x;
    }

    int getY() {
        return y;
    }

};

class Sub : public Base {

private:
    int z;

public:
    Sub(int x, int y, int z) :Base(x, y), z(z) {
        // write your code here

    }

    int getZ() {
        return z;
    }

    int calculate() {
        return Base::getX() * Base::getY() * this->getZ();
    }

};

int main() {

    int x, y, z;
    cin >> x;
    cin >> y;
    cin >> z;
    Sub sub(x, y, z);
    cout << sub.calculate() << endl;

    return 0;
}






#include <iostream>
using namespace std;

class Base {

private:
    int x;
    int y;

public:
    Base(int x, int y) {
        this->x = x;
        this->y = y;
    }

    int getX() {
        return x;
    }

    int getY() {
        return y;
    }

    void calculate() {
        cout << getX() * getY() << endl;
    }

};

class Sub : public Base {
    // write your code here......
public:
    Sub(int x, int y) : Base(x, y) {}

    void calculate() {  //计算除法的函数
        if (Base::getY() == 0) //先判断除数是否为0
            cout << "Error" << endl;
        else //再输出商
            cout << Base::getX() / Base::getY() << endl;
    }
};

int main() {

    int x, y, z;
    cin >> x;
    cin >> y;
    Sub sub(x, y);
    sub.calculate();

    return 0;
}





#include <iostream>
using namespace std;

class BaseCalculator {
public:
    int m_A;
    int m_B;
    // write your code here......
    virtual int getResult();
};

// 加法计算器类
class AddCalculator : public BaseCalculator {
    // write your code here......
    int getResult()
    {
        return m_A + m_B;
    }
};

// 减法计算器类
class SubCalculator : public BaseCalculator {
    // write your code here......
    int getResult()
    {
        return m_A - m_B;
    }
};


int main() {

    BaseCalculator* cal = new AddCalculator;
    cal->m_A = 10;
    cal->m_B = 20;
    cout << cal->getResult() << endl;
    delete cal;

    cal = new SubCalculator;
    cal->m_A = 20;
    cal->m_B = 10;
    cout << cal->getResult() << endl;
    delete cal;

    return 0;
}





#include <iostream>
// write your code here......
#include<vector>



using namespace std;

int main() {

    // write your code here......
    vector<int> arr(5);
    vector<int>::iterator p;
    for (p = arr.begin(); p != arr.end(); p++) {
        cin >> *p;
    }
    for (p = arr.begin(); p != arr.end(); p++) {
        cout << *p << ' ';
    }
    cout << endl;

    vector<int>::reverse_iterator q;
    for (q = arr.rbegin(); q != arr.rend(); q++) {
        cout << *q << ' ';
    }


    return 0;
}






#include <iostream>
#include <deque>
using namespace std;

class Guest {
public:
    string name;
    bool vip;

    Guest(string name, bool vip) {
        this->name = name;
        this->vip = vip;
    }
};

int main() {

    Guest guest1("张三", false);
    Guest guest2("李四", false);
    Guest vipGuest("王五", true);
    deque<Guest> deque;

    // write your code here......
    deque.push_back(vipGuest);
    deque.push_back(guest1);
    deque.push_back(guest2);


    for (Guest g : deque) {
        cout << g.name << " ";
    }

    return 0;
}







#include <iostream>
// write your code here......
#include<set>
using namespace std;

int main() {

    char str[100] = { 0 };
    cin.getline(str, sizeof(str));

    // write your code here......
    set<char> a;
    for (int i = 0; str[i] != '\0'; i++) {
        a.insert(str[i]);
    }
    set<char>::iterator p;
    for (p = a.begin(); p != a.end(); p++) {
        cout << *p;
    }

    return 0;
}








#include <iostream>
#include <map>
using namespace std;

int main() {
    char str[100] = { 0 };
    cin.getline(str, sizeof(str));
    map<char, int> mp;
    for (int i = 0; str[i] != '\0'; i++) { //遍历字符串
        if (isalpha(str[i])) //对于是字母的字符
            mp[str[i]]++; //加入哈希表，并统计次数
    }
    for (auto iter = mp.begin(); iter != mp.end(); iter++) //遍历哈希表
        cout << iter->first << ":" << iter->second << endl; //输出key与value
    return 0;
}




#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

//元素和元素之间使用空格隔开
void print(int x) {
    cout << x << " ";
}

int main() {

    int num;
    vector<int> v;
    for (int i = 0; i < 5; i++) {
        cin >> num;
        v.push_back(num);
    }

    //按从大到小方式排序
    sort(v.begin(), v.end(), greater<int>());
    //遍历容器中所有元素，并按print方法指定格式输出
    for_each(v.begin(), v.end(), print);

    return 0;
}





#include <iostream>
#include <cstring>
using namespace std;

int main() {

    int letter = 0;
    int digit = 0;
    int space = 0;
    int other = 0;

    char buf[1024] = { 0 };
    cin.getline(buf, sizeof(buf));

    // write your code here......
    for (int i = 0; buf[i] != '\0'; i++) { //遍历字符串到'\0'为止
        char c = buf[i];
        if (c >= 'a' && c <= 'z' || c >= 'A' && c <= 'Z') //大小写字母
            letter++;
        else if (c >= '0' && c <= '9') //数字
            digit++;
        else if (c == ' ')  //空格
            space++;
        else //其他字符
            other++;
    }
    cout << "letter:" << letter << " digit:" << digit << " space:" << space << " other:" << other << endl;

    return 0;
}





#include <iostream>
#include <string.h>
#include <string>
#include <cstdlib>
using namespace std;

int main() {

    char str[100] = { 0 };
    cin.getline(str, sizeof(str));
    string op = "";
    string num1 = "";
    string num2 = "";
    int space = 0;
    for (int i = 0; str[i] != '\0'; i++) {
        if (str[i] == ' ') {
            space++;
            continue;
        }
        else if (space == 0) //第一空格之前都是操作符
            op += str[i];
        else if (space == 1) //第一二个空格之间，为第一个数字
            num1 += str[i];
        else if (space == 2)
            num2 += str[i]; //第二个空格之后，为第二个数字
    }
    int x = stoi(num1); //字符串转数组
    int y = stoi(num2);
    //分情况计算加减乘除
    if (strcasecmp(op.c_str(), "add") == 0)
        cout << x + y << endl;
    else if (strcasecmp(op.c_str(), "sub") == 0)
        cout << x - y << endl;
    else if (strcasecmp(op.c_str(), "mul") == 0)
        cout << x * y << endl;
    else if (strcasecmp(op.c_str(), "div") == 0) {
        if (y == 0) //除数为0
            cout << "Error" << endl;
        else
            cout << (double)x / y << endl;
    }
    return 0;
}





#include <iostream>
#include <string>
using namespace std;

string toHexString(int n);

int main() {

    int n;
    cin >> n;

    string hexStr = toHexString(n);
    cout << hexStr << endl;

    return 0;
}

string toHexString(int n) {
    //定义字符串变量，用于记录最终结果
    string res = "";
    while (n != 0) {
        //计算当前对16取余的结果
        int mod = n % 16;
        //如果是0-9，则对应字符'0'-'9'
        if (mod >= 0 && mod <= 9) {
            char c = mod + '0';
            //将字符加在res前面
            res = c + res;
        }
        //如果是10-15，则对应字符'A'-'F'
        else {
            char c = mod - 10 + 'A';
            //将字符加在res前面
            res = c + res;
        }
        n = n / 16;
    }
    return res;
}
