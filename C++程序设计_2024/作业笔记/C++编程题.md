# 编程题目

## 作业一：

### 1.测试c++

倒序输出从控制台输入的n个整数

输入格式:

第一行输入一个数n，代表行数
依次输入n个整数

输出格式:

将n个整数倒序输出

输入样例:

```in
3
1 2 3
```

输出样例:

```out
321
```

code

```c++
#include <iostream>
using namespace std;

int main() {
	int n;
	int a[100];
	cin >> n;
	for (int i = 0; i < n; i++) {
		cin >> a[i];
	}
	for (int i = n - 1; i >= 0; i--) {
		cout << a[i];
	}
	return 0;
}
```

### 2.输出星号组成的三角形

从键盘输入一个整数n，然后输出一个由星号“*”组成的n行的三角形。

输入格式:

例如：输入5

输出格式:

```
*
```

输入样例:

```in
5
```

输出样例:

```out
    *
   ***
  *****
 *******
*********
```

code

```c++
#include <iostream>
using namespace std;

void CharPyramid(int n, char ch) {
    int max_width = n;// 金字塔底部的宽度
    for (int i = 1; i <= n; i++) {// 控制金字塔的行数
        int name_chars = 2*i-1;// 当前行的字符数量
        int name_spaces = max_width - name_chars/2-1;
        // 打印当前行的空格
        for (int j = 0; j < name_spaces; j++) {
            printf(" ");
        }
        // 打印当前行的字符
        for (int j = 1; j <= name_chars; j++) {
            printf("%c", ch);
        }
        // 换行
        printf("\n");
    }
}

int main() {
    int n;
    CharPyramid(5,'*');
    return 0;
}
```

### 3.橡皮泥 -《C++编程基础及应用》

将两块球形橡皮泥揉在一起，捏成一个正方体。请编程，完成下述功能：

从键盘读入第1个球形橡皮泥的直径，该直径为浮点数；
从键盘读入第2个球形橡皮泥的直径，该直径仍为浮点数；
求正方体的边长，并保留两位小数输出;

输入格式:

第一个球的直径
第二个球的直径

输出格式:

请参考输出样例。

输入样例:

```in
3.2
5.553
```

输出样例:

```out
Side length of cube: 4.74
```

提示：圆球的体积 V = 4/3 * π r³

正确code

```c++
#define _CRT_SECURE_NO_WARNINGS  1
#include <iostream>
#include <cmath>
#include <iomanip>
using namespace std;



int main() {

    double c, d, a, b;
    scanf("%lf %lf", &c, &d);
    a = c / 2.0;
    b = d / 2.0;
    double s;
    s = 4 / 3.0 * 3.14159 * (a * a * a + b * b * b);
    double r;
    r = pow(s, 1 / 3.0);
    printf("Side length of cube: %.2lf", r);
    return 0;

}
```

我的错误code

```c++
#define _CRT_SECURE_NO_WARNINGS  1
#include <iostream>
#include <cmath>
#include <iomanip>
using namespace std;



int main() {
	double pi = 3.14159;
	double d1, d2;
	double vbool;

	cin >> d1 >> d2;
	
	vbool = (4 / 3.0) * pi * pow(d1/2.0, 3) + (4 / 3) * pi * pow(d2/2.0, 3);
	cout << setprecision(2)<<pow(vbool, 1/3.0);
}
```

#### 有待分析

## 作业二

### 1.记忆法-权值函数Function

**记忆法就是用桶排序记忆已经遍历过的输入值**

题目描述
对于一个递归函数w(a,b,c)w(a,b,c)
• 如果a≤0 or b≤0 or c≤0就返回值1.
• 如果a>20 or b>20 or c>20就返回w(20,20,20)
• 如果a<b并且b<c 就返回w(a,b,c−1)+w(a,b−1,c−1)−w(a,b−1,c)
• 其它的情况就返回w(a−1,b,c)+w(a−1,b−1,c)+w(a−1,b,c−1)−w(a−1,b−1,c−1)
这是个简单的递归函数，但实现起来可能会有些问题。当a,b,c均为15时，调用的次数将非常的多。你要想个办法才行.(提示：采用记忆法）
比如 w(30,−1,0)既满足条件1又满足条件2,这种时候我们就按最上面的条件来算，所以答案为1

输入格式:

会有若干行。
并以−1,−1,−1结束。
保证输入的数在[[−9223372036854775808,9223372036854775807]之间，并且是整数。

输出格式:

输出若干行，每一行格式：
w(a, b, c) = ans //注意空格。。

输入样例:

在这里给出一组输入。例如：

```in
1 1 1
2 2 2
-1 -1 -1
```

输出样例:

在这里给出相应的输出。例如：

```out
w(1, 1, 1) = 2
w(2, 2, 2) = 4
```

code

```c++
#include<iostream>
#include<cstring>
using namespace std;
long long arr[21][21][21];
long long w(long long a, long long b, long long c);
long long fw(long long a, long long b, long long c)//如果是已经记忆了的abc,则直接返回数组值
{
	if (arr[a][b][c] == 0)
		return w(a, b, c);
	else
		return arr[a][b][c];
}
long long w(long long a, long long b, long long c)
{
	if (a <= 0 || b <= 0 || c <= 0)
		return 1;
	else if (a > 20 || b > 20 || c > 20)
		return w(20, 20, 20);//这里不能赋值，而是直接返回，因为数组下标不能越界
	else if (a < b && b < c)
		arr[a][b][c] = (fw(a, b, c - 1) + fw(a, b, c - 1) - fw(a, b - 1, c));
	else
		arr[a][b][c] = (fw(a - 1, b, c) + fw(a - 1, b - 1, c) + fw(a - 1, b, c - 1) - fw(a - 1, b - 1, c - 1));
	return arr[a][b][c];//先赋值，最后return，而不是直接return，以实现记忆化搜索
}
int main()
{
	memset(arr, 0, sizeof(arr));
	long long a, b, c;
	while (1)
	{
		cin >> a >> b >> c;
		if (a == -1 && b == -1 && c == -1)
			break;
		printf("w(%lld, %lld, %lld) = %lld\n", a, b, c, w(a, b, c));
	}
	return 0;
}
```

### 2.字符统计

程序实现的功能是从键盘读入一行字符（包括空格），统计输出该行字符串的数字字符个数n1、大写字母字符个数n2、小写字母字符个数n3,空格字符的个数n4,其他字符n5;
例如：输入 : I Am A Student. I Have 20 Years Old！
输出： n1=2 n2=8 n3=16 n4=8 n5=3
。

输入格式:

输入一行字符串（可能含有空格字符串），以回车键为结束符。

输出格式:

输出一行n1,n2,n3,n4,n5的值。例如：各个数之间有两个空格。

输入样例:

在这里给出一组输入。例如：

```in
Are You 20 Years Old? No,No......
```

输出样例:

在这里给出相应的输出。例如：

```out
n1=2  n2=6  n3=12  n4=5  n5=8
```

right code

```c++
2、
#include <iostream>
using namespace std;
#include <string>
int main()
{
	string a;
	getline(cin, a);
	int n1=0,n2=0,n3=0,n4=0,n5=0;
	for (int i=0;i<a.length();i++)
	{
		if(a[i]<='9'&& a[i]>='0')
		{
			n1++;
		}
		else if(a[i]<='Z'&& a[i]>='A')
		{
			n2++;
		}
		else if(a[i]<='z'&& a[i]>='a')
		{
			n3++;
		}
		else if(a[i]==' ')
		{
			n4++;
		}
		else
		{
			n5++;
		}
	}
	cout<<"n1="<<n1<<"  ";
	cout<<"n2="<<n2<<"  ";
	cout<<"n3="<<n3<<"  ";
	cout<<"n4="<<n4<<"  ";
	cout<<"n5="<<n5<<endl;
}
```

my wrong code

![](E:\programme\小笔记\assets_c++\2024-03-09 14 06 31.png)

```c++
#include <stdio.h>
#include <ctype.h>
#include <string.h>

void countCharacters(const char* str) {
    int SmallCount = 0;     // 小写字母个数
    int LargeCount = 0;     // 大写字母个数
    int digitCount = 0;      // 数字个数
    int spaceCount = 0;      // 空格个数
    int otherCount = 0;      // 其他字符个数


    size_t length = strlen(str);
    for (size_t i = 0; i < length; i++) {
        char ch = str[i];
        if ('a'<=ch&&'z'>=ch) {
            SmallCount++;
        }
        else if ( 'A' <= ch && 'Z' >= ch) {
            LargeCount++;
        }
        else if (isdigit(ch)) {
            digitCount++;
        }
        else if (isspace(ch)) {
            spaceCount++;
        }
        else {
            otherCount++;
        }
    }

    printf("n1=%d  n2=%d  n3=%d  n4=%d  n5=%d\n",digitCount,LargeCount,SmallCount ,spaceCount, otherCount);
}

int main() {
    char input[101];  // 存储输入字符串，最多不超过100个字符

    // 持续读取输入，直到遇到文件结束符
    while (fgets(input, sizeof(input), stdin) != NULL) {
        // 调用函数统计字符个数
        countCharacters(input);
    }

    return 0;
}

```



## 作业三：

### 1.函数重载-排序（数据类型不同）

用同一个函数名对n（n<=10）个数据进行从小到大排序，数据类型可以是整数、浮点数，用函数重载实现

输入格式:

输入n 例如 3
输入n个整数，例如 10 8 9
输入n个浮点数 例如 10.23 5.16 7.99

输出格式:

输出n个整数的升序排列：8 9 10
以空格间隔，并以空格结尾
换行，输出n个浮点数的升序排列：5.16 7.99 10.23
以空格间隔，并以空格结尾

输入样例:

在这里给出一组输入。例如：

```in
3
10 8 9
10.23 5.16 7.89
```

输出样例:

在这里给出相应的输出。例如：

```out
8 9 10 
5.16 7.89 10.23 
```

```c++
#include<iostream>
using namespace std;

void sort(int a[],int n) {
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n - i - 1; j++) {
            if (a[j] > a[j + 1]) {
                int temp = a[j];
                a[j] = a[j + 1];
                a[j + 1] = temp;
            }
        }
    }
    for (int i = 0; i < n; i++) {
        cout << a[i] << " ";
    }
    cout << endl;
}

void sort(float a[],int n) {
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n - i - 1; j++) {
            if (a[j] > a[j + 1]) {
                float temp = a[j];
                a[j] = a[j + 1];
                a[j + 1] = temp;
            }
        }
    }
    for (int i = 0; i < n; i++) {
        cout << a[i] << " ";
    }
    cout << endl;
}


int main()
{
    int n;
    int a[10];
    float b[10];
    cin >> n;
    for (int i = 0; i < n; i++) {
        cin >> a[i];
    }
    for (int i = 0; i < n; i++) {
        cin >> b[i];
    }
    sort(a,n);
    sort(b,n);
    return 0;
}
```





## 作业四：

### 1.Tree类的构造函数和成员函数（函数声明）

定义一个Tree（树）类，有成员ages（树龄），不带参数的构造函数对ages初始化为1，成员函数grow(int years)对ages加上years，age()显示tree对象的ages的值。

Tree类声明如下：

```c++
class Tree {
public:
    Tree();//构造函数
    void grow(int years);//对数龄ages加上years
    void age();//显示数龄ages的值
private:
    int ages;//树龄
};
```

请实现Tree类的构造函数和成员函数。

裁判测试程序样例：

```c++
#include <iostream>
using namespace std;

class Tree {
public:
    Tree();//构造函数
    void grow(int years);//对数龄ages加上years
    void age();//显示数龄ages的值
private:
    int ages;//树龄
};

int main()
{
    Tree tree;
    int years;
    cin >> years;
    tree.grow(years);
    tree.age();

    return 0;
}

/* 你的代码将被嵌在这里 */
```

输入样例：

```in
30
```

输出样例：

```out
31
```



code

```c++
#include <iostream>
using namespace std;

class Tree {
public:
    Tree();//构造函数
    void grow(int years);//对数龄ages加上years
    void age();//显示数龄ages的值
private:
    int ages;//树龄
};

int main()
{
    Tree tree;
    int years;
    cin >> years;
    tree.grow(years);
    tree.age();

    return 0;
}

/* 你的代码将被嵌在这里 */

Tree::Tree() {
    ages = 1;
}

void Tree::grow(int years) {
    ages += years;
}

void Tree::age() {
    cout << ages << endl;
}
```



### 2.设计一个矩形类Rectangle(构造函数测试)

设计一个矩形类Rectangle并创建测试程序（C++）

设计一个名为Rectangle的矩形类，这个类包括：两个名为width和height的double数据域，它们分别表示矩形的宽和高。width和height的默认值都为1.该类包括矩形类的无参构造函数（默认构造函数）；一个width和height为指定值的矩形构造函数；一个名为getArea( )的函数返回矩形的面积；一个名为getPerimeter( )的函数返回矩形的周长。请实现这个类。编写一个测试程序，创建一个Rectangle对象，从键盘输入矩形的宽和高，然后输出矩形的面积和周长。

输入格式:

3.5 35.9（第一个数表示矩形的宽，第二个数表示矩形的高，中间是空间分隔。）

输出格式:

125.65 （第一行输出矩形的面积）
78.8 （第二行输出矩形的周长）

输入样例:

```in
3.5 35.9
```

输出样例:

```out
125.65
78.8
```

code

```c++
#include <iostream>
using namespace std;

class Rectangle {
public:
    Rectangle();
    float getArea(float width, float heigth);
    float getPerimeter(float width, float heigth);
private:
    float width;
    float height;
};


/* 你的代码将被嵌在这里 */
Rectangle::Rectangle() {
    width = 1.0;
    height = 1.0;
}

float Rectangle::getArea(float width,float height) {
    return width * height;
}

float Rectangle::getPerimeter(float width, float height) {
    return (width + height) * 2;
}




int main()
{
    Rectangle r;
    float w;
    float h;
    cin >> w >> h;
    cout << r.getArea(w, h) << endl;
    cout << r.getPerimeter(w, h) << endl;
    

    return 0;
}
```

### 3.定义一个Time类（string转换int）

定义一个时间类，能够提供和设置由时、分、秒组成的时间，并按照如下的格式输出时间：
08-09-24
12-23-59

输入格式:

请在这里写输入格式。例如：
12 8 9
8 24 59

输出格式:

请在这里描述输出格式。例如：
12-08-09
08-24-59

输入样例:

在这里给出一组输入。例如：

```in
8 9 24
```

输出样例:

在这里给出相应的输出。例如：

```out
08-09-24
```

code

```c++
#include <iostream>
#include <string>
using namespace std;

class Time {
public:
    string check(int num);
    void outTime(int h, int m, int s);
private:
    int h;
    int m;
    int s;
};

string Time::check(int num) {
    if (num < 10) {
        return "0" + to_string(num);
    }
    return to_string(num);
}

void Time::outTime(int h, int m, int s) {
    cout << check(h) << "-" << check(m) << "-" << check(s) << endl;
}


int  main() {

    Time T;
    int h, m, s;
    cin >> h >> m >> s;
    //cout << T.check(h);
    T.outTime(h, m, s);
    return 0;
}
```



### 4.成员函数的选择调用一一常成员函数

类中的常对象选择调用常成员函数。语法要点: 如果将一个对象说明为常对象，则通过该常对象只能调用它的常成员函数,而不能调用其他成员函数。补充完整复数类的定义（复数类Complex,数据成员：构造函数，以常成员函数重载的输出函数。数据成员有实部与虚部）使得程序的输出结果符合题意的输出结果。
class Complex
{ public:
/***\**\*\*\*补充完整类的定义\*\*\*\*\****/

```
         /***********************************/
```

private:
int Real,Imag;
};
int main()
{ Complex a(2,3); a.disp(); //调用void disp()
const Complex b(10,20); b.disp(); //调用void disp() const
return 0;
}

输入格式:

读入两行，第一行读入两个整数，表示复数a的实部与虚部，第二行读入两个整数，表示复数b的实部与虚部。

输出格式:

输出两行不同格式表示的复数形式。

输入样例:

在这里给出一组输入。例如：

```in
1 2
10 20
```

输出样例:

在这里给出相应的输出。例如：

```out
(1,2i)
[10,20j]
```

code

```c++
#include <iostream>  
using namespace std;

class Complex {
public:
    // 构造函数  
    Complex(int real, int imag) : Real(real), Imag(imag) {}

    // 普通成员函数，重载输出函数  
    void disp() {
        cout << "(" << Real << "," << Imag << "i)" << endl;
    }

    // 常成员函数，重载输出函数  
    void disp() const {
        cout << "[" << Real << "," << Imag << "j]" << endl;
    }

private:
    int Real, Imag;
};

int main() {
    int real1, imag1, real2, imag2;
    cin >> real1 >> imag1;
    cin >> real2 >> imag2;

    Complex a(real1, imag1);
    a.disp(); // 调用非const的disp()  

    const Complex b(real2, imag2);
    b.disp(); // 调用const的disp()  

    return 0;
}
```







## 作业五：

### 1.设计一个People类

设计一个People 类，该类的数据成员有姓名、年龄、身高、体重和人数，其中人数为静态数据成员，成员函数有构造函数、显示和显示人数。其中构造函数由参数姓名、年龄、身高和体重来构造对象；显示函数用于显示人的姓名、年龄、身高和体重；显示人数函数为静态成员函数，用于显示总的人数。

输入格式:

按姓名、年龄、身高和体重依次输入每个人的信息
已exit结束
zhang 18 180 70
li 20 160 50
exit

输出格式:

输出总人数，例如
2

输入样例:

在这里给出一组输入。例如：

```in
zhang 18 180 70
li 20 160 50
exit
```

输出样例:

在这里给出相应的输出。例如：

```out
2
```



code

```c++
#include <iostream>  
#include <string>  

class People {
private:
    std::string name;
    int age;
    double height;
    double weight;

    // 静态数据成员，记录People类的实例总数  
    static int totalPeople;

public:
    // 构造函数  
    People(const std::string& n, int a, double h, double w)
        : name(n), age(a), height(h), weight(w) {
        totalPeople++; // 每创建一个实例，总数加1  
    }

    // 显示个人信息  
    void display() const {
        std::cout << name << " " << age
            << " " << height << " " << weight << std::endl;
    }

    // 静态成员函数，显示总人数  
    static int displayTotalPeople() {
        return totalPeople;
    }
};

// 初始化静态数据成员  
int People::totalPeople = 0;

int main() {
    std::string name;
    int age;
    double height, weight;

    int total = 0;
    while (true) {
        std::cin >> name;
        if (name == "exit") {
            break;
        }
        std::cin >> age >> height >> weight;

        People person(name, age, height, weight);
        //person.display();
        total++; // 也可以在这里使用totalPeople，但为了展示不同的计数方式，这里使用total  
    }

    std::cout << People::displayTotalPeople() << std::endl; // 输出总人数  

    return 0;
}
```



### 2.游泳池改造预算

例4-3一圆形游泳池如图所示，现在需在其周围建一圆形过道，并在其四周围上栅栏。栅栏价格为35元/米，过道造价为20元/平方米。过道宽度为3米，游泳池半径由键盘输入。要求编程计算并输出过道和栅栏的造价。

![7a08ad96-69ef-42b8-9889-114a2010c7a0.png](https://images.ptausercontent.com/5d97d9b4-89d1-47c0-9005-a326f53eeee2.png)

输入格式:

输入一个整数或小数。

输出格式:

分两行输出：在第一行中输出栅栏的造价。在第二行输出过道的造价。

输入样例:

```in
10
```

输出样例:

```out
Fencing Cost is $2858.85
Concrete Cost is $4335.4
```



code

```cpp
#include <iostream>  
#include <cmath>  
#include <iomanip> // 用于控制输出格式  

using namespace std;

int main() {
    double poolRadius; // 游泳池半径  
    double pathRadius; // 过道半径  
    double fenceCost; // 栅栏造价  
    double concreteCost; // 过道造价  
    const double fencePricePerMeter = 35.0; // 栅栏单价  
    const double concretePricePerSquareMeter = 20.0; // 过道单价  
    const double pathWidth = 3.0; // 过道宽度
    double PI = 3.1415926;

    // 输入游泳池半径  
    cin >> poolRadius;

    // 计算过道半径  
    pathRadius = poolRadius + pathWidth;

    // 计算栅栏总长度（圆周长）  
    double fenceLength = 2 * PI * pathRadius;
    // 计算栅栏造价  
    fenceCost = fenceLength * fencePricePerMeter;

    // 计算过道总面积（圆环面积）  
    double concreteArea = PI * (pathRadius * pathRadius - poolRadius * poolRadius);
    // 计算过道造价  
    concreteCost = concreteArea * concretePricePerSquareMeter;

    // 输出栅栏造价，注意格式控制，保留两位小数，并添加货币符号  
    cout << fixed << setprecision(2) << "Fencing Cost is $" << fenceCost << endl;
    // 输出过道造价，同样注意格式控制  
    cout << fixed << setprecision(1) << "Concrete Cost is $" << concreteCost << endl;

    return 0;
}
```



## 作业六:

### 1. 通过指针，输出对象数组的数据

分数 20

全屏浏览切换布局

作者 杨雪华

单位 沈阳师范大学

设计一个类，主函数中建立一个对象数组，输入5个学生数据（学号、成绩），用对象指针指向数组首元素，输出5个学生的数据。

输入格式:

输入5个学生数据（学号、成绩），学号为不超过10000的正整数，成绩为0-100的正整数。

输出格式:

按顺序输出学生的学号和成绩，每行显示一个学生的信息。

输入样例:

在这里给出一组输入。例如：

```in
101 90
102 80
103 70
104 60
105 50
```

输出样例:

在这里给出相应的输出。例如：

```out
101 90
102 80
103 70
104 60
105 50
```

code

```cpp
#define _CRT_SECURE_NO_WARNINGS  1

#include <iostream>  
using namespace std;

class Student {
public:
    // 构造函数  
    Student() {};
    Student(int id, int score) : id_(id), score_(score) {}

    // 显示学生信息的成员函数  
    void display() const {
        cout << id_ << " " << score_ << endl;
    }

private:
    int id_; // 学号  
    int score_; // 成绩  
};

int main() {
    const int NUM_STUDENTS = 5; // 定义学生数量  
    Student students[NUM_STUDENTS]; // 创建学生对象数组  需要定义无参构造函数
    Student* p = students; // 对象指针指向数组首元素  

    // 读取每个学生的学号和成绩  
    for (int i = 0; i < NUM_STUDENTS; ++i) {
        int id, score;
        cin >> id >> score;
        students[i] = Student(id, score); // 使用输入的值初始化对象  
    }

    // 输出每个学生的信息  
    for (int i = 0; i < NUM_STUDENTS; ++i) {
        p->display(); // 调用display函数输出学生信息  
        p++; // 移动指针到下一个对象  
    }

    return 0;
}
```



### 2.友元函数的练习

定义Boat与Car两个类，两者都有私有的整型weight属性，定义两者的一个友元函数getTotalWeight()，计算二者的重量和。

参考主函数：
int main()
{
int n,m;
cin>>n>>m;
Boat boat(n);
Car car(m);
cout<<"船和汽车共重"<<getTotalWeight(boat,car)<<"吨"<<endl;
}

输入格式:

请在这里写输入格式。例如：输入在一行中给出2个整数m和n。

输出格式:

请在这里描述输出格式。例如：对每一组输入，在一行中输出:船和汽车共重M+n吨值。

输入样例:

在这里给出一组输入。例如：

```in
40 30
```

输出样例:

在这里给出相应的输出。例如：

```out
船和汽车共重70吨
```



code

```cpp
#include <iostream>  
using namespace std;

class Car;//这里必须要提前定义，因为下面Boat类中调用到了Car类
class Boat {
private:
    int weight;
    // 声明getTotalWeight为友元函数  
    
public:
    Boat(int w) : weight(w) {};
    friend int getTotalWeight(Boat& b, Car& c);

    
};

class Car {
private:
    int weight;
    // 声明getTotalWeight为友元函数  
    
public:
    Car(int w) : weight(w) {};
    friend int getTotalWeight(Boat& b, Car& c);

};

// 定义友元函数，可以访问Boat和Car的私有成员weight  
int getTotalWeight(Boat& b,Car& c) {
    return b.weight + c.weight;
}

int main() {
    int m, n;
    cin >> m >> n;
    Boat boat(m);
    Car car(n);
    cout << "船和汽车共重" << getTotalWeight(boat, car) << "吨" << endl;
    return 0;
}
```



### 3.国际贸易统计



这里给出*N*个国家之间进行国际贸易的记录，请你统计这些国家进行国际贸易的收益。

输入格式:

输入第一行给出一个正整数*N*（≤104），即参与国际贸易的国家数量，则这些国家从1到*N*编号。随后*N*行，第*i*行给出编号为*i*的国家在贸易中卖出商品的记录，格式如下：*k**N*1*P*1⋯*N**k**P**k*，
其中*k*(0≤*k*≤20)是买入商品国家的个数，*N**i*​是买入商品国家的编号，*P**i*​>0是其买入商品的金额（整数表示，以万元为单位）。注意：一次贸易对于买入和卖出国家的贸易次数都会增加1次。

输出格式:

按照收入金额从高到低的递减顺序输出每个国家的编号和收入金额（整数表示，以万元为单位）。每个国家的信息占一行，两数字间有1个空格。如果收入金额有并列，则按参与国际贸易的次数递减输出；如果还有并列，则按国家编号递增输出。

输入样例:

```in
10
3 2 22 10 58 8 125
5 1 345 3 211 5 233 7 13 8 101
1 7 8800
2 1 1000 2 1000
2 4 250 10 320
6 5 11 9 22 8 33 7 44 10 55 4 2
1 3 8800
2 1 23 2 123
1 8 250
4 2 121 4 516 7 112 9 10
```

输出样例:

```out
4 1232
10 326
5 326
9 218
6 167
7 -169
3 -211
2 -363
8 -363
1 -1163
```



网络code

```cpp
#include<iostream> // 引入标准输入输出流库  
using namespace std; // 使用标准命名空间  
  
class country // 定义一个国家类  
{  
public:  
    int num; // 国家编号  
    int getings; // 国家收益  
    int counts; // 国家参与贸易次数  
};  
  
int main()  
{  
    int n;  
    cin >> n; // 读取国家数量  
    country cty[105]; // 定义国家数组，这里数组大小硬编码为105，实际上应根据n动态分配  
  
    // 初始化国家数组，编号从1开始，其实应该从0开始  
    for (int i = 1; i < n + 1; i++)  
    {  
        cty[i].counts = 0; // 初始化贸易次数为0  
        cty[i].getings = 0; // 初始化收益为0  
        cty[i].num = i; // 设定国家编号  
    }  
  
    // 读取每个国家的贸易记录  
    for (int i = 1; i < n + 1; i++)  
    {  
        int* in = new int; // 动态分配内存读取贸易次数，实际上可以直接使用局部变量  
        cin >> *in;  
        cty[i].counts += *in; // 累加贸易次数  
  
        // 读取具体的贸易详情  
        for (int j = 0; j < *in; j++)  
        {  
            int* id = new int; // 动态分配内存读取贸易伙伴编号  
            cin >> *id;  
            cty[*id].counts++; // 增加贸易伙伴的贸易次数  
  
            int* inin = new int; // 动态分配内存读取贸易金额  
            cin >> *inin;  
            cty[i].getings += *inin; // 增加本国的收益  
            cty[*id].getings -= *inin; // 减少贸易伙伴的收益  
  
            delete id; // 释放动态分配的内存  
            delete inin;  
        }  
        delete in;  
    }  
  
    // 排序国家数组，但排序逻辑不正确  
    for (int i = 1; i < n + 1; i++)  
    {  
        for (int j = 1; j < n; j++) // 这里循环条件应为 j < n - 1，否则最后一个元素不会参与比较  
        {  
            // 如果收益相同，且交易次数也相同，则按编号降序排序  
            if (cty[j].getings == cty[j + 1].getings && cty[j].counts == cty[j + 1].counts && cty[j].num > cty[j + 1].num)  
            {  
                country* p = new country; // 实际上这里不需要动态分配内存，可以直接使用临时变量  
                *p = cty[j];  
                cty[j] = cty[j + 1];  
                cty[j + 1] = *p;  
                delete p;  
            }  
            // 如果收益相同，但交易次数不同，则按交易次数降序排序  
            else if (cty[j].getings == cty[j + 1].getings && cty[j].counts < cty[j + 1].counts)  
            {  
                country* p = new country;  
                *p = cty[j];  
                cty[j] = cty[j + 1];  
                cty[j + 1] = *p;  
                delete p;  
            }  
            // 如果收益不同，则按收益降序排序  
            else if (cty[j].getings < cty[j + 1].getings)  
            {  
                country* p = new country;  
                *p = cty[j];  
                cty[j] = cty[j + 1];  
                cty[j + 1] = *p;  
                delete p;  
            }  
        }  
    }  
  
    // 输出排序后的国家编号和收益  
    for (int i = 1; i < n + 1; i++)  
    {  
        cout << cty[i].num << " " << cty[i].getings << endl;  
    }  
  
    return 0;  
}
```



### 若提示没有默认构造函数，直接在public中定义一个无参构造函数即可





## 作业七：

### 1.单继承中的构造函数与析构函数

编写代码实现一个表示点的父类Dot和一个表示圆的子类Cir，求圆的面积。

Dot类有两个private数据成员 float x,y;

Cir类新增一个private的数据成员半径float r 和一个public的求面积的函数getArea( );

主函数已经给出，请编写Dot和Cir类。

```
#include <iostream>
#include<iomanip>
using namespace std;
const double PI=3.14;
//请编写你的代码
int main(){
    float x,y,r;
    cin>>x>>y>>r;
    Cir c(x,y,r);
    cout<<fixed<<setprecision(2)<<c.getArea()<<endl;
    return 0;
}
```

输入格式:

输入圆心和半径，x y r中间用空格分隔。

输出格式:

输出圆的面积，小数点后保留2位有效数字，注意：const double PI=3.14，面积=`PI*r*r`。

输入样例:

在这里给出一组输入。例如圆的中心点为原点（0,0），半径为3：

```in
0 0 4
```

输出样例:

在这里给出相应的输出。例如：

```out
Dot constructor called
Cir constructor called
50.24
Cir destructor called
Dot destructor called
```

code

```cpp
#include <iostream>
#include <iomanip>
using namespace std;
const double PI=3.14;
 
class Dot{
	private:
		float x,y;
	public:
		Dot(int a,int b):x(a),y(b){
			printf("Dot constructor called\n") ;
		}
		Dot(){
			printf("Dot constructor called\n") ;
		}
        virtual ~Dot(){
        	printf("Dot destructor called\n");
		}
};
class Cir:public Dot{
	private :
		float r;
	public :
	Cir(){
		printf("Cir constructor called\n") ;
	} 
	Cir(int a,int b,int c):Dot(a,b),r(c){
		printf("Cir constructor called\n") ;
	}
	 ~Cir(){
        	printf("Cir destructor called\n");
		}
	float getArea(){
		return r*r*PI;
	}
};
int main(){
    float x,y,r;
    cin>>x>>y>>r;
    Cir c(x,y,r);
    cout<<fixed<<setprecision(2)<<c.getArea()<<endl;
    return 0;
}
```



### 2.动物世界

补充程序 ：

1、实现Mammal类的方法

2、由Mammal类派生出Dog类，在Dog类中增加itsColor成员(COLOR类型)

3、Dog类中增加以下方法：

constructors: Dog()、Dog(int age)、Dog(int age, int weight)、Dog(int age, COLOR color)、 Dog(int age, int weight, COLOR color)、~Dog()

accessors: GetColor()、SetColor()

Other methods: WagTail()、BegForFood() ，并实现以上这些方法 。

提示：类似Speak()、WagTail()这些动作，函数体可以是输出一句话。比如：Mammal is spaeking... , The Dog is Wagging its tail...

4、补充主函数的问号部分，并运行程序，检查输出是否合理。

```
enum COLOR{ WHITE, RED, BROWN, BLACK, KHAKI };

class Mammal
{
    public:
        //constructors
        Mammal();
        Mammal(int age);
        ~Mammal();
        
        //accessors
        int GetAge() const;
        void SetAge(int);
        int GetWeight() const;
        void SetWeight(int);
        
        //Other methods    
        void Speak() const;
        void Sleep() const;        
    protected:
        int itsAge;
        int itsWeight;
};

int main()
{
    Dog Fido;
    Dog Rover(5);
    Dog Buster(6, 8);
    Dog Yorkie(3, RED);
    Dog Dobbie(4, 20, KHAKI);
    Fido.Speak();
    Rover.WagTail();
    cout << "Yorkie is " << ?? << " years old." << endl;
    cout << "Dobbie    weighs " << ?? << " pounds." << endl;   
    return 0;
}
```

输入格式:

无

输出格式:

按照程序格式输出。

输入样例:

在这里给出一组输入。例如：

```in
无
```

输出样例:

在这里给出相应的输出。例如：

```out
Mammal is speaking...
The dog is wagging its tail...
Yorkie is 3 years old.
Dobbie weighs 20 pounds.
```



code

```cpp
#include<cmath>
#include<cstdio>
#include<algorithm>
#include<string>
#include<vector>
#include<iomanip>
#include<iostream>


using namespace std;
enum COLOR { WHITE, RED, BROWN, BLACK, KHAKI };
//枚举类型，定义的名字叫COLOR，变量有后边这一串（WHITE, RED, BROWN, BLACK, KHAKI ）
//在这里是好看的？
//有给他赋值吗？

/*基类*/
class Mammal
{
public:
    //constructors
    Mammal(){}
    Mammal(int age)
    {
        itsAge=age;
    }
    ~Mammal(){}

    //accessors
    int GetAge() const
    {
        return itsAge;
    }
    void SetAge(int n)
    {
        itsAge=n;
    }
    int GetWeight() const
    {
        return itsWeight;
    }
    void SetWeight(int n)
    {
        itsWeight=n;
    }

    //Other methods
    void Speak() const//这个得好好写
    {
        cout<<"Mammal is speaking..."<<endl;
    }
    void Sleep() const//看起来可以瞎写
    {
        cout<<"Mammal is sleeping..."<<endl;
    }
protected:
    int itsAge;
    int itsWeight;
};

/*派生类*/

class Dog:public Mammal
{
public://呵
    Dog() {}//构造函数1号
    Dog(int age):Mammal(age) {}//构造函数2号
    Dog(int age,int weight):Mammal(age)//构造函数3号
    {
       SetWeight(weight);
    }
    Dog(int age, COLOR color):Mammal(age)//构造函数4号
    {
        colors=color;
    }
    Dog(int age, int weight, COLOR color):Mammal(age)//构造函数5号
    {
         SetWeight(weight);
        colors=color;
    }
    ~Dog() {}

    void WagTail() const//这个得好好写
    {
        cout<<"The dog is wagging its tail..."<<endl;
    }
    void BegForFood()  const//看起来可以瞎写
    {
        cout<<"The dog is begging for food..."<<endl;
    }
protected:
    COLOR colors;//所以其实没啥用？
};
int main()
{
	Dog Fido;
	Dog Rover(5);
	Dog Buster(6, 8);
	Dog Yorkie(3, RED);
	Dog Dobbie(4, 20, KHAKI);
	Fido.Speak();
	Rover.WagTail();
	cout << "Yorkie is " << Yorkie.GetAge() << " years old." << endl;
	cout << "Dobbie weighs " << Dobbie.GetWeight() << " pounds." << endl;
	return 0;
}


```



## 作业八：

选填：

叮！快来看看我和文心一言的奇妙对话～点击链接 https://yiyan.baidu.com/share/StQrsH79iu -- 文心一言，既能写文案、读文档，又能绘画聊天、写诗做表，你的全能伙伴！



### 1.日程安排（多重继承+重载）



已有一个日期类Date，包括三个protected成员数据

int year;

int month;

int day;

另有一个时间类Time，包括三个protected成员数据

int hour;

int minute;

int second;

现需根据输入的日程的日期时间，安排前后顺序，为此以Date类和Time类为基类，建立一个日程类Schedule，包括以下新增成员：

int ID；//日程的ID

bool operator < (const Schedule & s2);//判断当前日程时间是否早于s2

生成以上类，并编写主函数，根据输入的各项日程信息，建立日程对象，找出需要最早安排的日程，并输出该日程对象的信息。

**输入格式：**

 测试输入包含若干日程，每个日程占一行（日程编号ID 日程日期（/**/\**）日程时间（\**:**:**））。当读入0时输入结束，相应的结果不要输出。

**输入样例：**

1 2014/06/27 08:00:01

2 2014/06/28 08:00:01

0

**输出样例：**

The urgent schedule is No.1: 2014/6/27 8:0:1



**code**

```cpp
#define _CRT_SECURE_NO_WARNINGS  1
#include <iostream>
using namespace std;
// 日期类
class Date {
protected:
    int year;
    int month;
    int day;
public:
    Date(int year, int month, int day) : year(year), month(month), day(day) {}

public:
    // 将日期转换为整型数据
    int toIntData() {
        return year * 10000 + month * 100 + day;
    }
    // 显示日期
    void showdate() { cout << " " << year << "/" << month << "/" << day; }
};
// 时间类
class Time {
protected:
    int hour;
    int minute;
    int second;
public:
    Time(int hour, int minute, int second) : hour(hour), minute(minute), second(second) {}

public:
    // 将时间转换为整型时间
    int toIntTime() {
        return hour * 10000 + minute * 100 + second;
    }
    // 显示时间
    void showtime() { cout << " " << hour << ":" << minute << ":" << second; }
};
// 日程类
class Schedule :public Date, Time {
protected:
    int id;
public:
    // 构造函数
    Schedule(int id, int year, int month, int day, int hour, int minute, int second) : Date(year, month, day),
        Time(hour, minute, second),
        id(id) {}

public:
    // 重载小于运算符
    bool operator < (Schedule s2) {
        if (this->toIntData() != s2.toIntData()) {
            return toIntData() < s2.toIntData();
        }
        else {
            return toIntTime() < s2.toIntTime();
        }
    }
    // 显示日程
    void show() {
        cout << "No." << id << ":";
        Date::showdate();
        Time::showtime();
    }
};

int main() {
    int n;
    int a, b, c, d, e, f;
    Schedule s2(0, 9999, 9999, 9999, 999, 999, 99);
    while (cin >> n, n != 0) {
        scanf("%d/%d/%d", &a, &b, &c);
        scanf("%d:%d:%d", &d, &e, &f);
        Schedule s1(n, a, b, c, d, e, f);
        if (s1 < s2) {
            s2 = s1;
        }
    }
    cout << "The urgent schedule is "; s2.show();

}

```





## 作业九：

**选填**

叮！快来看看我和文心一言的奇妙对话～点击链接 https://yiyan.baidu.com/share/Qt4oz85uAa -- 文心一言，既能写文案、读文档，又能绘画聊天、写诗做表，你的全能伙伴！



### 1.马会飞



已知Horse类是Pegasus类的父类，根据以下主函数完善程序内容，以实现规定的输出。不允许改变主函数的内容。

```
int main()
{
    Horse *p1 = new Horse; //输出：Horse 申请了空间...
    Horse *p2 = new Pegasus; /*  输出两行：
                                 Horse 申请了空间...
                                 Pegasus 申请了空间...   
                     */    
    cout << endl; 
    
    p1->Fly(); //输出：Just a horse.
    p2->Fly(); //输出：I can fly!
    cout << endl; 
    
    delete p1; //输出：Horse 释放了空间...
    delete p2;  /* 输出两行：
                   Pegasus 释放了空间... 
                   Horse 释放了空间... 
            */
    return 0;
}
```

**输入格式:**

无

**输出格式:**

根据样例格式输出。

**输入样例:**

在这里给出一组输入。例如：

```in
无
```

**输出样例:**

在这里给出相应的输出。例如：

```out
Horse 申请了空间...
Horse 申请了空间...
Pegasus 申请了空间...

Just a horse.
I can fly!

Horse 释放了空间...
Pegasus 释放了空间...
Horse 释放了空间...
```

code

```cpp
#include<iostream>
using namespace std;
class Horse{
public:
  	Horse(){cout<<"Horse 申请了空间...\n";}
  	virtual ~Horse(){cout<<"Horse 释放了空间...\n";}
  //这里的析构函数一定要设置为虚函数，否则子类里面的析构函数将不执行
  virtual void Fly(){cout<<"Just a horse.\n";}
};
class Pegasus:public Horse{
public:
  	Pegasus(){cout<<"Pegasus 申请了空间...\n";}
  	~Pegasus(){cout<<"Pegasus 释放了空间...\n";}
   void Fly(){cout<<"I can fly!\n";}
};
int main()
{
	Horse *p1 = new Horse; //输出：Horse 申请了空间...
	Horse *p2 = new Pegasus; /*  输出两行：
	                             Horse 申请了空间...
	                             Pegasus 申请了空间...   
			         */	
	cout << endl; 
	
	p1->Fly(); //输出：Just a horse.
	p2->Fly(); //输出：I can fly!
	cout << endl; 
	
	delete p1; //输出：Horse 释放了空间...
	delete p2;  /* 输出两行：
	               Pegasus 释放了空间... 
	               Horse 释放了空间... 
		    */
	return 0;
}

```



### 2.类的继承与派生



定义平面二维点类CPoint，有数据成员x坐标，y坐标，函数成员(构造函数复制构造函数、虚函数求面积GetArea,虚函数求体积函数GetVolume、输出点信息函数print。由CPoint类派生出圆类Cirle类（新增数据成员半径radius），函数成员(构造函数、复制构造函数、求面积GetArea,虚函数求体积函数GetVolume、输出圆信息函数print。
再由Ccirle类派生出圆柱体Ccylinder类（新增数据成员高度height），函数成员(构造函数、复制构造函数、求表面积GetArea,求体积函数GetVolume、输出圆柱体信息函数print。在主函数测试这个这三个类。

**输入格式:**

0 0 例如：第一行读入圆心坐标。
1 2 第二行读入半径与高度。

**输出格式:**

分四行输出，分别代表圆心、底面积、表面积、体积。

**输入样例:**

在这里给出一组输入。例如：

```in
0 0
1 2
```

**输出样例:**

在这里给出相应的输出。例如：

```out
Center:(0,0)
radius=1
height:2
BasalArea:3.14159
SupfaceArea:18.8496
Volume:6.28319
```

code

```cpp
#include <bits/stdc++.h>
using namespace std;
#define PI 3.1415926
class CPoint
{
	double x,y;
public:
	CPoint(double a=0,double b=0)
	{
		x=a;
		y=b;
	}
	CPoint(CPoint &c)
	{
		x=c.x;
		y=c.y;
	}
	virtual double GetArea()
	{
		return 0.0;
	}
	virtual double GetVolume()
	{
		return 0.0;
	}
	void print()
	{
		cout<<"Center:("<<x<<","<<y<<")"<<endl;
	}
	
};

class Cirle:public CPoint
{
protected:
	double radius;
public:
	Cirle(double a,double b,double r):CPoint(a,b)
	{
		radius=r;
	}
	Cirle(Cirle &c)
	{
		radius=c.radius;
	}
	double GetArea()
	{
		return PI*radius*radius;
	}
	virtual double GetVolume()
	{
		return 0.0;
	}
	void print()
	{
		cout<<"radius="<<radius<<endl;
	}	
};

class Cylinder:public Cirle
{
	double height;
public:
	Cylinder(double a,double b,double r,double h):Cirle(a,b,r)
	{
		height=h;
	}
	Cylinder(Cylinder &k):Cirle(k)
	{		
		height=k.height;
	}
	double SupfaceArea()
	{
		return 2*PI*radius*height+PI*radius*radius*2;
	}
	double GetVolume()
	{
		return PI*radius*radius*height;
	}
	void print()
	{
		cout<<"height:"<<height<<endl;
		cout<<"BasalArea:"<<GetArea()<<endl;
		cout<<"SupfaceArea:"<<SupfaceArea()<<endl;
		cout<<"Volume:"<<GetVolume()<<endl;		
	}	
};

int main()
{
	double a,b,c,d;
	cin>>a>>b>>c>>d;
	CPoint cp(a,b);
	Cirle ci(a,b,c);
	Cylinder cy(a,b,c,d);
	cp.print();
	ci.print();
	cy.print();
	return 0;
}

```



### 3.用虚函数计算各种图形的面积



定义抽象基类Shape，由它派生出五个派生类：Circle（圆形）、Square（正方形）、Rectangle（ 长方形）、Trapezoid （梯形）和Triangle （三角形），用虚函数分别计算各种图形的面积，输出它们的面积和。要求用基类指针数组，每一个数组元素指向一个派生类的对象。PI=3.14159f，单精度浮点数计算。

输入格式:

输入在一行中，给出9个大于0的数，用空格分隔，分别代表圆的半径，正方形的边长，矩形的宽和高，梯形的上底、下底和高，三角形的底和高。

输出格式:

输出所有图形的面积和，小数点后保留3位有效数字。

输入样例:

```in
12.6 3.5 4.5 8.4 2.0 4.5 3.2 4.5 8.4
```

输出样例:

```out
578.109
```



code

```cpp
 
#include<iostream>
using namespace std;
#define PI 3.14159
class Shape
{
protected:
    double a, b, c;
public:
    Shape(double a=0,double b=0,double c=0)
    {
        this->a = a; this->b = b;
        this->c = c;
    }
    virtual double getmianji() = 0;
};
class Circle:public Shape//（圆形）
{//Circle（圆形）、Square（正方形）、Rectangle（ 长方形）、Trapezoid （梯形）和Triangle （三角形）
public:
    Circle(double a) :Shape(a) {}
    double getmianji()
    {
        return PI * a * a;
    }
};
class Square :public Shape//（正方形）
{
public:
    Square(double a) :Shape(a) {}
    double getmianji()
    {
        return  a * a;
    }
};
class Rectangle :public Shape//（长方形）
{
public:
    Rectangle(double a,double b) :Shape(a,b) {}
    double getmianji()
    {
        return a*b;
    }
};
class Trapezoid :public Shape//（梯形）
{
public:
    Trapezoid(double a,double b,double c) :Shape(a,b,c) {}
    double getmianji()
    {
        return (a + b) * c * 0.5;
    }
};
class Triangle :public Shape//（三角形）
{
public:
    Triangle(double a,double b) :Shape(a,b) {}
    double getmianji()
    {
        return a*b*0.5;
    }
};
int main()
{//12.6 3.5 4.5 8.4 2.0 4.5 3.2 4.5 8.4
    //要求用基类指针数组
 
    double a, b, c;
    cin >> a;
    Circle C(a);
    cin >> a ;
    Square s(a);
    cin >> a >> b;
    Rectangle r(a, b);
    cin >> a >> b >> c;
    Trapezoid t1(a, b, c);
    cin >> a >> b;
    Triangle t2(a, b);
    Shape* sp[5] = { &C,&s,&r,&t1,&t2 };
    double sum = 0;
    for (int i = 0; i < 5; i++)
    {
        sum += sp[i]->getmianji();
    }
    printf("%0.3f", sum);
    system("pause");
}
```



## 作业十：



### 1.时间间隔计算

定义一个Time类，小时hour和分钟min是其两个私有成员数据。输入一个起始时间和一个结束时间(起始时间早于结束时间)，通过运算符重载-（减号），计算这两个时间相隔多少分钟。说明：这两个时间在同一天之内，且采用24小时计时分式，即从00:00-23:59。

输入格式:

输入若干测试用例，每个测试用例占一行。每个测试用例包括四个数，用空格间隔，每个数都是由两位数字组成，第一个数和第二个数分别表示起始时间的小时和分钟，第三个数和第四个数分别表示结束时间的小时和分钟。当读入一个测试用例是00 00 00 00时输入结束，其相应的结果不要输出。

输出格式:

对每个测试用例输出一行。输出一个数即可，表示两者之间间隔的分钟数。

输入样例:

```in
12 11 12 58
00 13 16 00
09 07 23 59
00 00 00 00
```

输出样例:

在这里给出相应的输出。例如：

```out
47
947
892
```



code

```cpp
#include<iostream>
using namespace std;
class Time {
private:
	int minute;
    int second;
public:
	Time(int m = 00, int s = 00) {
	minute = m;
	second = s;
	}
	int friend operator- (Time p, Time q);
};
int operator- (Time q, Time p) {
	int c = 0;
	int d = 0;
	if (p.second < q.second|| p.second == q.second) {
		d = q.minute - p.minute;
		c = q.second - p.second + 60 * d;
		return c;
	}
	else {
		d = q.minute - p.minute - 1;
		c = 60 + q.second - p.second + 60 * d;
		return c;
	
	}
}
int main() {
	int a, b, c, d;
	while (cin >> a >> b >> c >> d) {
		if (a == 00 && b == 00 && c == 00 && d == 00)
			break;
		int difference;
		Time p1(a, b);
		Time p2(c, d);
		difference = p2 - p1;
		cout << difference << endl;



	}
	return 0;
}

```



### 2.复数的输出输出



本题目要求完成复数类对象的输入运算符>>和输出运算符<<的重载，具体要求如下：定义复数类，包括两个私有成员：double real,imag;定义复数类的构造函数；重载输入运算符>>,使主函数可以通过cin>>接收复数对象的输入；重载输出运算符<<,使主函数可以通过cout<<输出复数对象。在主函数中构造复数对象，并用cin>>和cout<<进行输入输出的测试.

输入样例:

```in
3.1+4.2i
```

输出样例:

在这里给出相应的输出。例如：

```out
3.1+4.2i
```



code

```cpp
#include <iostream>  
#include <sstream>  
#include <string>  
  
using namespace std;  
  
class Complex {  
private:  
    double real, imag;  
  
public:  
    Complex(double r = 0.0, double i = 0.0) : real(r), imag(i) {}  
  
    friend istream& operator>>(istream& in, Complex& c);  
    friend ostream& operator<<(ostream& out, const Complex& c);  
};  
  
istream& operator>>(istream& in, Complex& c) {  
    string input;  
    in >> input;  
    size_t plusPos = input.find('+');  
    size_t iPos = input.find('i');  
    if (plusPos != string::npos && iPos != string::npos) {  
        string realStr = input.substr(0, plusPos);  
        string imagStr = input.substr(plusPos + 1, iPos - plusPos - 1);  
        c.real = stod(realStr);  
        c.imag = stod(imagStr);  
    } else {  
        c.real = stod(input);  
        c.imag = 0;  
    }  
    return in;  
}  
  
ostream& operator<<(ostream& out, const Complex& c) {  
    out << c.real;  
    if (c.imag >= 0) {  
        out << "+" << c.imag << "i";  
    } else {  
        out << c.imag << "i";  
    }  
    return out;  
}  
  
int main() {  
    Complex c;  
    cin >> c;  
    cout << c << endl;  
    return 0;  
}
```





## 作业十一

### 1.定义类模板实现2个数的算术运算

**7-1 定义类模板实现2个数的算术运算**

分数 30

全屏浏览切换布局

作者 孙杰

单位 青岛大学

本题目要求定义类模板实现2个数的最大值、最小值、加、减、乘、除等算术运算，在main（）函数中使用该类模板分别实例化为int型和double型的类，定义相关的对象，读入2个整数和2个浮点数，然后分别输出它们的最大值、最小值、加、减、乘、除的结果。

输入格式:

分别输入2组数字，第一行为2个整数，以空格分隔；第二行为2个浮点数，以空格分隔。

输出格式:

分2行分别输出整数和浮点数的运算结果，每行依次输出2个数的最大值、最小值、加、减、乘、除等算术运算。

输入样例:

```in
30 2
2.1 3.2
```

输出样例:

```out
30 2 32 28 60 15
3.2 2.1 5.3 -1.1 6.72 0.65625
```



code

```cpp
#include "iostream"
using namespace std;
 
template <class T>class Test {
public:
	Test(T a,T b) {
		this->a = a;
		this->b = b;
	}
	T m() {
		return max(a,b);
	}
	T x() {
		return min(a,b);
	}
 
	T jia() {
		return a + b;
	}
	T jian() {
		return  a - b;
	}
	T cheng() {
		return a * b;
	}
	T chu() {
		return a / b;
	}
	void print() {
		cout << m() << " " << x() << " " << jia() << " " << jian() << " " << cheng() << " " << chu() << endl;
	}
private:
	T a;
	T b;
};
 
 
int main() {
	int a, b;
	float c, d;
	cin >> a >> b;
	cin >> c >> d ;
	Test<int>test(a,b);
	test.print();
	Test<float>test2(c, d);
	test2.print();
	return 0;
}
```



### 2.办事大厅排队

**7-2 办事大厅排队**

分数 30

全屏浏览切换布局

作者 吴云鹏

单位 郑州大学

在郑州大学综合办事大厅，每天陆陆续续有很多人来排队办事。现在你能否写程序帮助老师时刻了解当前办理业务的情况。

**请同学们学习C++ STL中 list相关内容后，编程实践。**

输入格式:

第一行一个数字N，表示排队信息或者查询信息条目的数量。

以下N行，每行的内容有以下3种情况

(1) in name 表示名字为name的人员新来到办事大厅，排在队伍的最后。（in和name间存在一个空格，name是名字对应字符串，长度不超过10）。

(2) out 表示当前排在最前面的人已经办理完业务，离开了。

(3) q 表示一次查询，请输出当前正在办理业务的人，也就是队伍的第1个人。如果当前无人办理业务，则输出“NULL”，不包括引号。

输出格式:

请根据以上信息，每次遇到查询时，对应一行输出。如果这时队伍有人，则输出第一个人的姓名，否则输出NULL。

输入样例:

```in
5
in A
out
q
in B
q
```

输出样例:

在这里给出相应的输出。例如：

```out
NULL
B
```



code

```cpp
#include<cmath>
#include<cstdio>
#include<algorithm>
#include<string>
#include<vector>
#include<iomanip>
#include<iostream>
#include<cstring>
#include <list>
using namespace std;
int main()
{
    int n;
    string s,name;
    cin>>n;
    list<string> l;
    while(n--){
        cin>>s;
        if(s=="in"){
            cin>>name;
            l.push_back(name);
        }else if(s=="out"){
            l.pop_front();
        }else if(s=="q"){
            if(l.empty()){
                cout<<"NULL"<<endl;
            }else{
                cout<<l.front()<<endl;
            }
        }
    }

    return 0;
}

```



### 3.笨小猴

**7-3 笨小猴**

分数 10

全屏浏览切换布局

作者 CCF-NOI

单位 成都信息工程大学

笨小猴的词汇量很少，所以每次做英语选择题的时候都很头疼。但是他找到了一种方法，经试验证明，用这种方法去选择选项的时候选对的几率非常大！

这种方法的具体描述如下：假设max是单词中出现次数最多的字母的出现次数，min是单词中出现次数最少的字母的出现次数，如果max-min是一个质数，那么笨小猴就认为这是个Lucky Word，这样的单词很可能就是正确的答案。

输入格式:

一个单词，其中只可能出现小写字母，并且长度小于100。

输出格式:

共两行，第一行是一个字符串，假设输入的的单词是Lucky Word，那么输出“`Lucky Word`”，否则输出`No Answer`；

第二行是一个整数，如果输入单词是`Lucky Word`，输出max-min的值，否则输出0。

输入样例1:

```in
error
```

输出样例1:

```out
Lucky Word
2
```

输入样例2：

```in
olympic
```

输出样例2:

```out
No Answer
0
```



code

```cpp
#include <bits/stdc++.h>
using namespace std;
int a[30],b[30];
bool isPrime(int n)
{
	if(n==0)
		return false;
	if(n==1)
		return false;
	if(n==2)
		return true;
	for(int i=2; i*i<=n; i++)
	{
		if(n%i==0)
		{
			return false;
		}
	}
	return true;
}
int main()
{
	string s;
	cin>>s;
	for(int i=0; i<int(s.length()); i++)
	{
		a[s[i]-'a'+1]++;
		b[s[i]-'a'+1]++;
	}
	for(int i=1; i<=26; i++)
	{
		if(b[i]==0)
		{
			b[i]=1024;
		}
	}
	int maxn=*max_element(a+1,a+27);
	int minn=*min_element(b+1,b+27);
	int cha=maxn-minn;
	if(isPrime(cha))
	{
		cout<<"Lucky Word"<<endl;
		cout<<cha;
	}
	else
	{
		cout<<"No Answer"<<endl;
		cout<<0;
		
	}
	return 0;
}

```

